#ifndef MEWTLEENGINE_TEXTBOX_H
#define MEWTLEENGINE_TEXTBOX_H

#include "Mewtle/UI/GUIElement.h"

namespace Mewtle{
	class Textbox : public GUIElement{
	public :
		enum ALIGNMENT{CENTER, LEFT, RIGHT};

	private :
		std::vector<std::string> lines;
		std::string* text = nullptr;
		float left = 0, top = 0, right = 0, bottom = 0;
		int size = 0;
		float red = 0, green = 0, blue = 0;
		bool multiLine;
		bool verticalStretchToFitBox;
		std::vector<float> x;
		std::vector<float> y;
		ALIGNMENT alignment;

		void init();


	public :
		Textbox(int, std::string text, float left, float top, float right, float bottom, int size, float red, float green, float blue, ALIGNMENT alignment, bool multiline, bool stretchToFitBox);
		~Textbox();
		void render() override;

		void setText(std::string text);

		bool mouseLeftReleased(double x, double y);
		bool mouseLeftPressed(double x, double y);
		bool mouseRightReleased(double x, double y);
		bool mouseRightPressed(double x, double y);
		void mouseOnHover(double x, double y);
	};
}

#endif //MEWTLEENGINE_TEXTBOX_H
