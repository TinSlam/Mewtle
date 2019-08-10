#include <MewtlePreCompiledHeaders.h> // Add this line at the beginning of every cpp file.

#include "Mewtle.h" // The engine interface.

#include <Mewtle/Core/EntryPoint.h>

Mewtle::State* Mewtle::createInitialState(){
	// Return your initial state.
	return nullptr;
}

void Mewtle::init(){
	MTL_INFO("Client init.");
}

void Mewtle::loadModels(){
	MTL_INFO("Client load models.");
}

void Mewtle::loadTextures(){
	MTL_INFO("Client load textures.");
}

void Mewtle::tick(){
	MTL_INFO("Tick...");
}

void Mewtle::render(){
	MTL_INFO("Render");
}