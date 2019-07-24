#include <PrecompiledHeaders.h>

#include "ModelPremade.h"

#include "Mewtle/Core/Game.h"

namespace Mewtle{
	int ModelPremade::MODEL_SQUARE = 0;
	int ModelPremade::MODEL_CUBE = 0;

	void ModelPremade::loadModels(){
		MODEL_SQUARE = Game::createModel("assets/models/premade/square.obj");
		MODEL_CUBE = Game::createModel("assets/models/premade/block.obj");
	}
}
