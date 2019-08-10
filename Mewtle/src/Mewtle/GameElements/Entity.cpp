#include <PrecompiledHeaders.h>

#include "Entity.h"

#include "Mewtle/Core/MyGLRenderer.h"
#include "Mewtle/Utils/Utils.h"
#include "Mewtle/Utils/Math/Line3D.h"

namespace Mewtle{
	std::map<int, Entity*> Entity::entities;
	std::list<int> Entity::activeEntities;

	Entity::Entity(int id, Model3D* model, Texture* texture, float x, float y, float z, float rotX, float rotY, float rotZ, float width, float height, float depth){
		this->model = model;
		this->texture = texture;
		this->x = x;
		this->y = y;
		this->z = z;
		this->rotX = rotX;
		this->rotY = rotY;
		this->rotZ = rotZ;
		this->width = width;
		this->height = height;
		this->depth = depth;
		
		if(model->isTextured()){
			materials = new GLuint[model->getMaterial()->getMaterialCount()];
			for(int i = 0; i < model->getMaterial()->getMaterialCount(); i++){
				materials[i] = model->getMaterial()->getMaterials()[i];
			}
			if(texture != nullptr)
				coverWithMaterial(texture);
		}

		adjustOpenGLCoords();

		addEntity(id, this);
		activeEntities.push_back(id);
	}

	Entity::~Entity(){
		delete(openGLCoords);
		if(materials != nullptr)
			delete(materials);
	}

	Model3D* Entity::getModel(){
		return model;
	}

	std::map<int, Entity*>* Entity::getEntities(){
		return &entities;
	}

	std::list<int>* Entity::getActiveEntities(){
		return &activeEntities;
	}

	void Entity::addEntity(int id, Entity* entity){
		entities[id] = entity;
	}

	void Entity::tick(){
		move();
	}

	void Entity::render(){
		render(1);
	}

	void Entity::render(float alpha){
		if(model->isTextured()){
			MyGLRenderer::renderTexturedModel(model, model->getMaterial(), materials,
				openGLCoords->getX() + openGLCoords->getWidth() / 2,
				openGLCoords->getY() - openGLCoords->getHeight() / 2,
				openGLCoords->getZ() + openGLCoords->getDepth() / 2,
				openGLCoords->getRotX(),
				openGLCoords->getRotY(),
				openGLCoords->getRotZ(),
				openGLCoords->getScaleX(),
				openGLCoords->getScaleY(),
				openGLCoords->getScaleZ(),
				alpha);
		}else{
			MyGLRenderer::drawEntity(this, alpha);
		}
	}

	OpenGLCoords* Entity::getOpenGLCoords(){
		return openGLCoords;
	}

	void Entity::move(){
		float xDist = x2 - getX(), yDist = y2 - getY(), zDist = z2 - getZ();
		if(sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2)) < 16){
			setPosition(x2, y2, z2);
			return;
		}
		float xSpeed = speed * xDist / (sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2)));
		float ySpeed = speed * yDist / (sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2)));
		float zSpeed = speed * zDist / (sqrt(pow(xDist, 2) + pow(yDist, 2) + pow(zDist, 2)));
		setPosition(getX() + xSpeed, getY() + ySpeed, getZ() + zSpeed);
	}

	void Entity::setDestination(float x, float y, float z){
		x2 = x;
		y2 = y;
		z2 = z;
	}

	void Entity::setSpeed(float speed){
		this->speed = speed;
	}

	float Entity::getSpeed(){
		return speed;
	}

	void Entity::setX(float value){
		x = value;
		adjustOpenGLCoords();
	}

	void Entity::setY(float value){
		y = value;
		adjustOpenGLCoords();
	}

	void Entity::setZ(float value){
		z = value;
		adjustOpenGLCoords();
	}

	void Entity::setWidth(float value){
		width = value;
		adjustOpenGLCoords();
	}

	void Entity::setHeight(float value){
		height = value;
		adjustOpenGLCoords();
	}

	void Entity::setDepth(float value){
		depth = value;
		adjustOpenGLCoords();
	}

	void Entity::setPosition(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;

		adjustOpenGLCoords();
	}

	void Entity::setSize(float width, float height, float depth){
		this->width = width;
		this->height = height;
		this->depth = depth;

		adjustOpenGLCoords();
	}

	void Entity::setRotation(float rotX, float rotY, float rotZ){
		this->rotX = rotX;
		this->rotY = rotY;
		this->rotZ = rotZ;

		adjustOpenGLCoords();
	}

	void Entity::setTexture(Texture* texture){
		this->texture = texture;
	}

	GLuint Entity::getTexture(){
		return texture->getId();
	}

	int Entity::getTextureId(){
		return texture->getTextureId();
	}

	void Entity::switchMaterial(int index, Texture* texture){
		if(index >= 0 && index < model->getMaterial()->getMaterialCount())
			materials[index] = texture->getId();
	}

	void Entity::coverWithMaterial(Texture* texture){
		for(int i = 0; i < model->getMaterial()->getMaterialCount(); i++)
			materials[i] = texture->getId();
	}

	void Entity::adjustOpenGLCoords(){
		float tempWidth = width;
		float tempHeight = height;
		float tempDepth = depth;
		width = Utils::convertWidthToOpenGL(width);
		height = Utils::convertHeightToOpenGL(height);
		depth = Utils::convertHeightToOpenGL(depth);

		if(model->getWidth() == 0){
			this->scaleX = 0;
		}
		else{
			this->scaleX = width / model->getWidth();
		}
		if(model->getHeight() == 0){
			this->scaleY = 0;
		}
		else{
			this->scaleY = height / model->getHeight();
		}
		if(model->getDepth() == 0){
			this->scaleZ = 0;
		}
		else{
			this->scaleZ = depth / model->getDepth();
		}

		if(openGLCoords != nullptr){
			delete(openGLCoords);
		}
		openGLCoords = new OpenGLCoords(Utils::getWidthFromPixels((int) x), Utils::getHeightFromPixels((int) y), z, rotX, rotY, rotZ, width, height, depth, scaleX, scaleY, scaleZ);

		width = tempWidth;
		height = tempHeight;
		depth = tempDepth;
	}

	glm::vec3 Entity::getPositionVector(){
		return glm::vec3(x, y, z);
	}

	glm::vec3 Entity::getSizeVector(){
		return glm::vec3(width, height, depth);
	}

	bool Entity::mouseOver(double x, double y){
		double xComp[2], yComp[2], zComp[2];
		MyGLRenderer::getWorldCoordinates(x, y, xComp, yComp, zComp);
		Line3D line = Line3D(xComp[0], yComp[0], zComp[0], xComp[1], yComp[1], zComp[1]);
		double vec[3];
		line.getLineFromZComponent(0, vec);
		// TODO : Rotation not implemented.
		return line.intersectsBox(openGLCoords->getX(), openGLCoords->getY() - openGLCoords->getHeight(), openGLCoords->getZ(), openGLCoords->getWidth(), openGLCoords->getHeight(), openGLCoords->getDepth());
	}

	float Entity::getX(){
		return x;
	}

	float Entity::getY(){
		return y;
	}

	float Entity::getZ(){
		return z;
	}

	float Entity::getWidth(){
		return width;
	}

	float Entity::getHeight(){
		return height;
	}

	float Entity::getDepth(){
		return depth;
	}
}