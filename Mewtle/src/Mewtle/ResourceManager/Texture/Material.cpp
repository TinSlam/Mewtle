#include "PrecompiledHeaders.h"

#include "Material.h"

#include "Mewtle/Core/Game.h"

namespace Mewtle{
	std::vector<Material*> Material::allMaterials;
	
	Material::Material(std::map<int, std::string>* materialsPath, std::string directoryPath, GLuint* materials, int materialCount, int* materialsIndices){
		this->materials = materials;
		this->materialCount = materialCount;
		this->materialsIndices = materialsIndices;

		bool* visited = new bool[materialCount];
		for(int i = 0; i < materialCount; i++)
			visited[i] = false;
		for(auto it = materialsPath->begin(); it != materialsPath->end(); it++){
			int textureID = Game::createTexture((directoryPath + (it->second)).c_str());
			textureID = Texture::getTexture(textureID)->getId();
			for(int i = 0; i < materialCount; i++){
				if(materials[i] == it->first && !visited[i]){
					visited[i] = true;
					materials[i] = textureID;
				}
			}
		}
		delete(materialsPath);
		delete(visited);

		allMaterials.push_back(this);
	}
	
	void Material::deleteMaterials(){
		for(auto it = allMaterials.begin(); it != allMaterials.end(); it++){
			delete(*it);
		}
	}
	
	Material::~Material(){
		for(int i = 0; i < materialCount; i++)
			glDeleteTextures(1, &(materials[i]));
		delete(materials);
		delete(materialsIndices);
	}
	
	int Material::getMatLength(int index){
		return materialsIndices[index + 1] - materialsIndices[index];
	}
	
	int Material::getMatStartIndex(int index){
		return materialsIndices[index];
	}
	
	GLuint* Material::getMaterials(){
		return materials;
	}
	
	int Material::getMaterialCount(){
		return materialCount;
	}
}