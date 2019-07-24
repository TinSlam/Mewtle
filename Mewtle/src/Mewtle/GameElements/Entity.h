#ifndef MEWTLEENGINE_ENTITY_H
#define MEWTLEENGINE_ENTITY_H

#include "Mewtle/ResourceManager/Model/Model3D.h"
#include "Mewtle/ResourceManager/Texture/Texture.h"

#include "Mewtle/Utils/3DUtils/OpenGLCoords.h"

namespace Mewtle{
	class Entity{
		OpenGLCoords* openGLCoords = nullptr;

		static std::map<int, Entity*> entities;
		static std::list<int> activeEntities;
		static void addEntity(int, Entity*);

	protected :
		Texture* texture = nullptr;
		Model3D* model = nullptr;
		float x = 0, y = 0, z = 0;
		float rotX = 0, rotY = 0, rotZ = 0;
		float scaleX = 1, scaleY = 1, scaleZ = 1;
		float width = 0, height = 0, depth = 0;
		float speed = 0;
		float x2 = 0, y2 = 0, z2 = 0;

	public:
		explicit Entity(int, Model3D*, Texture*, float, float, float, float, float, float, float, float, float);
		~Entity();

		glm::vec3 getPositionVector();
		glm::vec3 getSizeVector();
		Model3D* getModel();
		GLuint getTexture();
		int getTextureId();

		void adjustOpenGLCoords();

		static std::map<int, Entity*>* getEntities();
		static std::list<int>* getActiveEntities();

		bool mouseOver(double x, double y);

		virtual void tick();
		virtual void render();
		virtual void render(float alpha);

		OpenGLCoords* getOpenGLCoords();

		void move();
		void setDestination(float x, float y, float z);
		void setSpeed(float speed);
		float getSpeed();

		void setX(float value);
		void setY(float value);
		void setZ(float value);

		void setWidth(float value);
		void setHeight(float value);
		void setDepth(float value);

		float getX();
		float getY();
		float getZ();
	
		float getWidth();
		float getHeight();
		float getDepth();

		void setPosition(float x, float y, float z);
		void setSize(float width, float height, float depth);
		void setRotation(float rotX, float rotY, float rotZ);
		void setTexture(Texture* texture);
	};
}
#endif //MEWTLEENGINE_ENTITY_H