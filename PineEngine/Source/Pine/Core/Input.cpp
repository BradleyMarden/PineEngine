#include "Input.h"

namespace Pine {
	 Input::MouseButtons Input::CurrentMouseButton;
	 SDL_KeyCode Input::m_key;
	void Input::MousePressed(SDL_Event* mouseButton)
	{
		switch (mouseButton->button.button)
		{
		default:
			break;
		case SDL_BUTTON_RIGHT:
			//PINE_ENGINE_ERROR("RIGHT PRESSED");
			CurrentMouseButton = RIGHTDOWN;
			break;
		case SDL_BUTTON_MIDDLE://double click
			//PINE_ENGINE_ERROR("MIDDLE PRESSED");
			CurrentMouseButton = MIDDLEMOUSEDOWN;
			break;
		case SDL_BUTTON_LEFT://single slick
			//PINE_ENGINE_ERROR("LEFT PRESSED");
			CurrentMouseButton = LEFTDOWN;
			break;
			
		
		}
		
	}

	Input::MouseButtons Input::MouseDown(SDL_Event* e) 
	{
		switch (e->button.button)
		{
		default:
			break;
		case SDL_BUTTON_RIGHT:
			return RIGHTSINGLECLICK;
			break;
		case SDL_BUTTON_MIDDLE:
			return MIDDLEMOUSECLICK;
			break;
		case SDL_BUTTON_LEFT://single slick
			return LEFTSINGLECLICK;
			break;
		}
	}

	Input::KeyStrokes Input::KeyDown(SDL_Event* e)
	{
		switch (e->button.button)
		{
		default:
			break;
		case SDLK_w:
			return W;
			break;
		case SDLK_a:
			return A;
			break;
		case SDLK_s:
			return S;
			break;
		}
	}


	void Input::MouseReleased(SDL_Event* mouseButton)
	{
		switch (mouseButton->button.button)
		{
		default:
			break;
		case SDL_BUTTON_RIGHT:
			//PINE_ENGINE_ERROR("RIGHT RELEASED");
			CurrentMouseButton = RIGHTUP;
			break;
		case SDL_BUTTON_MIDDLE://double click
		//	PINE_ENGINE_ERROR("MIDDLE RELEASED");
			CurrentMouseButton = MIDDLEMOUSEDOWN;
			break;
		case SDL_BUTTON_LEFT://single slick
		//	PINE_ENGINE_ERROR("LEFT RELEASED");
			CurrentMouseButton = LEFTUP;
			break;

		}
	}
	bool Input::OnMouseButton(MouseButtons State)
	{
		switch (State)
		{
		default:
			break;
		case LEFTDOWN:
			if (CurrentMouseButton == LEFTDOWN)
			{
				CurrentMouseButton = DEFAULT;
				return true;
			}
			break;
			
		case RIGHTDOWN:
			if (CurrentMouseButton == RIGHTDOWN)
			{
				CurrentMouseButton = DEFAULT;
				return true;
			}
			break;
		case MIDDLEMOUSEDOWN:
			if (CurrentMouseButton == MIDDLEMOUSEDOWN)
			{
				CurrentMouseButton = DEFAULT;
				return true;
			}
			break;
		case LEFTUP:
			if (CurrentMouseButton == LEFTUP)
			{
				CurrentMouseButton = DEFAULT;
				return true;
			}
			break;
		case RIGHTUP:
			if (CurrentMouseButton == RIGHTUP)
			{
				CurrentMouseButton = DEFAULT;
				return true;
			}
			break;
		case MIDDLEMOUSEUP:
			if (CurrentMouseButton == MIDDLEMOUSEUP)
			{
				CurrentMouseButton = DEFAULT;
				return true;
			}
			break;
			

		}
		return false;
	}

	/*bool Input::OnMouseButtonDown(MouseButtons State)
	{
		switch (State)
		{
		case Pine::Input::DEFAULT:
			break;
		case Pine::Input::LEFTDOWN:

			break;

		case Pine::Input::RIGHTDOWN:
			break;

		case Pine::Input::MIDDLEMOUSEDOWN:
			break;

		default:
			break;
		}
	}*/
	bool Input::OnMouseButtonUp(int mouseButton)
	{
		return false;
	}
	bool Input::CloseApplication()
	{
		SDL_Event e;
		SDL_PollEvent(&e);
		switch (e.type)
		{
		default:
			break;
		case SDL_QUIT:
			
			("CLOSE BUTTON PRESSED");
			return true;
		}
		return false;
		
	}

	//need to change to glm vec2
	PVector2f Input::GetMousePosition()//return mouse current on-screen pos
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		return PVector2f(x, y);
	}



	void Input::KeyPressed(SDL_Event* Key)
	{
		switch(Key->key.keysym.sym)
		{
		case SDLK_LEFT:
			PINE_ENGINE_WARN("Left Arrow Pressed!");
			m_key = SDLK_LEFT;
			break;
		case SDLK_RIGHT:
			PINE_ENGINE_WARN("RIGHT Arrow Pressed!");
			break;
		case SDLK_UP:
			PINE_ENGINE_WARN("Up Arrow Pressed!");
			break;
		case SDLK_DOWN:
			PINE_ENGINE_WARN("Down Arrow Pressed!");
			break;
		case SDLK_w:
			PINE_ENGINE_WARN("W Arrow Pressed!");
			m_key = SDLK_w;
			break;
		case SDLK_a:
			PINE_ENGINE_WARN("A Arrow Pressed!");
			m_key = SDLK_a;
			break;
		case SDLK_s:
			PINE_ENGINE_WARN("S Arrow Pressed!");
			m_key = SDLK_s;
			break;
		case SDLK_d:
			PINE_ENGINE_WARN("D Arrow Pressed!");
			m_key = SDLK_d;
			break;
		}
	
	}
	bool Input::GetKeyDown(SDL_Scancode key)
	{
		//auto* window = static_cast<SDL_Window*>(Window::GetWindowGLData(Window::GetMainWindow()->s_WindowName)->s_Window);
		int count = 0;
		const uint8_t* state = SDL_GetKeyboardState(NULL);

		if (state[key]) {
			//PINE_ENGINE_WARN("PRESSED");
			return true;
		}
		else {

			//PINE_ENGINE_WARN("NOT PRESSED");
			return false;
		}
/*
		if (key != m_key)
		{
			return false;
		}
		m_key = SDLK_UNKNOWN;
		return true;
		*/
		
	}


	
}