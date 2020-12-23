#include "PObject.h"

namespace Pine
{
	PObject::PObject()
	{
	
	}
	PObject::~PObject()
	{
	
	}
	SDL_Rect PObject::GetBounds()
	{
		SDL_Rect temp = { 1,1 };
		return temp;
	}
	bool PObject::Render(SDL_Renderer *renderer) 
	{
		return true;
	}


}