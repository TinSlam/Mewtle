#include <PrecompiledHeaders.h>

#include "Utils.h"
#include "Mewtle/Core/MyGLRenderer.h"

namespace Mewtle{
	void Utils::splitString(std::string string, char character, std::vector<std::string>* vector){
		std::string str;
		for(size_t i = 0; i < string.length(); i++){
			if(string[i] == character){
				vector->push_back(str);
				str = "";
			}else{
				str += string[i];
			}
		}
		vector->push_back(str);
	}

	void Utils::breakDownString(std::string string, int lines, std::vector<std::string>* vector){
		vector->clear();
		std::vector<int> spaces;
		for(size_t i = 0; i < string.size(); i++){
			if(iswspace(static_cast<wint_t>(string[i]))){
				spaces.push_back((int) i);
			}
		}
		std::vector<int> indices;
		for(int i = 0; i < lines - 1; i++){
			int index = findClosestValueTo(spaces, (float) string.size() * (i + 1) / lines);
			if(index != -1){
				if(std::find(indices.begin(), indices.end(), spaces[index]) == indices.end()){
					indices.push_back(spaces[index]);
				}
			}
		}
		for(size_t i = 0; i < indices.size() + 1; i++){
			int lastIndex = 0;
			int nextIndex = (int) string.size();
			if(i != 0){
				lastIndex = indices[i - 1] + 1;
			}
			if(i != indices.size()){
				nextIndex = indices[i];
			}
			vector->push_back(string.substr(static_cast<unsigned int>(lastIndex), static_cast<unsigned int>(nextIndex - lastIndex)));
		}
		if(vector->empty()) vector->push_back(string);
	}

	int Utils::findClosestValueTo(std::vector<int> vector, float value){
		int index = -1;
		float dist = 10000000;
		for(size_t i = 0; i < vector.size(); i++){
			if(distance(value, (float) vector[i]) < dist){
				index = (int) i;
				dist = distance(value, (float) vector[i]);
			}
		}
		return index;
	}

	float Utils::distance(float x, float y){
		return abs(x - y);
	}

	float Utils::distance(float x1, float y1, float x2, float y2){
		return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	}

	bool Utils::stringStartsWith(std::string subString, std::string string){
		for(size_t i = 0; i < subString.length(); i++){
			if(string[i] == '\0'){
				return false;
			}
			if(subString[i] != string[i]) return false;
		}
		return true;
	}

	float Utils::getWidthPercentage(float percentage){
		return percentage * MyGLRenderer::width / 100;
	}

	float Utils::getHeightPercentage(float percentage){
		return percentage * MyGLRenderer::height / 100;
	}

	float Utils::getOpenGLWidthInPixels(double value){
		value /= getScreenRatio();
		return ((float) value + 1) * MyGLRenderer::width / 2;
	}

	float Utils::getOpenGLHeightInPixels(double value){
		return MyGLRenderer::height - ((float) value + 1) * MyGLRenderer::height / 2;;
	}

	float Utils::getHeightFromPixels(int pixels) {
		return 1 - 2.0f * pixels / MyGLRenderer::height;
	}

	float Utils::getWidthFromPixels(int pixels){
		return 2.0f * pixels * getScreenRatio() / MyGLRenderer::width - getScreenRatio();
	}

	float Utils::convertWidthToOpenGL(float pixel){
		pixel *= getScreenRatio();
		return pixel * 2.0f / MyGLRenderer::width;
	}

	float Utils::convertHeightToOpenGL(float pixel){
		return (float) pixel * 2 / MyGLRenderer::height;
	}

	float Utils::getScreenRatio(){
		return (float) MyGLRenderer::width / MyGLRenderer::height;
	}

	int Utils::max(int x, int y){
		return x > y ? x : y;
	}

	float Utils::max(float x, float y){
		return x > y ? x : y;
	}

	int Utils::min(int x, int y){
		return x < y ? x : y;
	}

	float Utils::min(float x, float y){
		return x < y ? x : y;
	}

	float Utils::abs(float number) {
		return number > 0 ? number : -number;
	}

	float Utils::toDegrees(float radians){
		return radians / (float) M_PI * 180;
	}

	float Utils::toRadians(float degrees){
		return degrees / 180 * (float) M_PI;
	}

	void Utils::printMatrix(glm::mat4 matrix){
		MTL_CORE_INFO("Mewtle::Utils::printMatrix() function is commented out.");
		/*for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				float temp = *(glm::value_ptr(matrix) + 4 * j + i);
				if(abs(temp) < 0.01f) temp = 0;
			}
			std::cout << std::endl;
		}*/
	}

	void Utils::printMatrix(double* matrix){
		MTL_CORE_INFO("Mewtle::Utils::printMatrix() function is commented out.");
		/*for(int i = 0; i < 4; i++){
			for(int j = 0; j < 4; j++){
				float temp = (float) *(matrix + 4 * j + i);
				if(abs(temp) < 0.01f) temp = 0;
				std::cout << temp << " ";
			}
			std::cout << std::endl;
		}*/
	}

	void Utils::printVector(glm::vec3 vector){
		float x = vector.x;
		float y = vector.y;
		float z = vector.z;
		if(abs(x) < 0.01f) x = 0;
		if(abs(y) < 0.01f) y = 0;
		if(abs(z) < 0.01f) z = 0;
		MTL_CORE_INFO("Vector : {0} {1} {2}", x, y, z);
	}

	bool Utils::isInRect(float x, float y, float x1, float y1, float x2, float y2){
		return x >= x1 && x <= x2 && y >= y1 && y <= y2;
	}

	double Utils::getPI(){
		return M_PI;
	}

	double Utils::atan(float dy, float dx){
		return atan2(dy, dx);
	}
}