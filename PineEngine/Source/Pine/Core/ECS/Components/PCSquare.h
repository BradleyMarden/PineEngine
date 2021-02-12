#pragma once
#include "../../../Primitives/2D/PRect.h"
#include "../../Core.h"
namespace Pine {
	class PCSquare : public PComponent
	{
		/*
			TODO:
			Utilise PRect to create a square, and allow it to be used as a component.
			Abstract all of the rendering away from the user so that they do not need to worry about the object after it has been created.
		
		*/
	public:
		PCSquare() {}
		PCSquare(SDL_Renderer* p_rend);
		
		~PCSquare();

		void Update();
		void Start();
	private:

	};
}

