#pragma once

#include "Mewtle/UI/GUIElement.h"
#include "Mewtle/UI/Label.h"
#include "Mewtle/ResourceManager/Texture/Texture.h"

namespace Mewtle{
	class Button : public GUIElement{
	protected :
		Label* label = nullptr;

	private :
		Texture* texture = nullptr;
		Texture* onHoverTexture = nullptr;

		static std::vector<Button*> buttons;

	public :
		Button(int id, Texture* texture, Texture* onHover);
		~Button();

		virtual void onClick() = 0;

		virtual bool mouseLeftReleased(double x, double y) = 0;
		virtual bool mouseLeftPressed(double x, double y) = 0;
		virtual bool mouseRightReleased(double x, double y) = 0;
		virtual bool mouseRightPressed(double x, double y) = 0;
		virtual void mouseOnHover(double x, double y) = 0;
		virtual bool hovered(double x, double y) = 0;

		virtual void tick() = 0;
		virtual void render() = 0;

		static void renderAll();
		static bool checkMouseLeftReleased(double x, double y);
		static bool checkMouseLeftPressed(double x, double y);
		static bool checkMouseRightPressed(double x, double y);
		static bool checkMouseRightReleased(double x, double y);
	};
}