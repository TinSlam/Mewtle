#ifndef MEWTLEENGINE_UTILS_H
#define MEWTLEENGINE_UTILS_H

namespace Mewtle{
	class Utils{
	public :
		static void printMatrix(glm::mat4 matrix);
		static void printMatrix(double* matrix);
		static void printVector(glm::vec3 matrix);

		static void splitString(std::string, char, std::vector<std::string>*);
		static bool stringStartsWith(std::string, std::string);
		static void breakDownString(std::string, int, std::vector<std::string>*);

		static float getWidthPercentage(float);
		static float getHeightPercentage(float);

		static float getOpenGLWidthInPixels(double);
		static float getOpenGLHeightInPixels(double);
		static float getHeightFromPixels(int);
		static float getWidthFromPixels(int);
		static float convertWidthToOpenGL(float);
		static float convertHeightToOpenGL(float);

		static float getScreenRatio();

		static int findClosestValueTo(std::vector<int>, float);

		static int max(int, int);
		static float max(float, float);
		static int min(int, int);
		static float min(float, float);
		static float abs(float i);
		static float distance(float, float);
		static float distance(float, float, float, float);
		static float toDegrees(float radians);
		static float toRadians(float degrees);

		static bool isInRect(float x, float y, float x1, float y1, float x2, float y2);
		static double getPI();
		static double atan(float dy, float dx);
	};
}

#endif //MEWTLEENGINE_UTILS_H
