#pragma once

namespace Mewtle{
	class OpenGLCoords{
	private :
		float x = 0, y = 0, z = 0;
		float scaleX = 0, scaleY = 0, scaleZ = 0;
		float rotX = 0, rotY = 0, rotZ = 0;
		float width = 0, height = 0, depth = 0;

	public :
		OpenGLCoords(float, float, float, float, float, float, float, float, float, float, float, float);

		float getX();
		float getY();
		float getZ();
		float getScaleX();
		float getScaleY();
		float getScaleZ();
		float getRotX();
		float getRotY();
		float getRotZ();
		float getWidth();
		float getHeight();
		float getDepth();

		glm::vec3 getPositionVector();
		glm::vec3 getRotationVector();
		glm::vec3 getScaleVector();
	};
}