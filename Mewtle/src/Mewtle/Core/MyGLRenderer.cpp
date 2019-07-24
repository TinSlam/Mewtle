#include <PrecompiledHeaders.h>

#include "MyGLRenderer.h"

#include "Mewtle/Core/Game.h"
#include "Mewtle/Utils/Utils.h"
#include "Mewtle/EventManager/Keyboard/KeyboardUtils.h"
#include "Mewtle/ResourceManager/Texture/stb_image.h"

namespace Mewtle{	
	int MyGLRenderer::width = 1920;
	int MyGLRenderer::height = 1080;

	double MyGLRenderer::mouseX = 0;
	double MyGLRenderer::mouseY = 0;

	Game MyGLRenderer::game;

	bool MyGLRenderer::running = true;
	std::mutex MyGLRenderer::renderLock;

	GLuint MyGLRenderer::programId = 0;
	GLuint MyGLRenderer::textProgramId = 0;
	GLuint MyGLRenderer::pointsProgramID = 0;
	GLuint MyGLRenderer::vaoId = 0;
	GLuint MyGLRenderer::textVbo = 0;
	int MyGLRenderer::mvMatrixId = 0;
	int MyGLRenderer::mvpMatrixId = 0;
	int MyGLRenderer::pointsMvpMatrixID = 0;
	int MyGLRenderer::lightPositionId = 0;
	int MyGLRenderer::ambientLightingId = 0;
	int MyGLRenderer::lightingFlagId = 0;
	int MyGLRenderer::alphaValueId = 0;
	int MyGLRenderer::pointsAlphaValueID = 0;
	int MyGLRenderer::pointsColorID = 0;
	int MyGLRenderer::lightPowerId = 0;

	float MyGLRenderer::ambientLighting = 0;
	bool MyGLRenderer::lightingFlag = 0;
	float MyGLRenderer::lightPower = 0;

	float MyGLRenderer::backgroundColorRed = 1;
	float MyGLRenderer::backgroundColorGreen = 1;
	float MyGLRenderer::backgroundColorBlue = 1;
	float MyGLRenderer::backgroundColorAlpha = 1;

	GLFWwindow* MyGLRenderer::window = nullptr;

	glm::mat4 MyGLRenderer::modelMatrix;
	glm::mat4 MyGLRenderer::projectionMatrix;
	glm::mat4 MyGLRenderer::mvpMatrix;
	glm::mat4 MyGLRenderer::mvMatrix;
	glm::vec4 MyGLRenderer::lightPosition;
	glm::vec4 MyGLRenderer::lightUniform;

	void MyGLRenderer::start(std::function<void()> clientInit, std::function<void()> clientTick, std::function<void()> clientRender, State* initState){
		initializeGlfw();
		createWindow();
		initializeGlew();
		bindVao();
		programId = loadShaders("assets/shaders/vertex_shader.glsl", "assets/shaders/fragment_shader.glsl");
		textProgramId = loadShaders("assets/shaders/text_vertex_shader.glsl", "assets/shaders/text_fragment_shader.glsl");
		pointsProgramID = loadShaders("assets/shaders/points_vertex_shader.glsl", "assets/shaders/points_fragment_shader.glsl");
		mvpMatrixId = glGetUniformLocation(programId, "mvpMatrix");
		pointsMvpMatrixID = glGetUniformLocation(pointsProgramID, "mvpMatrix");
		mvMatrixId = glGetUniformLocation(programId, "mvMatrix");
		lightPositionId = glGetUniformLocation(programId, "lightPosition");
		ambientLightingId = glGetUniformLocation(programId, "ambientLighting");
		lightingFlagId = glGetUniformLocation(programId, "lightingFlag");
		alphaValueId = glGetUniformLocation(programId, "alphaValue");
		lightPowerId = glGetUniformLocation(programId, "lightPower");
		pointsAlphaValueID = glGetUniformLocation(pointsProgramID, "alphaValue");

		//createViewMatrix();
		createProjectionMatrix();

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST); // TODO : Maybe need to change to open the alpha channel.
		glDepthFunc(GL_LESS);
		//glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

		glfwSwapInterval(1);

		initTextRenderer();

		disableLighting();
		game.init(initState);
		clientInit();

		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		glClearColor(backgroundColorRed, backgroundColorGreen, backgroundColorBlue, backgroundColorAlpha);

		glfwSetMouseButtonCallback(window, mouseButtonCallback);

		double lastTime = glfwGetTime();
		int nbFrames = 0;

