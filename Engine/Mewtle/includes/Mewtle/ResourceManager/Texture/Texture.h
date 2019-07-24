#ifndef MEWTLEENGINE_TEXTURE_H
#define MEWTLEENGINE_TEXTURE_H

namespace Mewtle{
	class Texture{
		GLuint texture = 0;
		int id = 0;

		public :
			GLuint getId();
			int getTextureId();

			static std::map<int, Texture*> textures;

			static void createTexture(int, const char*);
			static Texture* getTexture(int);
			static void deleteTextures();
			static void deleteTexture(Texture*);

		explicit Texture(int id, const char *path);
	};
}

#endif //MEWTLEENGINE_TEXTURE_H
