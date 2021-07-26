#pragma once
#include <vector>
#include <assert.h>
#include <iostream>
#include <functional>
#include <iostream>
#include <iterator>

#include "Log.h"
#include "Input.h"
//#include "Event.h"

namespace Pine {

	//NEEDS TO BE MOVED INTO A BASE.CPP
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
		MiddleMouseScroll,
		NetworkPacketRecieve, NetworkPlayerConnected, NetworkPlayerDisconnected

	};

	enum  EventCategory //define the category of event, needs to be a 
						//bitset as an event can be more than one category
	{
		None = 0,
		KeyboardEvent = SETBIT(0),	//this equates to '0000 0000 0000 0000 0000 0000 0000 0001' 32 bits or 4 bytes. The size of a int
		MouseEvent =	SETBIT(1),	//this equates to '0000 0000 0000 0000 0000 0000 0000 0010'
		InputEvent =	SETBIT(2),	//this equates to '0000 0000 0000 0000 0000 0000 0000 0100'
		WindowEvent =	SETBIT(3),	//this equates to '0000 0000 0000 0000 0000 0000 0000 1000'
		GameEvent =		SETBIT(4),	//this equates to '0000 0000 0000 0000 0000 0000 0001 0000'
		NetworkEvent =  SETBIT(5)
	};


	//base event struct
	struct PEvent
	{

		virtual int			GetCatFlags()			const = 0;
		virtual EventType	GetEventType()			const = 0;
		virtual int			GetSizeOfCatFlags()		const = 0;//debug only. Returns the size of the category bitset
		bool		IsInCategory(EventCategory p_Cat){return GetCatFlags()& p_Cat;}
		void		SetRepeat(bool p_Repeat) { s_is_Repeat = p_Repeat;  }
		bool		is_Handled = false;
		void		SetRepeatCount(int p_Amount) { s_repeatCount = p_Amount; }
		int			GetRepeatCount() { return s_repeatCount; }
	private:
		int			s_Category = 0;
		bool		s_is_Repeat = false;
		int			s_repeatCount = 0;
	};


	using EventCallbackFn = std::function<void(PEvent&)>;

	class EventSystem
	{
	public:
		~EventSystem() 
		{
			for (int i = 0; i < (sizeof(m_PendingEvents) / sizeof(data)); i++) 
			{

				if (m_PendingEvents[i] != nullptr)
				{
					delete(m_PendingEvents[i]);

				}
			}

			
		}
		static void PublishEvent(PEvent* p_Event)
		{
			//ISSUE check working, just not printing to the console.
			if (!CheckCallbackIsSet())
				return;

			assert((m_Tail+1) % m_MaxPendingEvents != m_Head);

			//create new data event, pass controll of ptr
			data* eventData = new data(p_Event);

			//pass data event to pending events list
			m_PendingEvents[m_Tail] = eventData;

			//increment position
			m_Tail = (m_Tail + 1) % m_MaxPendingEvents;
			//m_NumberPendingEvents++;
			
			UpdatePendingEvents();
		}

		//Pass the function that you would like the events to be recieved by. NOTE: the function must take an event& as a parameter.
		//need to change from void to bool, to check if func register has failed.
		inline static void RegisterEventCallback(EventCallbackFn p_Func)
		{
			//m_Func = fn;
			assert((m_FuncTail + 1) % m_MaxCallbackFuncs != m_FuncHead);

			m_Func[m_FuncTail] = p_Func;

			m_FuncTail = (m_FuncTail + 1) % m_MaxCallbackFuncs;
		}

		//Implement ability to remove event callbackfun, base on the classtype the func belongs to or when that class is deleted.
		inline static bool DeregisterEventCallback() 
		{
			return true;
		}

		//unused
		inline static void DestroyEventsOfType(EventType e) 
		{
			std::cout << "DESTORYING" << std::endl;
			for (data* eventData : m_PendingEvents)
			{
				if (eventData != nullptr)
				{
					if (eventData->GetEvent().GetEventType() == e)
					{
						//maybe change for func to mark for deletion
						eventData->GetEvent().is_Handled = true;
						
						UpdatePendingEvents();
					}
				}
			}
		}


	private:

		inline static void UpdatePendingEvents() 
		{
			for (size_t num = 0; num < sizeof(m_PendingEvents) / sizeof(data); num++)
			{
				if (m_PendingEvents[num] != nullptr)
				{
					//if the event is handled we no longer need it, remove it. 
					if (m_PendingEvents[num]->GetEvent().is_Handled)
					{
						PINE_ENGINE_INFO("Removing event as it has been handled");
						delete m_PendingEvents[num];

						m_PendingEvents[num] = nullptr;

						m_Head = (m_Head + 1) % m_MaxPendingEvents;

						continue;
					}
					//Works but it is janky. Requires user to seperate out the event types. I need to handle that. Works with static cast too.
					for (EventCallbackFn func : m_Func)
					{
						if (func == nullptr)
							break;

						//after each function has run, it will check to see if the event has been handled as this will allow for the event 
						//to be stopped before reaching a function. However, the event will be removed on the next UpdatePendingEvents cycle.
						if (!m_PendingEvents[num]->GetEvent().is_Handled)
						{
							func(dynamic_cast<decltype(m_PendingEvents[num]->GetEvent())>(m_PendingEvents[num]->GetEvent()));
						}
					}
				}
			}
		}
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
		inline static int	m_FuncHead;
		inline static int	m_FuncTail;
		inline static const int			m_MaxPendingEvents = 16;
		inline static const int			m_MaxCallbackFuncs = 50;
		inline static EventCallbackFn	m_Func[m_MaxCallbackFuncs];
		inline static int		m_NumberPendingEvents;
		inline static data*		m_PendingEvents[m_MaxPendingEvents];//This is a ring buffer, 

		inline static bool CheckCallbackIsSet() 
		{
			if (m_Func == nullptr)
			{
				static int i = 0;
				if (i < 1)
				{
					PINE_ENGINE_ERROR("EVENT SYSTEM CALLBACK NOT SET. PLEASE REGISTER A FUNCTION WITH: EventSystem::RegisterEventCallback(EventCallback fn);");
					i++;
				}
				return false;
			}
			return true;
		}
	};




	//THE EVENTS NEED TO BE MOVED OUTSIDE OF THIS CLASS

	//Event takes care of itself, when created with a pointer
	//The events need to be moved either to the event.cpp, or into a class that deals with the event type. 


	struct NetworkPlayerJoinedEvent : PEvent
	{

		NetworkPlayerJoinedEvent() : Name(), pos()
		{
			EventSystem::PublishEvent(this);
		}

		//std::string GetName() const { return Name; }
		//glm::vec2 GetPosition() const { return pos; }
		SET_EVENT_TYPE(NetworkPlayerConnected);
		SET_CATEGORY_TYPE(NetworkEvent);

	private:
		std::string Name;
		glm::vec2 pos;
	};
	struct NetworkPacketEvent : PEvent
	{

		NetworkPacketEvent(std::string p_Packet) : packet(p_Packet)
		{
			EventSystem::PublishEvent(this);
		}

		std::string GetPacket() const { return packet; }
		int SizeOfPacket() const { return sizeof(packet); }
		SET_EVENT_TYPE(NetworkPacketRecieve);
		SET_CATEGORY_TYPE(NetworkEvent);

	private:
		std::string packet;
	};

	struct WindowResizeEvent : PEvent
	{

		WindowResizeEvent(unsigned int width, unsigned int height, const char* p_WindowName) : x(width), y(height), windowName(p_WindowName)
		{
			EventSystem::PublishEvent(this);
		}

		unsigned int GetWidth() const { return x; }
		unsigned int GetHeight() const { return y; }
		const char* GetWindowName() const { return windowName; }

		SET_EVENT_TYPE(WindowResize);
		SET_CATEGORY_TYPE(WindowEvent);

	private:
		int x = 100;
		int y = 100;
		const char* windowName;

	};

	struct WindowCloseEvent : PEvent
	{

		WindowCloseEvent(const char* p_WindowName): windowName(p_WindowName)
		{
			EventSystem::PublishEvent(this);
		}

		const char* GetWindowName() const { return windowName; }
		SET_EVENT_TYPE(WindowClose);
		SET_CATEGORY_TYPE(WindowEvent);

	private:
		const char* windowName;
	};

	//p_X is the x position of the cursor, p_Y is the y pos of the cursor, p_button for the Input::TYPE of mouse press, and bool for if the button is held. The event when created will self publish to the event system
	struct MouseButtonDownEvent : PEvent
	{
		MouseButtonDownEvent(int p_X, int p_Y, Input::MouseButtons p_Button, bool p_Held, const char* p_WindowName) : x(p_X), y(p_Y),l_button(p_Button), held(p_Held), windowName(p_WindowName)
		{
			EventSystem::PublishEvent(this);
		}

		int GetX() const { return x; }
		int GetY() const { return y; }
		Input::MouseButtons GetButtonDown() const { return l_button; }
		const char* GetWindowName() const { return windowName; }

		bool IsHeld() const { return held; }

		SET_EVENT_TYPE(MouseButtonDown);
		SET_CATEGORY_TYPE(WindowEvent | MouseEvent | InputEvent);

	private:
		int x;
		int y;
		bool held;
		Input::MouseButtons l_button;
		const char* windowName;
	};
	struct MouseButtonUpEvent : PEvent
	{
		MouseButtonUpEvent(int p_X, int p_Y, Input::MouseButtons p_Button, bool p_Held, const char* p_WindowName) : x(p_X), y(p_Y), l_button(p_Button), held(p_Held), windowName(p_WindowName)
		{
			EventSystem::PublishEvent(this);
		}

		int GetX() const { return x; }
		int GetY() const { return y; }
		Input::MouseButtons GetButtonDown() const { return l_button; }
		const char* GetWindowName() const { return windowName; }

		bool IsHeld() const { return held; }

		SET_EVENT_TYPE(MouseButtonUp);
		SET_CATEGORY_TYPE(WindowEvent | MouseEvent | InputEvent);

	private:
		int x;
		int y;
		bool held;
		Input::MouseButtons l_button;
		const char* windowName;


	};

	struct MouseScrollEvent : PEvent
	{

		MouseScrollEvent(float p_Ofset) : l_Offset(p_Ofset)
		{
			EventSystem::PublishEvent(this);
		}

		int GetOffset() const { return l_Offset; }
		SET_EVENT_TYPE(MiddleMouseScroll);
		SET_CATEGORY_TYPE(MouseEvent | InputEvent);

	private:
		const float l_Offset;
	};
	struct KeyDownEvent :PEvent 
	{
		
		KeyDownEvent(Input::KeyStrokes p_Key) :l_Key(p_Key)
		{
			EventSystem::PublishEvent(this);
		}

		Input::KeyStrokes GetKey() { return l_Key; }
		SET_EVENT_TYPE(KeyDown);
		SET_CATEGORY_TYPE(WindowEvent | KeyboardEvent | InputEvent);
	private: 
		Input::KeyStrokes l_Key;
	
	};

	struct KeyUpEvent :PEvent
	{

		KeyUpEvent(Input::KeyStrokes p_Key) :l_Key(p_Key)
		{
			EventSystem::PublishEvent(this);
		}

		Input::KeyStrokes GetKey() { return l_Key; }

		SET_EVENT_TYPE(KeyUp);
		SET_CATEGORY_TYPE(WindowEvent | KeyboardEvent | InputEvent);
	private:
		Input::KeyStrokes l_Key;

	};
}


//in window creation create a function that sets the callback function that should be run when a event occurs.
//This will be set when the window is created, after this all events that are created will be passed to this function in application
//we can then distribute event types to different fucntions. 
//going back where the sdl event occurs, each sdl event will need to pass a struct with the screen data
