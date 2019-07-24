#ifndef MEWTLEENGINE_MYGLRENDERER_H
#define MEWTLEENGINE_MYGLRENDERER_H

#include <ft2build.h>
#include <freetype/freetype.h>

#include "Mewtle/GameElements/State.h"
#include "Mewtle/Core/Game.h"
#include "Mewtle/UI/Label.h"
#include "Mewtle/Utils/Math/Line3D.h"

namespace Mewtle{
	class Game;

	class MyGLRenderer{
	    static GLFWwindow* window;
	    static GLuint vaoId, programId, textProgramId, pointsProgramID, textVbo;
	    static int mvpMatrixId, mvMatrixId, pointsMvpMatrixID;
	    static int lightingFlagId, lightPositionId, ambientLightingId, lightPowerId;
		static int alphaValueId, pointsAlphaValueID, pointsColorID;
	
	    static glm::mat4 mvMatrix;
	    static glm::mat4 mvpMatrix;
	    static glm::mat4 modelMatrix;
	    static glm::mat4 projectionMatrix;
	    static glm::vec4 lightPosition;
	    static glm::vec4 lightUniform;
	
	    static bool lightingFlag;
	    static float ambientLighting;
	    static float lightPower;
	
		static float backgroundColorRed;
		static float backgroundColorGreen;
		static float backgroundColorBlue;
		static float backgroundColorAlpha;
	
	    static void initializeGlfw();
	    static void createWindow();
	    static void initializeGlew();
	    static void initTextRenderer();
	    static void render(Entity*);
	    static void bindVao();
	    static void createProjectionMatrix();
	
	    static void mouseButtonCallback(GLFWwindow*, int, int, int);
	
	    static GLuint loadShaders(std::string, std::string);
	    static void useTexture(GLuint);
	
	    public:
	        static void start(std::function<void()> clientInit, std::function<void()> clientTick, std::function<void()> clientRender, State* initState);
	        static void tickLoop(Game*);
	        static void drawEntity(Entity*, float alpha);
			static void render(Model3D* model, GLuint* texture, float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float alpha);
	        static void drawLabel(Label*, float alpha);
	        static void drawText(std::string, float, float, int, float, float, float);
			static void drawPoints(float* vbo, int vboSize, float r, float g, float b, float alpha);
			static void drawQuad(float* vbo, float r, float g, float b, float alpha);
			static void drawTriangle(float* vbo, float r, float g, float b, float alpha);
	        static GLuint loadTexture(const char*);
	        static void bindVbo(GLuint *, GLfloat *, int size);
	        static void bindIbo(GLuint *, short*, int size);
	
	        static void getTextBounds(std::string, int, float*);
	
	        static void translateCamera(float, float, float);
	        static void rotateCamera(float, float, float, float);
	        static void scaleCamera(float, float, float);
	        static void setCameraPosition(float, float, float);
	
			static void getWorldCoordinates(double x, double y, double* worldX, double* worldY, double* worldZ);
			static void getMouseVector(double x, double y, Line3D* line);
	
	        static void enableLighting();
	        static void disableLighting();
	        static void setLightPosition(float, float, float);
	        static void setAmbientLighting(float);
	
			static void setBackgroundColor(float r, float g, float b, float a);
	
			static bool keyPressed(int key);
			static bool keyReleased(int key);
	
			static void setLightPower(float power);
	
	    static Game game;
	
	    static int height;
	    static int width;
	
	    static double mouseX;
	    static double mouseY;
	
	    static std::mutex renderLock;
	    static bool running;
	};
}

#endif //MEWTLEENGINE_MYGLRENDERER_H