#include "PrecompiledHeaders.h"

#include "EventHandler.h"

namespace Mewtle{
	EventHandler::EventHandler(){
		queue = new std::queue<Event*>();
	}

	EventHandler::~EventHandler(){
		lock.lock();
		while(!queue->empty()){
			Event* event = queue->front();
			queue->pop();
			delete(event);
		}
		lock.unlock();
		delete(queue);
	}

	void EventHandler::dispatchEvents(){
		lock.lock();
		while(!queue->empty()){
			Event* event = queue->front();
			queue->pop();
			if(!event->perform()){
				queue->push(event);
			}
		}
		lock.unlock();
	}

	void EventHandler::scheduleEvent(Event* event){
		lock.lock();
		queue->push(event);
		lock.unlock();
	}

	void EventHandler::cancelEvent(Event* event){
		event->setCancelled(true);
	}

	void EventHandler::resumeEvent(Event* event){
		event->setCancelled(false);
	}
}