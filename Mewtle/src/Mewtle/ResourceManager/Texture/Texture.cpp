#include <PrecompiledHeaders.h>

#include "Texture.h"

#include "Mewtle/Core/MyGLRenderer.h"

namespace Mewtle{
	std::map<int, Texture*> Texture::textures;

	GLuint Texture::getId(){
		return texture;
	}

	int Texture::getTextureId(){
		return id;
	}

	Texture::Texture(int id, const char *path){
		texture = MyGLRenderer::loadTexture(path);
		this->id = id;
	}

	void Texture::createTexture(int id, const char* path){
		textures[id] = new Texture(id, path);
	}

	Texture* Texture::getTexture(int id){
		return textures[id];
	}

	void Texture::deleteTextures(){
		for(auto it = textures.begin(); it != textures.end(); it++){
			deleteTexture(it->second);
		}
	}

	void Texture::deleteTexture(Texture* texture){
		GLuint id = texture->getId();
		glDeleteTextures(1, &id);
		delete(texture);
	}
}