#pragma once

#include "Mewtle/Core/MyGLRenderer.h"

#include "Mewtle/GameElements/State.h"
#include "Mewtle/GameElements/Camera.h"
#include "Mewtle/GameElements/Entity.h"

#include "Mewtle/EventManager/EventHandler.h"

#include "Mewtle/UI/GUIElement.h"
#include "Mewtle/UI/Textbox/Textbox.h"

#include "Mewtle/Utils/Math/Line3D.h"

namespace Mewtle{
	class Game{
		public :
			static State* state;
			static Camera* camera;
			static int width, height;

			static void initRenderer(std::function<void()> clientInit, std::function<void()> clientTick, std::function<void()> clientRender, State* initState);
			static void init(State* initState);
			static void handleInput();
			static void tick();
			static void render();
			static int generateId();
			static int createEntity(Model3D*, Texture*, float, float, float, float, float, float, float, float, float);
			static int createLabel(Texture*, float, float, float, float, float);
			static int createModel(const char*);
			static int createTexture(const char*);
			static int createTextbox(std::string text, float left, float top, float right, float bottom, int size, float red, float green, float blue, Textbox::ALIGNMENT alignment, bool multiline, bool verticalStretchToFitBox);
			static void drawEntity(Entity*);
			static void renderModel(int model, int texture, float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float alpha);
			static void drawAllEntities();
			static void drawAllGuiElements();
			static Entity* getEntity(int id);
			static GUIElement* getGUIElement(int id);
			static void translateCamera(float, float, float);
			static void setCameraPosition(float, float, float);
			static void rotateCamera(float, float, float, float);
			static void scaleCamera(float, float, float);
			static bool keyPressed(int);
			static bool keyReleased(int);
			static void mouseLeftPressed(double, double);
			static void mouseLeftReleased(double, double);
			static void mouseRightPressed(double, double);
			static void mouseRightReleased(double, double);
			static double getMouseX();
			static double getMouseY();
			static void enableLighting();
			static void setAmbientLighting(float value);
			static void setLightPosition(float x, float y, float z);
			static void setLightPower(float power);
			static void setBackgroundColor(float r, float g, float b, float a);
			static void getMouseVector(double x, double y, Line3D* line);
			static void renderPoints(float* vbo, int vboSize, float r, float g, float b, float alpha);
			static void renderQuad(float* vbo, float r, float g, float b, float alpha);
			static void renderTriangle(float* vbo, float r, float g, float b, float alpha);
			static Camera* getCamera();

		private :
			static bool alreadyInitialized;
			static EventHandler* eventHandler;

			static Entity** entities;
			static int id;
	};
}
