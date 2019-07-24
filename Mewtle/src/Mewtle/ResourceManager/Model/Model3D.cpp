#include <PrecompiledHeaders.h>

#include "Model3D.h"

#include "Mewtle/Core/MyGLRenderer.h"
#include "Mewtle/ResourceManager/Model/ModelLoader.h"

namespace Mewtle{
	std::map<const int, Model3D*> Model3D::models;

	void Model3D::createModel(int id, const char* path){
		mapModel(id, path);
	}

	void Model3D::mapModel(int id, const char* path){
		models[id] = new Model3D(path);
	}

	void Model3D::deleteModels(){
		for(std::map<const int, Model3D*>::iterator it = models.begin(); it != models.end(); it++){
			deleteModel(it->second);
		}
	}

	Model3D* Model3D::getModel(int id){
		return models[id];
	}

	void Model3D::deleteModel(Model3D* model){
		glDeleteBuffers(1, model->getVboId());
		free(model->vbo);
		delete(model);
	}

	Model3D::Model3D(const char* path){
		ModelLoader::loadObj(path, &vbo, &vboLength, &ibo, &iboLength, &width, &height, &depth);
		MyGLRenderer::bindVbo(&vboId, vbo, vboLength);
		MyGLRenderer::bindIbo(&iboId, ibo, iboLength);
	}

	int Model3D::getIboLength(){
		return iboLength;
	}

	int Model3D::getVboLength(){
		return vboLength;
	}

	GLuint* Model3D::getVboId(){
		return &vboId;
	}

	GLuint* Model3D::getIboId(){
		return &iboId;
	}

	float Model3D::getWidth(){
		return width;
	}

	float Model3D::getHeight(){
		return height;
	}

	float Model3D::getDepth(){
		return depth;
	}
}