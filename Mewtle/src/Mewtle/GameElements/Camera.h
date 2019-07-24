#pragma once

namespace Mewtle{
	class Camera{
		float cameraX = 0, cameraY = 0, cameraZ = 0;
		float rotX = 0, rotY = 0, rotZ = 0;
		float scaleX = 0, scaleY = 0, scaleZ = 0;
		float upX = 0, upY = 0, upZ = 0;
	
		glm::mat4 viewMatrix;

	public :
		Camera();
		~Camera();

		void init();
		void translate(float x, float y, float z);
		void rotate(float angle, float x, float y, float z);
		void scale(float x, float y, float z);
		void setPosition(float x, float y, float z);
		glm::mat4 getViewMatrix();
		float getCameraX();
		float getCameraY();
		float getCameraZ();
		float getRotX();
		float getRotY();
		float getRotZ();
	};
}