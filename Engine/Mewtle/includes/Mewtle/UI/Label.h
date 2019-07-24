#ifndef MEWTLEENGINE_LABEL_H
#define MEWTLEENGINE_LABEL_H

#include "Mewtle/GameElements/Entity.h"

namespace Mewtle{
	class Label : public Entity{
	public :
		Label(int id, Texture* texture, float left, float top, float width, float height, float rotZ);
		void render();
		void render(float alpha);
		bool mouseOver(double x, double y);
	};
}

#endif //MEWTLEENGINE_LABEL_H
