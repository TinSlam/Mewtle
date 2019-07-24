#include <PrecompiledHeaders.h>

#include "Label.h"

#include "Mewtle/Core/MyGLRenderer.h"
#include "Mewtle/ResourceManager/Model/ModelPremade.h"

namespace Mewtle{
	Label::Label(int id, Texture* texture, float x, float y, float width, float height, float rot) : Entity(id, Model3D::getModel(ModelPremade::MODEL_SQUARE), texture, x, y, 0, 0, 0, rot, width, height, 0){
	
	}

	void Label::render() {
		render(1);
	}

	void Label::render(float alpha) {
		MyGLRenderer::drawLabel(this, alpha);
	}

	bool Label::mouseOver(double x, double y){
		x -= this->x + this->width / 2;
		y -= this->y + this->height / 2;
		double tempX = x * cos(rotZ) - y * sin(rotZ);
		double tempY = x * sin(rotZ) + y * cos(rotZ);
		tempX += this->x + this->width / 2;
		tempY += this->y + this->height / 2;
		if(tempX >= this->x &&
			tempX <= this->x + this->width &&
			tempY >= this->y &&
			tempY <= this->y + this->height) return true;
		return false;
	}
}