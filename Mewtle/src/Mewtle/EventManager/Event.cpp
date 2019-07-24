#include "PrecompiledHeaders.h"

#include "Event.h"

namespace Mewtle{
	Event::Event(int id, std::string* name){
		this->id = id;
		this->name = name;
	}

	Event::~Event(){
		delete(name);
	}

	void Event::setCancelled(bool value){
		cancelled = value;
	}
}