		std::thread thread(tickLoop, &game);
		do{
			double currentTime = glfwGetTime();
			nbFrames++;
			if(currentTime - lastTime >= 1.0){
				//printf("Render : %d frames. %f ms/frame\n", nbFrames, 1000.0/double(nbFrames));
				nbFrames = 0;
				lastTime += 1.0;
			}

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // NOLINT(hicpp-signed-bitwise)
			glUseProgram(programId);

			if(lightingFlag){
				lightUniform = /*game.getCamera()->getViewMatrix() * */lightPosition;
				glUniform3f(lightPositionId, lightUniform.x, lightUniform.y, lightUniform.z);
				glUniform1f(ambientLightingId, ambientLighting);
				glUniform1i(lightingFlagId, 1);
				glUniform1f(lightPowerId, lightPower);
			}else{
				glUniform1i(lightingFlagId, 0);
			}

			game.tick();
			clientTick();
			renderLock.lock();
			game.render();
			clientRender();
			renderLock.unlock();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

		running = false;
		thread.join();

		glDeleteVertexArrays(1, &vaoId);
		glDeleteProgram(programId);

		Model3D::deleteModels();
		Texture::deleteTextures();
		glfwTerminate();
	}

	void MyGLRenderer::drawPoints(float* vbo, int vboSize, float r, float g, float b, float alpha){
		glUseProgram(pointsProgramID);

		GLuint vboID;
		GLuint iboID;
		for(int i = 0; i < vboSize; i += 3){
			vbo[i] = Utils::getWidthFromPixels((int) vbo[i]);
			vbo[i + 1] = Utils::getHeightFromPixels((int) vbo[i + 1]);
		}
		int iboSize = vboSize / 3;
		short* ibo = new short[iboSize];
		for(short i = 0; i < iboSize; i++){
			ibo[i] = i;
		}
		bindVbo(&vboID, vbo, vboSize);
		bindIbo(&iboID, ibo, iboSize);

		glUniform3f(pointsColorID, r, g, b);
		glUniform1f(pointsAlphaValueID, alpha);
	
		mvpMatrix = projectionMatrix * game.getCamera()->getViewMatrix();
		glUniformMatrix4fv(pointsMvpMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, nullptr);
		glDrawElements(GL_LINE_STRIP, iboSize, GL_UNSIGNED_SHORT, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
		glDeleteBuffers(1, &vboID);
		glDeleteBuffers(1, &iboID);
		delete ibo;
	}

	void MyGLRenderer::drawQuad(float* vbo, float r, float g, float b, float alpha){
		glUseProgram(pointsProgramID);

		GLuint vboID;
		int vboSize = 12;

		int iboSize = vboSize / 2;
		for(int i = 0; i < vboSize; i += 3){
			vbo[i] = Utils::getWidthFromPixels((int) vbo[i]);
			vbo[i + 1] = Utils::getHeightFromPixels((int) vbo[i + 1]);
		}
		short* ibo = new short[iboSize];
		int index = 0;
		for(short i = 0; i < iboSize; i++){
			switch(i){
			case 3:
				ibo[i] = index - 3;
				break;

			case 4:
				ibo[i] = index - 1;
				break;

			case 5:
				ibo[i] = index;
				index++;
				break;

			default:
				ibo[i] = index;
				index++;
			}
		}
		bindVbo(&vboID, vbo, vboSize);

		glUniform3f(pointsColorID, r, g, b);
		glUniform1f(pointsAlphaValueID, alpha);

		mvpMatrix = projectionMatrix * game.getCamera()->getViewMatrix();
		glUniformMatrix4fv(pointsMvpMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, nullptr);
		glDrawElements(GL_TRIANGLE_STRIP, iboSize, GL_UNSIGNED_SHORT, ibo);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
		glDeleteBuffers(1, &vboID);
		delete ibo;
	}

	void MyGLRenderer::drawTriangle(float* vbo, float r, float g, float b, float alpha){
		glUseProgram(pointsProgramID);

		GLuint vboID;
		int vboSize = 9;
		for(int i = 0; i < vboSize; i += 3){
			vbo[i] = Utils::getWidthFromPixels((int) vbo[i]);
			vbo[i + 1] = Utils::getHeightFromPixels((int) vbo[i + 1]);
		}
		int iboSize = 6;
		short* ibo = new short[iboSize];
		ibo[0] = 1;
		ibo[1] = 0;
		ibo[2] = 2;
		ibo[3] = 0;
		ibo[4] = 1;
		ibo[5] = 2;
		bindVbo(&vboID, vbo, vboSize);

		mvpMatrix = projectionMatrix * game.getCamera()->getViewMatrix();
		glUniformMatrix4fv(pointsMvpMatrixID, 1, GL_FALSE, &mvpMatrix[0][0]);

		glUniform3f(pointsColorID, r, g, b);
		glUniform1f(pointsAlphaValueID, alpha);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, nullptr);
		glDrawElements(GL_TRIANGLE_STRIP, iboSize, GL_UNSIGNED_SHORT, ibo);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
		glDeleteBuffers(1, &vboID);
		delete ibo;
	}

