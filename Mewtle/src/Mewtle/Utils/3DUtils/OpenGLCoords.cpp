#include <PrecompiledHeaders.h>

#include "OpenGLCoords.h"

namespace Mewtle{
	OpenGLCoords::OpenGLCoords(float x, float y, float z, float rotX, float rotY, float rotZ, float width, float height, float depth, float scaleX, float scaleY, float scaleZ){
		this->x = x;
		this->y = y;
		this->z = z;
		this->rotX = rotX;
		this->rotY = rotY;
		this->rotZ = rotZ;
		this->scaleX = scaleX;
		this->scaleY = scaleY;
		this->scaleZ = scaleZ;
		this->width = width;
		this->height = height;
		this->depth = depth;
	}

	float OpenGLCoords::getX(){
		return x;
	}

	float OpenGLCoords::getY(){
		return y;
	}

	float OpenGLCoords::getZ(){
		return z;
	}

	float OpenGLCoords::getScaleX(){
		return scaleX;
	}

	float OpenGLCoords::getScaleY(){
		return scaleY;
	}

	float OpenGLCoords::getScaleZ(){
		return scaleZ;
	}

	float OpenGLCoords::getRotX(){
		return rotX;
	}

	float OpenGLCoords::getRotY(){
		return rotY;
	}

	float OpenGLCoords::getRotZ(){
		return rotZ;
	}

	float OpenGLCoords::getWidth(){
		return width;
	}

	float OpenGLCoords::getHeight(){
		return height;
	}

	float OpenGLCoords::getDepth(){
		return depth;
	}

	glm::vec3 OpenGLCoords::getPositionVector(){
		return glm::vec3(x, y, z);
	}

	glm::vec3 OpenGLCoords::getRotationVector(){
		return glm::vec3(rotX, rotY, rotZ);
	}

	glm::vec3 OpenGLCoords::getScaleVector(){
		return glm::vec3(scaleX, scaleY, scaleZ);
	}
}