#pragma once

#include "Mewtle/UI/Button/Button.h"

namespace Mewtle{
	class ButtonRectangle : public Button{
	private :
		int x = 0, y = 0;
		int width = 0, height = 0;
		std::function<void ()> onClickFunction;

	public:
		ButtonRectangle(int id, Texture* texture, Texture* onHover, int x, int y, int width, int height, std::function<void ()> onClickFunction);
		~ButtonRectangle();

		void onClick();

		bool mouseLeftReleased(double x, double y);
		bool mouseLeftPressed(double x, double y);
		bool mouseRightReleased(double x, double y);
		bool mouseRightPressed(double x, double y);
		void mouseOnHover(double x, double y);
		bool hovered(double x, double y);

		void tick();
		void render();

		int getLeft();
		int getTop();
		int getRight();
		int getBottom();
		int getWidth();
		int getHeight();
		int getCenterX();
		int getCenterY();
	};
}