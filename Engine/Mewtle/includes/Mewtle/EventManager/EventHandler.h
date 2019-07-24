#pragma once

#include "Event.h"

namespace Mewtle{
	class EventHandler{
		private : 
			std::queue<Event*>* queue = nullptr;
			std::mutex lock;

		public :
			EventHandler();
			~EventHandler();
			void dispatchEvents();
			void scheduleEvent(Event* event);
			void cancelEvent(Event* event);
			void resumeEvent(Event* event);
	};
}

