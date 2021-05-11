#pragma once
#include <SDL2/SDL.h>
#include "Core.h"
#include "../Maths/PMaths.h"
namespace Pine {
	class Input {

	public:
		 enum MouseButtons { 
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

		//static void MousePressed(int mouseButton);//0 for L, 2 for R, 3 For Middle
		static void MousePressed(SDL_Event* mouseButton);//0 for L, 2 for R, 3 For Middle
		static bool OnMouseButtonUp(int mouseButton);
		static bool CloseApplication();
		static bool OnMouseButton(MouseButtons State);
	//	static bool OnMouseButtonDown(MouseButtons State);
		static void MouseReleased(SDL_Event* mouseButton);
		static PVector2f GetMousePosition();
		static void KeyPressed(SDL_Event* Key);
		static SDL_KeyCode m_key;
		static bool GetKeyDown(SDL_KeyCode key);

	private:
		bool clicked;
		static MouseButtons CurrentMouseButton;
	};
}
