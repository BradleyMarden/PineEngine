/*
	Two types of events. Engine events, and custom events.

	Engine events, predefined. e.g, mouse button down, key down, game paused.

	custom events, player dead, player jump, player collision.




*/

#pragma once
#include "Core.h"
#include "Event.h"
#include <vector>


namespace Pine {

	
	
	struct handler
	{
		
		void(*func)();
		int id;
		
	};

	struct PineEvent
	{
		PineEvent(std::string p_Name) 
		{
			eventName = p_Name;
		
		}
		int eventId;
		std::string eventName;
		std::vector<handler*> handles;


	};
	class EventSystem
	{
	public:
		EventSystem();
		~EventSystem();
		
		int Register(PineEvent* event) //Takes in the event you want to register, returns id for the event
		{
			m_Events.insert({ event->eventName,event});
			int tempId = id;
			id++;
			return tempId;
		}
	
		 

		
		template<class T>
		void Subscribe(std::string eventName, void(T::*func)())//function you want to run when evnt is called, and the event you want to sub to
		{
			auto it = m_Events.find(eventName);
			handler* h = new handler();
			h->func = func;//need to figure out how to store the func
			h->id = 0;
			it->second->handles.push_back(h);
			
		}
		 void Publish(std::string p_eventName) 
		{
			auto it = m_Events.find(p_eventName);

			for each(handler* var in it->second->handles)
			{
				var->func;

			}

		


		}
		 int EventList() 
		{
		
		}
//void UnSubscribe();//function evnt is called on, and the event you want to un sub to




	private:
		  std::unordered_map<std::string, PineEvent*> m_Events;
		  int id;
	};
}