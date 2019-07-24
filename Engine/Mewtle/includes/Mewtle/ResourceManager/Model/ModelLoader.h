#ifndef MEWTLEENGINE_MODELLOADER_H
#define MEWTLEENGINE_MODELLOADER_H

namespace Mewtle{
	class ModelLoader {
	public :
		static void loadObj(const char*, GLfloat**, int*, short**, int*, float*, float*, float*);
	};
}

#endif //MEWTLEENGINE_MODELLOADER_H