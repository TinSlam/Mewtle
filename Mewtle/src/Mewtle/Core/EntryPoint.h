#pragma once

#include "Mewtle/Core/Game.h"
#include "Mewtle/Core/Engine.h"

#ifdef MTL_PLATFORM_WINDOWS
	int main(int argc, char** argv){
		Mewtle::Game::initRenderer(Mewtle::init, Mewtle::tick, Mewtle::render, Mewtle::createInitialState());

		return 0;
	}
#endif