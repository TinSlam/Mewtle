#ifndef MEWTLEENGINE_MODEL3D_H
#define MEWTLEENGINE_MODEL3D_H

#include "Mewtle/ResourceManager/Texture/Material.h"

namespace Mewtle{
	class Model3D{
		private :
			GLuint vboId = 0;
			GLuint iboId = 0;
			int iboLength = 0;
			int vboLength = 0;
			GLfloat* vbo = nullptr;
			short* ibo = nullptr;
			float width = 0;
			float height = 0;
			float depth = 0;
			bool textured = false;
			Material* material = nullptr;

		public :
			int getIboLength();
			int getVboLength();
			GLuint* getVboId();
			GLuint* getIboId();
			float getWidth();
			float getHeight();
			float getDepth();
			bool isTextured();
			Material* getMaterial();

			static std::map<const int, Model3D*> models;

			static Model3D* getModel(int id);
			static void createModel(int, const char*);
			static void mapModel(int, const char*);
			static void deleteModels();
			static void deleteModel(Model3D*);

			explicit Model3D(const char *path);
			~Model3D();
	};
}

#endif //MEWTLEENGINE_MODEL3D_H
