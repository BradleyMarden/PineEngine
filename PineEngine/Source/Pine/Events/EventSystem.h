#pragma once
//#include "Event.h"
#include <vector>
#include <assert.h>
#include <iostream>
#include <functional>
#include "Log.h"
#include <iostream>
#include "Input.h"
namespace Pine {
#define SETBIT(x) (1 << x) //this is set to 4 bytes, we could use a bitset for a more controlled amount of bits.
							//for now, this works fine.

//used in event childeren, saves repeating code.
#define SET_EVENT_TYPE(EType)	static EventType GetStaticType() {return EventType::EType;}\
								virtual EventType GetEventType() const override {return GetStaticType();}

#define SET_CATEGORY_TYPE(CType) virtual int GetCatFlags() const override{return CType;}\
								virtual int GetSizeOfCatFlags() const override{return sizeof(CType);}



	enum class EventType //define the type of event
	{
		None = 0,
		WindowResize, WindowClose, WindowMinimize, WindowMoved, WindowFocus, WindowLostFocus,
		KeyDown, KeyUp, KeyHold,
		MouseButtonDown, MouseButtonUp, MouseMoved,
		MiddleMouseScroll

	};

	enum  EventCategory //define the category of event, needs to be a 
							//bitset as an event can be more than one category
	{
		None = 0,
		KeyboardEvent = SETBIT(0),	//this equates to '0000 0000 0000 0000 0000 0000 0000 0001' 32 bits or 4 bytes. The size of a int
		MouseEvent =	SETBIT(1),	//this equates to '0000 0000 0000 0000 0000 0000 0000 0010'
		InputEvent =	SETBIT(2),	//this equates to '0000 0000 0000 0000 0000 0000 0000 0100'
		WindowEvent =	SETBIT(3),	//this equates to '0000 0000 0000 0000 0000 0000 0000 1000'
		GameEvent =		SETBIT(4)	//this equates to '0000 0000 0000 0000 0000 0000 0001 0000'
	};


	//base event struct
	struct PEvent
	{

		virtual int			GetCatFlags()			const = 0;
		virtual EventType	GetEventType()			const = 0;
		virtual int			GetSizeOfCatFlags()		const = 0;//debug only. Returns the size of the category bitset

		bool		IsInCategory(EventCategory cat){return GetCatFlags()& cat;}
		bool		is_Handled = false;
	private:
		int			s_Category = 0;

	};


	using EventCallbackFn = std::function<void(PEvent&)>;

	class EventSystem
	{
	public:

		static void init()
		{
			m_Head = 0;
			m_Tail = 0;
			m_NumberPendingEvents = 0;
		}

		static void PublishEvent(PEvent* e)
	{
			assert((m_Tail+1) % m_MaxPendingEvents != m_Head);
			//create new data event, pass controll of ptr
			data* d = new data(e);

			//pass data event to pending events list
			m_PendingEvents[m_Tail] = d;

			//increment position
			m_Tail = (m_Tail + 1) % m_MaxPendingEvents;
			//m_NumberPendingEvents++;
		}

		//Pass the fucntion that you would like the events to be recieved by. NOTE: the function must take an event& as a parameter.
		inline static void RegisterEventCallback(EventCallbackFn fn)
		{
			m_Func = fn;
		}


		//fix loop, deletes
		inline static void Run()
		{
			if (m_Head == m_Tail) { return; }


			 int i =0;
			//check for repeat events, for ex a key hold. If it is held, delete the old event, and replace with new one with the isHeld bool set to true,

			//remove loop based event system, to on call event system
			for (data* d : m_PendingEvents) 
			{
				if (d != nullptr)
				{
					if (d->GetEvent().is_Handled)
					{
						m_PendingEvents[i] = nullptr;
						delete d;
						//handle tail update here
						//m_NumberPendingEvents--;
						m_Head = (m_Head + 1) % m_MaxPendingEvents;
						return;
					}
					//works but janky. Requires user to seperate out the event types. I need to handle that. Works with static cast too.
					m_Func(dynamic_cast<decltype(d->GetEvent())>(d->GetEvent()));
				}
				i++;
			}
		}



	private:
		struct data
		{
			data(PEvent* p_Event) : m_Event(p_Event) {}
			~data() { delete m_Event; }//handle ptr deletion

			PEvent& GetEvent()		 { return *m_Event; }//needs to return reference to the event
		private:
			 PEvent* m_Event;
		};

		inline static int	m_Head;
		inline static int	m_Tail;
		inline static const int			m_MaxPendingEvents = 16;
		inline static EventCallbackFn	m_Func;
		inline static int		m_NumberPendingEvents;
		inline static data*		m_PendingEvents[m_MaxPendingEvents];


	};



	//Event takes care of itself, when created with a pointer
	struct WindowResizeEvent : PEvent
	{

		WindowResizeEvent(unsigned int width, unsigned int height) : x(width), y(height)
		{
			EventSystem::PublishEvent(this);
		}

		unsigned int GetWidth() const { return x; }
		unsigned int GetHeight() const { return y; }

		SET_EVENT_TYPE(WindowResize);
		SET_CATEGORY_TYPE(WindowEvent);

	private:
		int x = 100;
		int y = 100;
	};

	struct MouseButtonDownEvent : PEvent
	{
		MouseButtonDownEvent(int p_X, int p_Y, Input::MouseButtons p_Button, bool p_Held) : x(p_X), y(p_Y),l_button(p_Button), held(p_Held)
		{
			EventSystem::PublishEvent(this);
		}

		int GetX() const { return x; }
		int GetY() const { return y; }
		Input::MouseButtons GetButtonDown() const { return l_button; }

		bool IsHeld() const { return held; }

		SET_EVENT_TYPE(MouseButtonDown);
		SET_CATEGORY_TYPE(WindowEvent | MouseEvent | InputEvent);

	private:
		int x;
		int y;
		bool held;
		Input::MouseButtons l_button;


	};
}

//using EventCallbackFn = std::function<void(Event&)>;

//in window creation create a function that sets the callback function that should be run when a event occurs.
//This will be set when the window is created, after this all events that are created will be passed to this function in application
//we can then distribute event types to different fucntions. 

//going back where the sdl event occurs, each sdl event will need to pass a struct with the screen data
