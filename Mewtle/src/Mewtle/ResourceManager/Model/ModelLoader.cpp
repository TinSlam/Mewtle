#include <PrecompiledHeaders.h>

#include "ModelLoader.h"

#include "Mewtle/Utils/Utils.h"

namespace Mewtle{
	void ModelLoader::loadObj(const char* path, GLfloat** vbo, int* vboLength, short** ibo, int* iboLength, float* width, float* height, float* depth){
		std::vector<float*> vertices;
		std::vector<float*> textureCoordinates;
		std::vector<float*> normals;
		std::vector<short*> faces;
		std::vector<short> verticesFoundSoFar;
		bool newFace = true;
		short lastFaces[3];
		short lastFacesNewValue[3];

		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float minZ = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::min();
		float maxY = std::numeric_limits<float>::min();
		float maxZ = std::numeric_limits<float>::min();

		std::ifstream inputStream;
		inputStream.open(path);
		if(!inputStream){
			MTL_CORE_ERROR("Could not open file : {0}", path);
			exit(5);
		}

		std::stringstream strStream;
		strStream << inputStream.rdbuf();//read the file
		std::string data = strStream.str();

		inputStream.close();

		std::vector<std::string> lines;
		Utils::splitString(data, '\n', &lines);
		for(auto line : lines){
			if(Utils::stringStartsWith("v ", line)){
				std::vector<std::string> strList;
				Utils::splitString(line, ' ', &strList);
				float x = (float) atof(strList[1].c_str());
				float y = (float) atof(strList[2].c_str());
				float z = (float) atof(strList[3].c_str());
				if(x < minX) minX = x;
				if(x > maxX) maxX = x;
				if(y < minY) minY = y;
				if(y > maxY) maxY = y;
				if(z < minZ) minZ = z;
				if(z > maxZ) maxZ = z;
				vertices.push_back(new float[3]{x, y, z});
			}else if(Utils::stringStartsWith("vt ", line)){
				std::vector<std::string> strList;
				Utils::splitString(line, ' ', &strList);
				textureCoordinates.push_back(new float[2]{
						(float) atof(strList[1].c_str()),
						1 - (float) atof(strList[2].c_str())
				});
			}else if(Utils::stringStartsWith("vn ", line)){
				std::vector<std::string> strList;
				Utils::splitString(line, ' ', &strList);
				normals.push_back(new float[3]{
						(float) atof(strList[1].c_str()),
						(float) atof(strList[2].c_str()),
						(float) atof(strList[3].c_str())
				});
			}else if(Utils::stringStartsWith("f ", line)){
				std::vector<std::string> strList;
				Utils::splitString(line, ' ', &strList);
				std::vector<std::string> vertex1List;
				std::vector<std::string> vertex2List;
				std::vector<std::string> vertex3List;
				Utils::splitString(strList[1], '/', &vertex1List);
				Utils::splitString(strList[2], '/', &vertex2List);
				Utils::splitString(strList[3], '/', &vertex3List);
				short index1 = (short) atoi(vertex1List[0].c_str());
				short index2 = (short) atoi(vertex2List[0].c_str());
				short index3 = (short) atoi(vertex3List[0].c_str());
				if(newFace){
					lastFaces[0] = index1;
					lastFaces[1] = index2;
					lastFaces[2] = index3;
					if(std::find(verticesFoundSoFar.begin(), verticesFoundSoFar.end(), index1) != verticesFoundSoFar.end()){
						vertices.push_back(vertices[index1 - 1]);
						index1 = (short) vertices.size();
					}else{
						verticesFoundSoFar.push_back(index1);
					}
					if(std::find(verticesFoundSoFar.begin(), verticesFoundSoFar.end(), index2) != verticesFoundSoFar.end()){
						vertices.push_back(vertices[index2 - 1]);
						index2 = (short) vertices.size();
					}else{
						verticesFoundSoFar.push_back(index2);
					}
					if(std::find(verticesFoundSoFar.begin(), verticesFoundSoFar.end(), index3) != verticesFoundSoFar.end()){
						vertices.push_back(vertices[index3 - 1]);
						index3 = (short) vertices.size();
					}else{
						verticesFoundSoFar.push_back(index3);
					}
					lastFacesNewValue[0] = index1;
					lastFacesNewValue[1] = index2;
					lastFacesNewValue[2] = index3;
				}else{
					int ind = 0;
					bool flag = false;
					for(int i = 0; i < 3; i++){
						if(index1 == lastFaces[i]){
							flag = true;
							ind = i;
							break;
						}
					}
					if(!flag){
						if(std::find(verticesFoundSoFar.begin(), verticesFoundSoFar.end(), index1) != verticesFoundSoFar.end()){
							vertices.push_back(vertices[index1 - 1]);
							index1 = (short) vertices.size();
						}else{
							verticesFoundSoFar.push_back(index1);
						}
					}else{
						index1 = lastFacesNewValue[ind];
					}
					flag = false;
					for(int i = 0; i < 3; i++){
						if(index2 == lastFaces[i]){
							flag = true;
							ind = i;
							break;
						}
					}
					if(!flag){
						if(std::find(verticesFoundSoFar.begin(), verticesFoundSoFar.end(), index2) != verticesFoundSoFar.end()){
							vertices.push_back(vertices[index2 - 1]);
							index2 = (short) vertices.size();
						}else{
							verticesFoundSoFar.push_back(index2);
						}
					}else{
						index2 = lastFacesNewValue[ind];
					}
					flag = false;
					for(int i = 0; i < 3; i++){
						if(index3 == lastFaces[i]){
							flag = true;
							ind = i;
							break;
						}
					}
					if(!flag){
						if(std::find(verticesFoundSoFar.begin(), verticesFoundSoFar.end(), index3) != verticesFoundSoFar.end()){
							vertices.push_back(vertices[index3 - 1]);
							index3 = (short) vertices.size();
						}else{
							verticesFoundSoFar.push_back(index3);
						}
					}else{
						index3 = lastFacesNewValue[ind];
					}
				}
				newFace = !newFace;
				faces.push_back(new short[9]{
						index1,
						(short) atoi(vertex1List[1].c_str()),
						(short) atoi(vertex1List[2].c_str()),
						index2,
						(short) atoi(vertex2List[1].c_str()),
						(short) atoi(vertex2List[2].c_str()),
						index3,
						(short) atoi(vertex3List[1].c_str()),
						(short) atoi(vertex3List[2].c_str())
				});
			}
		}

		*vbo = (GLfloat*) calloc(static_cast<size_t>(8 * faces.size() * 3), sizeof(GLfloat));
		*ibo = (short*) calloc(static_cast<size_t>(faces.size() * 3), sizeof(short));

		for(size_t i = 0; i < faces.size(); i++){
			(*ibo)[i * 3] = (short) (faces[i][0] - 1);
			(*vbo)[(int) (*ibo)[i * 3] * 8] = vertices[(int) faces[i][0] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3] * 8 + 1] = vertices[(int) faces[i][0] - 1][1];
			(*vbo)[(int) (*ibo)[i * 3] * 8 + 2] = vertices[(int) faces[i][0] - 1][2];
			(*vbo)[(int) (*ibo)[i * 3] * 8 + 3] = normals[(int) faces[i][2] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3] * 8 + 4] = normals[(int) faces[i][2] - 1][1];
			(*vbo)[(int) (*ibo)[i * 3] * 8 + 5] = normals[(int) faces[i][2] - 1][2];
			(*vbo)[(int) (*ibo)[i * 3] * 8 + 6] = textureCoordinates[(int) faces[i][1] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3] * 8 + 7] = textureCoordinates[(int) faces[i][1] - 1][1];
			(*ibo)[i * 3 + 1] = (short) (faces[i][3] - 1);
			(*vbo)[(int) (*ibo)[i * 3 + 1] * 8] = vertices[(int) faces[i][3] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3 + 1] * 8 + 1] = vertices[(int) faces[i][3] - 1][1];
			(*vbo)[(int) (*ibo)[i * 3 + 1] * 8 + 2] = vertices[(int) faces[i][3] - 1][2];
			(*vbo)[(int) (*ibo)[i * 3 + 1] * 8 + 3] = normals[(int) faces[i][5] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3 + 1] * 8 + 4] = normals[(int) faces[i][5] - 1][1];
			(*vbo)[(int) (*ibo)[i * 3 + 1] * 8 + 5] = normals[(int) faces[i][5] - 1][2];
			(*vbo)[(int) (*ibo)[i * 3 + 1] * 8 + 6] = textureCoordinates[(int) faces[i][4] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3 + 1] * 8 + 7] = textureCoordinates[(int) faces[i][4] - 1][1];
			(*ibo)[i * 3 + 2] = (short) (faces[i][6] - 1);
			(*vbo)[(int) (*ibo)[i * 3 + 2] * 8] = vertices[(int) faces[i][6] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3 + 2] * 8 + 1] = vertices[(int) faces[i][6] - 1][1];
			(*vbo)[(int) (*ibo)[i * 3 + 2] * 8 + 2] = vertices[(int) faces[i][6] - 1][2];
			(*vbo)[(int) (*ibo)[i * 3 + 2] * 8 + 3] = normals[(int) faces[i][8] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3 + 2] * 8 + 4] = normals[(int) faces[i][8] - 1][1];
			(*vbo)[(int) (*ibo)[i * 3 + 2] * 8 + 5] = normals[(int) faces[i][8] - 1][2];
			(*vbo)[(int) (*ibo)[i * 3 + 2] * 8 + 6] = textureCoordinates[(int) faces[i][7] - 1][0];
			(*vbo)[(int) (*ibo)[i * 3 + 2] * 8 + 7] = textureCoordinates[(int) faces[i][7] - 1][1];
		}

		*width = maxX - minX;
		*height = maxY - minY;
		*depth = maxZ - minZ;

		*vboLength = 8 * (int) faces.size() * 3;
		*iboLength = (int) faces.size() * 3;
	}
}