	void MyGLRenderer::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
		if(button == GLFW_MOUSE_BUTTON_LEFT){
			if(action == GLFW_PRESS){
				game.mouseLeftPressed(mouseX, mouseY);
			}else if(action == GLFW_RELEASE){
				game.mouseLeftReleased(mouseX, mouseY);
			}
		}else if(button == GLFW_MOUSE_BUTTON_RIGHT){
			if(action == GLFW_PRESS){
				game.mouseRightPressed(mouseX, mouseY);
			}else if(action == GLFW_RELEASE){
				game.mouseRightReleased(mouseX, mouseY);
			}
		}
	}

	void MyGLRenderer::tickLoop(Game* game){
		double lastTime = glfwGetTime();
		int nbFrames = 0;

		do{
			double currentTime = glfwGetTime();
			nbFrames++;
			if(currentTime - lastTime >= 1.0){
				MTL_CORE_TRACE("Tick : {0} frames. {1} ms/frame.", nbFrames, 1000.f / double (nbFrames));
				nbFrames = 0;
				lastTime += 1.0;
			}

			game->handleInput();
			glfwGetCursorPos(window, &mouseX, &mouseY);
			std::this_thread::sleep_for(std::chrono::milliseconds(8));
		}while(running);
	}

	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		glm::ivec2 Size;    // Size of glyph
		glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};
	std::map<GLchar, Character> Characters;
	int fontYOffset;

	void MyGLRenderer::initTextRenderer(){
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			MTL_CORE_ERROR("ERROR::FREETYPE: Could not init FreeType Library.");

		FT_Face face;
		if (FT_New_Face(ft, "assets/fonts/arial.ttf", 0, &face))
			MTL_CORE_ERROR("ERROR::FREETYPE: Failed to load font.");

		FT_Set_Pixel_Sizes(face, 0, 48); // Height = 48, Width = auto.

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		fontYOffset = 0;
		for(GLubyte c = 0; c < 128; c++){
			if(FT_Load_Char(face, c, FT_LOAD_RENDER)){
				MTL_CORE_ERROR("ERROR::FREETYTPE: Failed to load Glyph.");
				continue;
			}
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			Character character = {
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					static_cast<GLuint>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));
			if(fontYOffset < character.Bearing.y / 2){
				fontYOffset = character.Bearing.y / 2;
			}
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		glGenBuffers(1, &textVbo);
		glBindBuffer(GL_ARRAY_BUFFER, textVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glActiveTexture(GL_TEXTURE0);
	}

	void MyGLRenderer::getTextBounds(std::string text, int scale, float* pointer){
		float scaleF = scale / 48.0f;
		int width = 0;
		int height = 0;
		for(auto c = text.begin(); c != text.end(); c++){
			Character ch = Characters[*c];
			if(ch.Size.y > height) height = ch.Size.y;
			if(c + 1 != text.end()) width += (ch.Advance >> 6);
			else width += ch.Bearing.x + ch.Size.x;
		}
		*pointer = width * scaleF;
		*(pointer + 1) = height * scaleF;
	}

	void MyGLRenderer::drawText(std::string text, float x, float y, int size, float red, float green, float blue){
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glUseProgram(textProgramId);

		glUniform3f(glGetUniformLocation(textProgramId, "textColor"), red, green, blue);

		std::string::const_iterator c;
		GLfloat scaleX = static_cast<GLfloat>(2.0f / width) * size / 48;
		GLfloat scaleY = static_cast<GLfloat>(2.0f / height) * size / 48;

		y -= Utils::convertHeightToOpenGL(fontYOffset * size / 48.0f);

		glEnableVertexAttribArray(0);
		for(c = text.begin(); c != text.end(); c++){
			Character ch = Characters[*c];

			GLfloat xpos = x + ch.Bearing.x * scaleX;
			GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scaleY;

			GLfloat w = ch.Size.x * scaleX;
			GLfloat h = ch.Size.y * scaleY;
			// Update VBO for each character
			GLfloat vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos,     ypos,       0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 1.0 },

					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos + w, ypos,       1.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			// Render glyph texture over quad
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);
			// Update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, textVbo);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scaleX; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableVertexAttribArray(0);
		glDisable(GL_BLEND);
	}

	void MyGLRenderer::drawEntity(Entity* entity, float alpha){
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glUseProgram(programId);

		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, entity->getOpenGLCoords()->getPositionVector());
		modelMatrix = glm::translate(modelMatrix, glm::vec3(entity->getOpenGLCoords()->getWidth() / 2, -entity->getOpenGLCoords()->getHeight() / 2, entity->getOpenGLCoords()->getDepth() / 2));
		glm::vec3 rotationVector = entity->getOpenGLCoords()->getRotationVector();
		modelMatrix = glm::rotate(modelMatrix, rotationVector.z, glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, rotationVector.y, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, rotationVector.x, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, entity->getOpenGLCoords()->getScaleVector());
		//modelMatrix = glm::scale(modelMatrix, glm::vec3(Utils::getScreenRatio(), 1.0f, 1.0f));

		mvMatrix = game.getCamera()->getViewMatrix() * modelMatrix;
		mvpMatrix = projectionMatrix * game.getCamera()->getViewMatrix() * modelMatrix;
		glUniformMatrix4fv(mvMatrixId, 1, GL_FALSE, &mvMatrix[0][0]);
		glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &mvpMatrix[0][0]);
		glUniform1f(alphaValueId, alpha);

		useTexture(entity->getTexture());
		render(entity);
	}

	void MyGLRenderer::drawLabel(Label* label, float alpha){
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glUseProgram(programId);

		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1 / Utils::getScreenRatio(), 1, 1));
		modelMatrix = glm::translate(modelMatrix, label->getOpenGLCoords()->getPositionVector());
		modelMatrix = glm::translate(modelMatrix, glm::vec3(label->getOpenGLCoords()->getWidth() / 2, -label->getOpenGLCoords()->getHeight() / 2, label->getOpenGLCoords()->getDepth() / 2));
		glm::vec3 rotationVector = label->getOpenGLCoords()->getRotationVector();
		modelMatrix = glm::rotate(modelMatrix, rotationVector.z, glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, rotationVector.y, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, rotationVector.x, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, label->getOpenGLCoords()->getScaleVector());

		mvMatrix = modelMatrix;
		mvpMatrix = modelMatrix;
		glUniformMatrix4fv(mvMatrixId, 1, GL_FALSE, &mvMatrix[0][0]);
		glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &mvpMatrix[0][0]);
		glUniform1f(alphaValueId, alpha);

		useTexture(label->getTexture());
		render(label);
	}

	void MyGLRenderer::createProjectionMatrix(){
		projectionMatrix = glm::perspective(45.0f, (float) width / height, 1.0f, 100.0f);
	}

	GLuint MyGLRenderer::loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath){
		GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

		std::string vertexShaderCode, fragmentShaderCode;

		std::ifstream vertexShaderStream(vertexShaderPath, std::ios::in);
		if(vertexShaderStream.is_open()){
			std::stringstream strStream;
			strStream << vertexShaderStream.rdbuf();
			vertexShaderCode = strStream.str();
			vertexShaderStream.close();
		}else{
			MTL_CORE_ERROR("Failed to open shader from {0}", vertexShaderPath);
			exit(4);
		}
		std::ifstream fragmentShaderStream(fragmentShaderPath, std::ios::in);
		if(fragmentShaderStream.is_open()){
			std::stringstream strStream;
			strStream << fragmentShaderStream.rdbuf();
			fragmentShaderCode = strStream.str();
			fragmentShaderStream.close();
		}else{
			MTL_CORE_ERROR("Failed to open shader from {0}", fragmentShaderPath);
			exit(4);
		}

		GLint result = GL_FALSE;
		int infoLogLength;

		// Compile vertex shader.
		MTL_CORE_INFO("Compiling shader : {0}", vertexShaderPath);
		char const * vertexSourcePointer = vertexShaderCode.c_str();
		glShaderSource(vertexShaderId, 1, &vertexSourcePointer , nullptr);
		glCompileShader(vertexShaderId);

		// Check Vertex Shader
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		if(infoLogLength > 0){
			std::vector<char> vertexShaderErrorMessage(static_cast<unsigned int>(infoLogLength + 1));
			glGetShaderInfoLog(vertexShaderId, infoLogLength, nullptr, &vertexShaderErrorMessage[0]);
			MTL_CORE_ERROR("{0}", &vertexShaderErrorMessage[0]);
		}

		// Compile fragment shader.
		MTL_CORE_INFO("Compiling shader : {0}", fragmentShaderPath);
		char const * fragmentSourcePointer = fragmentShaderCode.c_str();
		glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer , nullptr);
		glCompileShader(fragmentShaderId);

		// Check fragment Shader
		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		if(infoLogLength > 0){
			std::vector<char> fragmentShaderErrorMessage(static_cast<unsigned int>(infoLogLength + 1));
			glGetShaderInfoLog(fragmentShaderId, infoLogLength, nullptr, &fragmentShaderErrorMessage[0]);
			MTL_CORE_ERROR("{0}", &fragmentShaderErrorMessage[0]);
		}

		// Link the program
		MTL_CORE_INFO("Linking program.");
		GLuint programId = glCreateProgram();
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);
		glLinkProgram(programId);

		// Check the program
		glGetProgramiv(programId, GL_LINK_STATUS, &result);
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		if(infoLogLength > 0){
			std::vector<char> programErrorMessage(static_cast<unsigned int>(infoLogLength + 1));
			glGetProgramInfoLog(programId, infoLogLength, nullptr, &programErrorMessage[0]);
			MTL_CORE_ERROR("{0}", &programErrorMessage[0]);
		}

		glDetachShader(programId, vertexShaderId);
		glDetachShader(programId, fragmentShaderId);

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);

		return programId;
	}

	GLuint MyGLRenderer::loadTexture(const char* path){
		GLuint textureID;
		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);

		int width, height;
		unsigned char* image = stbi_load(path, &width, &height, nullptr, 0); 
		//unsigned char* image = SOIL_load_image(path, &width, &height, nullptr, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return textureID;
	}

	void MyGLRenderer::useTexture(GLuint id){
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void MyGLRenderer::bindVao(){
		glGenVertexArrays(1, &vaoId);
		glBindVertexArray(vaoId);
	}

	void MyGLRenderer::bindVbo(GLuint *vboId, GLfloat *vbo, int size){
		glGenBuffers(1, vboId);
		glBindBuffer(GL_ARRAY_BUFFER, *vboId);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vbo, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void MyGLRenderer::bindIbo(GLuint* iboId, short* ibo, int size){
		glGenBuffers(1, iboId);
		glBindBuffer(GL_ARRAY_BUFFER, *iboId);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(short), ibo, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void MyGLRenderer::render(Entity* entity){
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, *entity->getModel()->getVboId());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *entity->getModel()->getIboId());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<const void *>(12));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<const void *>(24));
		glDrawElements(GL_TRIANGLES, entity->getModel()->getIboLength(), GL_UNSIGNED_SHORT, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	void MyGLRenderer::render(Model3D* model, GLuint* texture, float x, float y, float z, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, float alpha){
		glUseProgram(programId);

		modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
		//modelMatrix = glm::translate(modelMatrix, glm::vec3(entity->getOpenGLCoords()->getWidth() / 2, -entity->getOpenGLCoords()->getHeight() / 2, entity->getOpenGLCoords()->getDepth() / 2));
		glm::vec3 rotationVector = glm::vec3(rotX, rotY, rotZ);
		modelMatrix = glm::rotate(modelMatrix, rotationVector.z, glm::vec3(0, 0, 1));
		modelMatrix = glm::rotate(modelMatrix, rotationVector.y, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, rotationVector.x, glm::vec3(1, 0, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(scaleX, scaleY, scaleZ));
		//modelMatrix = glm::scale(modelMatrix, glm::vec3(Utils::getScreenRatio(), 1.0f, 1.0f));

		mvMatrix = game.getCamera()->getViewMatrix() * modelMatrix;
		mvpMatrix = projectionMatrix * game.getCamera()->getViewMatrix() * modelMatrix;
		glUniformMatrix4fv(mvMatrixId, 1, GL_FALSE, &mvMatrix[0][0]);
		glUniformMatrix4fv(mvpMatrixId, 1, GL_FALSE, &mvpMatrix[0][0]);
		glUniform1f(alphaValueId, alpha);

		useTexture(*texture);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, *(model->getVboId()));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(model->getIboId()));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 32, nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<const void *>(12));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 32, reinterpret_cast<const void *>(24));
		glDrawElements(GL_TRIANGLES, model->getIboLength(), GL_UNSIGNED_SHORT, nullptr);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

	void MyGLRenderer::initializeGlfw(){
		if(!glfwInit()){
			MTL_CORE_ERROR("Failed to initialize GLFW.");
			exit(0);
		}
	}

	void MyGLRenderer::createWindow(){
		glEnable(GL_MULTISAMPLE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_DECORATED, GL_FALSE);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		window = glfwCreateWindow(width, height, "Starter", nullptr, nullptr);
		//window = glfwCreateWindow(mode->width, mode->height, "Starter", monitor, nullptr);
		if(window == nullptr){
			MTL_CORE_ERROR("Failed to open GLFW window. If you have an Intel GPU they are not 3.3 compatible. Try the 2.1 version.");
			glfwTerminate();
			exit(1);
		}
		glfwMakeContextCurrent(window);
	}

	void MyGLRenderer::initializeGlew(){
		glewExperimental = GL_TRUE;
		if(glewInit() != GLEW_OK){
			MTL_CORE_ERROR("Failed to initialize GLEW.");
			exit(2);
		}
	}

	void MyGLRenderer::setCameraPosition(float x, float y, float z){
		renderLock.lock();
		game.getCamera()->setPosition(x, y, z);
		renderLock.unlock();
	}

	void MyGLRenderer::translateCamera(float x, float y, float z){
		renderLock.lock();
		game.getCamera()->translate(x, y, z);
		renderLock.unlock();
	}

	void MyGLRenderer::rotateCamera(float angle, float x, float y, float z){
		renderLock.lock();
		game.getCamera()->rotate(angle, x, y, z);
		renderLock.unlock();
	}

	void MyGLRenderer::scaleCamera(float x, float y, float z){
		renderLock.lock();
		game.getCamera()->scale(x, y, z);
		renderLock.unlock();
	}

	void MyGLRenderer::getWorldCoordinates(double x, double y, double* worldX, double* worldY, double* worldZ){
		double modelMatrix[16];
		double projMatrix[16];
		GLint viewport[4] = {0, 0, width, height};

		y = height - y;
		const float *pSource = (const float*) glm::value_ptr(projectionMatrix);
		for(int i = 0; i < 16; ++i)
			projMatrix[i] = pSource[i];

		const float *pSource2 = (const float*) glm::value_ptr(game.getCamera()->getViewMatrix());
		for(int i = 0; i < 16; ++i)
			modelMatrix[i] = pSource2[i];

		gluUnProject(x, y, 1, modelMatrix, projMatrix, viewport, worldX, worldY, worldZ);
		gluUnProject(x, y, 0, modelMatrix, projMatrix, viewport, worldX + 1, worldY + 1, worldZ + 1);
	}

	void MyGLRenderer::getMouseVector(double x, double y, Line3D* line){
		double xComp[2], yComp[2], zComp[2];
		MyGLRenderer::getWorldCoordinates(x, y, xComp, yComp, zComp);
		*line = Line3D(xComp[0], yComp[0], zComp[0], xComp[1], yComp[1], zComp[1]);
	}

	bool MyGLRenderer::keyPressed(int key){
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	bool MyGLRenderer::keyReleased(int key){
		if(KeyboardUtils::getFlag(key)){
			if(glfwGetKey(window, key) == GLFW_RELEASE){
				KeyboardUtils::setFlag(key, false);
				return true;
			}
		}
		if(glfwGetKey(window, key) == GLFW_PRESS){
			KeyboardUtils::setFlag(key, true);
		}	
		return false;
	}

	void MyGLRenderer::setLightPosition(float x, float y, float z){
		lightPosition = glm::vec4(x, y, z, 1);
	}

	void MyGLRenderer::setAmbientLighting(float value){
		ambientLighting = value;
	}

	void MyGLRenderer::setBackgroundColor(float r, float g, float b, float a){
		backgroundColorRed = r;
		backgroundColorGreen = g;
		backgroundColorBlue = b;
		backgroundColorAlpha = a;
	}

	void MyGLRenderer::enableLighting(){
		lightingFlag = true;
	}

	void MyGLRenderer::disableLighting(){
		lightingFlag = false;
	}

	void MyGLRenderer::setLightPower(float power) {
		lightPower = power;
	}
}
