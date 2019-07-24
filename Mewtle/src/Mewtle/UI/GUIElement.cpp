#include <PrecompiledHeaders.h>

#include "GUIElement.h"

namespace Mewtle{
	std::map<int, GUIElement*> GUIElement::guiElements;

	GUIElement::GUIElement(int id){
		this->id = id;

		guiElements[id] = this;
	}

	GUIElement::~GUIElement() {
		guiElements.erase(id);
	}

	void GUIElement::renderAll(){
		for(auto &pair : guiElements){
			pair.second->render();
		}
	}

	bool GUIElement::checkMouseLeftPressed(double x, double y){
		for(auto &pair : guiElements){
			if(pair.second->mouseLeftPressed(x, y)) return true;
		}
		return false;
	}

	bool GUIElement::checkMouseLeftReleased(double x, double y){
		for(auto &pair : guiElements){
			if(pair.second->mouseLeftReleased(x, y)) return true;
		}
		return false;
	}

	bool GUIElement::checkMouseRightPressed(double x, double y){
		for(auto &pair : guiElements){
			if(pair.second->mouseRightPressed(x, y)) return true;
		}
		return false;
	}

	bool GUIElement::checkMouseRightReleased(double x, double y){
		for(auto &pair : guiElements){
			if(pair.second->mouseRightReleased(x, y)) return true;
		}
		return false;
	}
}