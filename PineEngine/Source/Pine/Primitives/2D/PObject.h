#pragma once

//#include "../../Maths/PMaths.h"
#include "sdl2/SDL.h"
#include "../../Maths/PMaths.h"
namespace Pine {
	class PObject
	{
	public:
		//Base class for creating on screen objects

		PObject();
		~PObject();//inherited by child
	
		virtual bool Render();
		virtual SDL_Rect GetBounds();
		virtual void SetRenderer(SDL_Renderer* p_Renderer);
		virtual void UpdateRenderer(SDL_Renderer* p_Renderer);
	};
}
