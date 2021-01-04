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
	
	private:

		//Pine::PMaths::PVector2 Position;//maybe abstract out to child classes
		//Pine::PMaths::PVector3 Colour;
	public:
		//Pine::PMaths::PVector2 GetPosition() {	return Position; }
		//Pine::PMaths::PVector3 GetColour()   {  return Colour;	 }
		

		//void SetColour(Pine::PMaths::PVector3 m_Colour)		{ Colour = m_Colour;	 }
		//void SetPosition(Pine::PMaths::PVector2 m_Position) { Position = m_Position; }


		virtual bool Render();
		virtual SDL_Rect GetBounds();
		virtual void SetRenderer(SDL_Renderer* p_Renderer);
	};
}
