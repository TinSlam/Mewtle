#include <PrecompiledHeaders.h>

#include "ButtonRectangle.h"

#include "Mewtle/Core/Game.h"
#include "Mewtle/Utils/Utils.h"

namespace Mewtle{
	ButtonRectangle::ButtonRectangle(int id, Texture* texture, Texture* onHover, int x, int y, int width, int height, std::function<void ()> onClickFunction) : Button(id, texture, onHover){
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		this->onClickFunction = onClickFunction;

		label = new Label(Game::generateId(), texture, (float) x, (float) y, (float) width, (float) height, 0);
	}


	ButtonRectangle::~ButtonRectangle(){

	}

	void ButtonRectangle::tick(){

	}

	void ButtonRectangle::render(){
		label->render();
	}

	bool ButtonRectangle::hovered(double x, double y){
		return Utils::isInRect((float) x, (float) y, (float) this->x, (float) this->y, (float) this->x + (float) this->width, (float) this->y + (float) this->height);
	}

	void ButtonRectangle::onClick(){

	}

	void ButtonRectangle::mouseOnHover(double x, double y){

	}

	bool ButtonRectangle::mouseLeftReleased(double x, double y){
		if(hovered(x, y)){
			onClickFunction();
			return true;
		}else{
			return false;
		}
	}

	bool ButtonRectangle::mouseLeftPressed(double x, double y){
		if(hovered(x, y)){
			return true;
		}else{
			return false;
		}
	}

	bool ButtonRectangle::mouseRightReleased(double x, double y){
		return false;
	}

	bool ButtonRectangle::mouseRightPressed(double x, double y){
		return false;
	}

	int ButtonRectangle::getLeft(){
		return x;
	}

	int ButtonRectangle::getTop(){
		return y;
	}

	int ButtonRectangle::getWidth(){
		return width;
	}

	int ButtonRectangle::getHeight(){
		return height;
	}

	int ButtonRectangle::getCenterX(){
		return x + width / 2;
	}

	int ButtonRectangle::getCenterY(){
		return y + height / 2;
	}

	int ButtonRectangle::getRight(){
		return x + width;
	}

	int ButtonRectangle::getBottom(){
		return y + height;
	}
}