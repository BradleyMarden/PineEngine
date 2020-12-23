#pragma once
#include "PObject.h"
//#include "sdl2/SDL.h"
namespace Pine {
	class PCircle : public PObject
	{
		public:
		PCircle(int centerX,int centerY, int radius, int r, int g, int b);
		~PCircle();

		bool Render(SDL_Renderer* renderer);
		SDL_Rect GetBounds();
		SDL_Point GetCenter();
		int GetRadius();


	private: //private fucntions
	
		void RecalculateBounds();//run anytime a change is made to a circle

	private: //private member variables
		SDL_Rect m_Bounds;
		SDL_Point m_Center;
		//PMaths::PVector3 m_Colour;
		int cR, cG, cB;
		int m_Radius;

	};
}

