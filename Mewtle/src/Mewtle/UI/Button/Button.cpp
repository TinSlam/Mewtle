#include <PrecompiledHeaders.h>

#include "Button.h"

namespace Mewtle{
	std::vector<Button*> Button::buttons;

	Button::Button(int id, Texture* texture, Texture* onHover) : GUIElement(id){
		buttons.push_back(this);

		this->texture = texture;
		this->onHoverTexture = onHover;
	}


	Button::~Button(){

	}

	void Button::renderAll(){
		for(auto it = buttons.begin(); it != buttons.end(); it++){
			(*it)->render();
		}
	}

	bool Button::checkMouseLeftPressed(double x, double y){
		for(auto it = buttons.begin(); it != buttons.end(); it++){
			if((*it)->mouseLeftPressed(x, y)){
				(*it)->label->setTexture((*it)->onHoverTexture);
				return true;
			}
		}
		return false;
	}

	bool Button::checkMouseLeftReleased(double x, double y){
		for(auto it = buttons.begin(); it != buttons.end(); it++){
			(*it)->label->setTexture((*it)->texture);
			if((*it)->mouseLeftReleased(x, y)) return true;
		}
		return false;
	}

	bool Button::checkMouseRightPressed(double x, double y){
		for(auto it = buttons.begin(); it != buttons.end(); it++){
			if((*it)->mouseRightPressed(x, y)) return true;
		}
		return false;
	}

	bool Button::checkMouseRightReleased(double x, double y){
		for(auto it = buttons.begin(); it != buttons.end(); it++){
			if((*it)->mouseRightReleased(x, y)) return true;
		}
		return false;
	}
}