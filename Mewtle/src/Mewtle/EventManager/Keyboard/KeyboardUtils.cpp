#include <PrecompiledHeaders.h>

#include "KeyboardUtils.h"

namespace Mewtle{
	bool KeyboardUtils::up, KeyboardUtils::down, KeyboardUtils::right, KeyboardUtils::left;
	bool KeyboardUtils::leftControl, KeyboardUtils::rightControl;
	bool KeyboardUtils::space, KeyboardUtils::enter, KeyboardUtils::escape, KeyboardUtils::tab;
	bool KeyboardUtils::letters[26];
	bool KeyboardUtils::numbers[10];

	bool KeyboardUtils::getFlag(int key){
		switch(key){
		case GLFW_KEY_UP:
			return up;
			break;

		case GLFW_KEY_DOWN:
			return down;
			break;

		case GLFW_KEY_LEFT:
			return left;
			break;

		case GLFW_KEY_RIGHT:
			return right;
			break;

		case GLFW_KEY_LEFT_CONTROL:
			return leftControl;
			break;

		case GLFW_KEY_RIGHT_CONTROL:
			return rightControl;
			break;

		case GLFW_KEY_SPACE:
			return space;
			break;

		case GLFW_KEY_ENTER:
			return enter;
			break;

		case GLFW_KEY_ESCAPE:
			return escape;
			break;

		case GLFW_KEY_TAB:
			return tab;
			break;

		default:
			if(key >= GLFW_KEY_A && key <= GLFW_KEY_Z){
				key -= GLFW_KEY_A;
				return letters[key];
				break;
			}
			if(key >= GLFW_KEY_0 && key <= GLFW_KEY_9){
				key -= GLFW_KEY_0;
				return numbers[key];
			}
			break;
		}
		return false;
	}

	void KeyboardUtils::setFlag(int key, bool value){
		switch(key){
		case GLFW_KEY_UP:
			up = value;
			break;

		case GLFW_KEY_DOWN:
			down = value;
			break;

		case GLFW_KEY_LEFT:
			left = value;
			break;

		case GLFW_KEY_RIGHT:
			right = value;
			break;

		case GLFW_KEY_LEFT_CONTROL:
			leftControl = value;
			break;

		case GLFW_KEY_RIGHT_CONTROL:
			rightControl = value;
			break;

		case GLFW_KEY_SPACE:
			space = value;
			break;

		case GLFW_KEY_ENTER:
			enter = value;
			break;

		case GLFW_KEY_ESCAPE:
			escape = value;
			break;

		case GLFW_KEY_TAB:
			tab = value;
			break;

		default:
			if(key >= GLFW_KEY_A && key <= GLFW_KEY_Z){
				key -= GLFW_KEY_A;
				letters[key] = value;
				break;
			}
			if(key >= GLFW_KEY_0 && key <= GLFW_KEY_9){
				key -= GLFW_KEY_0;
				numbers[key] = value;
			}
			break;
		}
	}
}