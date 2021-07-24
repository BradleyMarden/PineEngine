#pragma once
#include <SDL.h>
#include "../Maths/PMaths.h"
#include "Log.h"
#include "window.h"
namespace Pine {
	class Input {

	public:
		 enum  MouseButtons { 
			DEFAULT,
			LEFTSINGLECLICK,
			LEFTDOUBLECLICK,
			LEFTDOWN,
			LEFTUP,
			RIGHTSINGLECLICK,
			RIGHTDOUBLECLICK,
			RIGHTDOWN,
			RIGHTUP,
			MIDDLEMOUSECLICK,
			MIDDLEMOUSEDOWN,
			MIDDLEMOUSEUP 
		};

		 //need to link these up to ascii numbers. Currently still works, we have bigger issues
		 enum KeyStrokes 
		 {
			W,
			A,
			S,
			D
		 };
		//static void MousePressed(int mouseButton);//0 for L, 2 for R, 3 For Middle
		static void MousePressed(SDL_Event* mouseButton);//0 for L, 2 for R, 3 For Middle

		//THESE NEED TO BE REFACTORED< LOTS OF UNUSED OR REWRITTEN CODE AS A RESUKT OF THE EVENT SYSTEM

		//test function for event system.
        static MouseButtons MouseDown(SDL_Event* e);
        static KeyStrokes KeyDown(SDL_Event* e);

		static bool OnMouseButtonUp(int mouseButton);
		static bool CloseApplication();
		static bool OnMouseButton(MouseButtons State);
	//	static bool OnMouseButtonDown(MouseButtons State);
		static void MouseReleased(SDL_Event* mouseButton);
		static PVector2f GetMousePosition();
		static void KeyPressed(SDL_Event* Key);
		static SDL_KeyCode m_key;
		//returns true if key is down
		static bool GetKeyDown(SDL_Scancode key);

	private:
		bool clicked;
		static MouseButtons CurrentMouseButton;
	};
}
