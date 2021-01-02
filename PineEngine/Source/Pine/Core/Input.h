#pragma once
#include "Core.h"
#include "../Maths/PMaths.h"
#include "sdl2/SDL.h"
namespace Pine {
	class Input {

	public:
		static enum MouseButtons { 
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

		//static	PVector2f  GetMousePosition();
		//static void MousePressed(int mouseButton);//0 for L, 2 for R, 3 For Middle
		static void MousePressed(SDL_Event* mouseButton);//0 for L, 2 for R, 3 For Middle
		static bool OnMouseButtonUp(int mouseButton);
		static bool CloseApplication();
		static bool OnMouseButton(MouseButtons State);
	//	static bool OnMouseButtonDown(MouseButtons State);
		static void MouseReleased(SDL_Event* mouseButton);
	private:
		
		bool clicked;
		static MouseButtons CurrentMouseButton;
	};
}