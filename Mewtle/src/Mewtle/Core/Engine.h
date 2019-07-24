
#include "Mewtle/Core/Game.h"

namespace Mewtle{
	// To be defined in client.
	void init();
	void tick();
	void render();
	State* createInitialState();
	void loadModels();
	void loadTextures();
}