#ifndef MEWTLEENGINE_GUIELEMENT_H
#define MEWTLEENGINE_GUIELEMENT_H

namespace Mewtle{
	class GUIElement{
	private :

	protected :
		int id = 0;
		bool active = false;

	public :
		static std::map<int, GUIElement*> guiElements;
		explicit GUIElement(int);
		~GUIElement();
		virtual void render() = 0;
		static void renderAll();
		static bool checkMouseLeftReleased(double x, double y);
		static bool checkMouseLeftPressed(double x, double y);
		static bool checkMouseRightPressed(double x, double y);
		static bool checkMouseRightReleased(double x, double y);

		virtual bool mouseLeftPressed(double x, double y) = 0;
		virtual bool mouseLeftReleased(double x, double y) = 0;
		virtual bool mouseRightReleased(double x, double y) = 0;
		virtual bool mouseRightPressed(double x, double y) = 0;
		virtual void mouseOnHover(double x, double y) = 0;
	};
}

#endif //MEWTLEENGINE_GUIELEMENT_H
