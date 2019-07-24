#include <PrecompiledHeaders.h>

#include "Textbox.h"

#include "Mewtle/Core/MyGLRenderer.h"
#include "Mewtle/Utils/Utils.h"

namespace Mewtle{
	Textbox::Textbox(int id, std::string text, float left, float top, float right, float bottom, int size, float red, float green, float blue, ALIGNMENT alignment, bool multiLine, bool stretchVerticallyToFitBox) : GUIElement(id){
		this->text = new std::string(std::move(text));
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		this->size = size;
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alignment = alignment;
		this->multiLine = multiLine;
		this->verticalStretchToFitBox = stretchVerticallyToFitBox;

		init();
	}

	Textbox::~Textbox(){
		delete(this->text);
	}

	void Textbox::setText(std::string text){
		delete(this->text);
		this->text = new std::string(std::move(text));

		init();
	}

	void Textbox::init(){
		auto* size = new float[2];
		std::vector<float> widths;
		std::vector<float> heights;
		float width, height;
		int linesCounter = 1;

		do{
			Utils::breakDownString(*text, linesCounter, &lines);
			width = 0;
			height = 0;
			widths.clear();
			heights.clear();
			for(std::string str : lines){
				MyGLRenderer::getTextBounds(str, this->size, size);
				widths.push_back(size[0]);
				heights.push_back(size[1]);
				width = Utils::max(width, size[0]);
				height += size[1];
			}
			if(verticalStretchToFitBox) height += this->size / 3.0f * lines.size();
			this->size--;
			if(this->multiLine) linesCounter++;
		}while(width > right - left || height > bottom - top);
		this->size++;

		float maxHeight = bottom - top;
		float yOffset = top + maxHeight / (lines.size() + 1);
		if(!verticalStretchToFitBox) yOffset = top - this->size / 3.0f;
		for(size_t i = 0; i < lines.size(); i++){
			switch(alignment){
				case CENTER :
					x.push_back((left + right) / 2 - widths[i] / 2);
					break;

				case LEFT :
					x.push_back(left);
					break;

				case RIGHT :
					x.push_back(right - widths[i]);
					break;
			}
			if(verticalStretchToFitBox){
				y.push_back(yOffset);
				yOffset += maxHeight / (lines.size() + 1);
			}else{
				yOffset += heights[i];
				y.push_back(yOffset);
			}
		}
	}

	void Textbox::render(){
		for(size_t i = 0; i < lines.size(); i++){
			MyGLRenderer::drawText(lines[i], Utils::getWidthFromPixels((int) x[i]) / Utils::getScreenRatio(), Utils::getHeightFromPixels((int) y[i]), size, red, green, blue);
		}
	}

	void Textbox::mouseOnHover(double x, double y){

	}

	bool Textbox::mouseLeftReleased(double x, double y){
		return false;
	}

	bool Textbox::mouseLeftPressed(double x, double y){
		return false;
	}

	bool Textbox::mouseRightReleased(double x, double y){
		return false;
	}

	bool Textbox::mouseRightPressed(double x, double y){
		return false;
	}
}