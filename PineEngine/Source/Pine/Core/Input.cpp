#include "Input.h"

namespace Pine {
	 Input::MouseButtons Input::CurrentMouseButton;
	
	void Input::MousePressed(SDL_Event* mouseButton)
	{
		switch (mouseButton->button.button)
		{
		default:
			break;
		case SDL_BUTTON_RIGHT:
			PINE_ENGINE_ERROR("RIGHT PRESSED");
			CurrentMouseButton = RIGHTDOWN;
			break;
		case SDL_BUTTON_MIDDLE://double click
			PINE_ENGINE_ERROR("MIDDLE PRESSED");
			CurrentMouseButton = MIDDLEMOUSEDOWN;
			break;
		case SDL_BUTTON_LEFT://single slick
			PINE_ENGINE_ERROR("LEFT PRESSED");
			CurrentMouseButton = LEFTDOWN;
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
			PINE_ENGINE_ERROR("RIGHT RELEASED");
			CurrentMouseButton = RIGHTUP;
			break;
		case SDL_BUTTON_MIDDLE://double click
			PINE_ENGINE_ERROR("MIDDLE RELEASED");
			CurrentMouseButton = MIDDLEMOUSEDOWN;
			break;
		case SDL_BUTTON_LEFT://single slick
			PINE_ENGINE_ERROR("LEFT RELEASED");
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
			PINE_ENGINE_WARN("CLOSE BUTTON PRESSED");
			return true;
		}
		return false;
		
	}

	
}