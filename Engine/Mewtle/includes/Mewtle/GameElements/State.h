#pragma once

namespace Mewtle{
	class State{
		public :
			virtual void init() = 0;
			virtual void tick() = 0;
			virtual void render() = 0;
			virtual void keyboardInput() = 0;
			virtual void mouseLeftPressed(double, double) = 0;
			virtual void mouseLeftReleased(double, double) = 0;
			virtual void mouseRightPressed(double, double) = 0;
			virtual void mouseRightReleased(double, double) = 0;
	};
}