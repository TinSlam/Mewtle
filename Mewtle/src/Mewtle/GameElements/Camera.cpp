#include <PrecompiledHeaders.h>

#include "Camera.h"

#include "Mewtle/Utils/Utils.h"

namespace Mewtle{
	Camera::Camera(){
		init();
	}

	Camera::~Camera(){

	}

	void Camera::init(){
		float eyeX = -Utils::getScreenRatio();
		float eyeY = -2;
		float eyeZ = 2;
		float lookX = -Utils::getScreenRatio();
		float lookY = 0;
		float lookZ = 0;
		upX = 0;
		upY = 1;
		upZ = 1;
		scaleX = 1;
		scaleY = 1;
		scaleZ = 1;
		cameraX = eyeX;
		cameraY = eyeY;
		cameraZ = eyeZ;
		float temp = sqrt(pow(eyeX - lookX, 2) + pow(eyeY - lookY, 2) + pow(eyeZ - lookZ, 2));
		rotX = asin(sqrt(pow(eyeY - lookY, 2) + pow(eyeZ - lookZ, 2)) / temp);
		rotY = asin(sqrt(pow(eyeX - lookX, 2) + pow(eyeZ - lookZ, 2)) / temp);
		rotZ = asin(sqrt(pow(eyeX - lookX, 2) + pow(eyeY - lookY, 2)) / temp);
		// TODO : Assign correct signs to rotations.
		glm::vec3 eye(eyeX, eyeY, eyeZ);
		glm::vec3 look(lookX, lookY, lookZ);
		glm::vec3 up(upX, upY, upZ);
		viewMatrix = glm::lookAt(eye, look, up);
	}

	void Camera::translate(float x, float y, float z){
		viewMatrix = glm::translate(viewMatrix, glm::vec3(x, y, z));

		cameraX += x;
		cameraY += y;
		cameraZ += z;
	}

	void Camera::rotate(float angle, float x, float y, float z){
		viewMatrix = glm::rotate(viewMatrix, angle, glm::vec3(x, y, z));

		rotX += angle * x / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
		rotY += angle * y / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
		rotZ += angle * z / (sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
	}

	void Camera::scale(float x, float y, float z){
		viewMatrix = glm::translate(viewMatrix, glm::vec3(-cameraX, -cameraY, -cameraZ));
		viewMatrix = glm::scale(viewMatrix, glm::vec3(x, y, z));
		viewMatrix = glm::translate(viewMatrix, glm::vec3(cameraX, cameraY, cameraZ));
		scaleX *= x;
		scaleY *= y;
		scaleZ *= z;
	}

	void Camera::setPosition(float x, float y, float z){
		translate(-cameraX, -cameraY, -cameraZ);
		translate(x, y, z);
	}

	glm::mat4 Camera::getViewMatrix(){
		return viewMatrix;
	}

	float Camera::getCameraX() {
		return cameraX;
	}

	float Camera::getCameraY() {
		return cameraY;
	}

	float Camera::getCameraZ() {
		return cameraZ;
	}

	float Camera::getRotX(){
		return rotX;
	}

	float Camera::getRotY(){
		return rotY;
	}

	float Camera::getRotZ(){
		return rotZ;
	}
}