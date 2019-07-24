#include <PrecompiledHeaders.h>

#include "Game.h"

#include "Mewtle/ResourceManager/Model/ModelPremade.h"
#include "Mewtle/UI/Label.h"

namespace Mewtle{
	extern void loadModels();
	extern void loadTextures();

	Entity** Game::entities = nullptr;
	State* Game::state = nullptr;
	Camera* Game::camera = nullptr;
	int Game::id = 0;
	int Game::width = 0, Game::height = 0;
	bool Game::alreadyInitialized = false;
	EventHandler* Game::eventHandler = nullptr;
	
	void Game::initRenderer(std::function<void()> clientInit, std::function<void()> clientTick, std::function<void()> clientRender, State* initState){
		if(alreadyInitialized){
			MTL_CORE_WARN("Engine already initialized !");
			return;
		}
		alreadyInitialized = true;

		Mewtle::Log::init();
		MTL_CORE_TRACE("Initializing...");

		MyGLRenderer::start(clientInit, clientTick, clientRender, initState);
	}

	void Game::init(State* initState){
		MTL_CORE_TRACE("----Logger initialized.");
		eventHandler = new EventHandler();
		MTL_CORE_TRACE("----Event handler initialized.");

		width = MyGLRenderer::width;
		height = MyGLRenderer::height;
		MTL_CORE_TRACE("----Screen initialized.");
		
		ModelPremade::loadModels();
		Mewtle::loadModels();
		MTL_CORE_TRACE("Models loaded.");
		Mewtle::loadTextures();
		MTL_CORE_TRACE("Textures loaded.");

		camera = new Camera();
		state = initState;
		state->init();

		MTL_CORE_TRACE("Initialization successful.");
	}

	void Game::handleInput(){
		state->keyboardInput();
	}

	void Game::tick(){
		state->tick();
	}

	void Game::render(){
		state->render();
	}

	int Game::createTextbox(std::string text, float left, float top, float right, float bottom, int size, float red, float green, float blue, Textbox::ALIGNMENT alignment, bool multiLine, bool verticalStretchToFitBox){
		int id = generateId();
		new Textbox(id, std::move(text), left, top, right, bottom, size, red, green, blue, alignment, multiLine, verticalStretchToFitBox);
		return id;
	}

	int Game::createEntity(Model3D* model, Texture* texture, float x, float y, float z, float rotX, float rotY, float rotZ, float width, float height, float depth){
		int id = generateId();
		new Entity(id, model, texture, x, y, z, rotX, rotY, rotZ, width, height, depth);
		return id;
	}

	int Game::createLabel(Texture* texture, float x, float y, float width, float height, float rot){
		int id = generateId();
		new Label(id, texture, x, y, width, height, rot);
		return id;
	}

	int Game::createTexture(const char* path){
		int id = generateId();
		Texture::createTexture(id, path);
		return id;
	}

	int Game::createModel(const char* path){
		int id = generateId();
		Model3D::createModel(id, path);
		return id;
	}

	int Game::generateId(){
		return id++;
	}

	void Game::drawEntity(Entity* entity){
		entity->render();
	}

	void Game::renderModel(int model, int texture, float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float alpha){
		GLuint id = Texture::getTexture(texture)->getId();
		MyGLRenderer::render(Model3D::getModel(model), &id, x, y, z, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, alpha);
	}

	void Game::drawAllEntities(){
		std::map<int, Entity*>* entities = Entity::getEntities();
		std::list<int>* activeEntities = Entity::getActiveEntities();

		for(int activeEntity : *activeEntities){
			Entity* entity = (*entities)[activeEntity];
			entity->render();
		}
	}

	void Game::drawAllGuiElements(){
		GUIElement::renderAll();
	}

	Entity* Game::getEntity(int id){
		return (*Entity::getEntities())[id];
	}

	GUIElement* Game::getGUIElement(int id){
		return GUIElement::guiElements[id];
	}

	bool Game::keyPressed(int key){
		return MyGLRenderer::keyPressed(key);
	}

	bool Game::keyReleased(int key){
		return MyGLRenderer::keyReleased(key);
	}

	void Game::mouseLeftPressed(double x, double y){
		state->mouseLeftPressed(x, y);
	}

	void Game::mouseLeftReleased(double x, double y){
		state->mouseLeftReleased(x, y);
	}

	void Game::mouseRightPressed(double x, double y){
		state->mouseRightPressed(x, y);
	}

	void Game::mouseRightReleased(double x, double y){
		state->mouseRightReleased(x, y);
	}

	double Game::getMouseX(){
		return MyGLRenderer::mouseX;
	}

	double Game::getMouseY(){
		return MyGLRenderer::mouseY;
	}

	void Game::translateCamera(float x, float y, float z){
		MyGLRenderer::translateCamera(-x, -y, -z);
	}

	void Game::setCameraPosition(float x, float y, float z){
		MyGLRenderer::setCameraPosition(x, y, z);
	}

	void Game::rotateCamera(float angle, float x, float y, float z){
		MyGLRenderer::rotateCamera(angle, x, y, z);
	}

	void Game::scaleCamera(float x, float y, float z){
		MyGLRenderer::scaleCamera(x, y, z);
	}

	void Game::enableLighting() {
		MyGLRenderer::enableLighting();
	}

	void Game::setAmbientLighting(float value) {
		MyGLRenderer::setAmbientLighting(value);
	}

	void Game::setLightPosition(float x, float y, float z) {
		MyGLRenderer::setLightPosition(x, y, z);
	}

	void Game::setLightPower(float power) {
		MyGLRenderer::setLightPower(power);
	}

	void Game::setBackgroundColor(float r, float g, float b, float a){
		MyGLRenderer::setBackgroundColor(r, g, b, a);
	}

	void Game::getMouseVector(double x, double y, Line3D* line){
		MyGLRenderer::getMouseVector(x, y, line);
	}

	Camera* Game::getCamera(){
		return camera;
	}

	void Game::renderPoints(float* vbo, int vboSize, float r, float g, float b, float alpha){
		MyGLRenderer::drawPoints(vbo, vboSize, r, g, b, alpha);
	}

	void Game::renderTriangle(float* vbo, float r, float g, float b, float alpha){
		MyGLRenderer::drawTriangle(vbo, r, g, b, alpha);
	}

	void Game::renderQuad(float* vbo, float r, float g, float b, float alpha){
		MyGLRenderer::drawQuad(vbo, r, g, b, alpha);
	}
}