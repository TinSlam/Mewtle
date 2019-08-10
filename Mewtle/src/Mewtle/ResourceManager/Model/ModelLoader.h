#ifndef MEWTLEENGINE_MODELLOADER_H
#define MEWTLEENGINE_MODELLOADER_H

namespace Mewtle{
	class ModelLoader {
	public :
		static void loadObj(const char*, GLfloat**, int*, short**, int*, float*, float*, float*);
		static void loadTexturedObj(const char* path, GLfloat** vbo, int* vboLength, short** ibo, int* iboLength, float* width, float* height, float* depth, int** materialsIndecies, int* materialsNumber);
	};
}

#endif //MEWTLEENGINE_MODELLOADER_H