#include "PCSquare.h"
namespace Pine
{
	
	PCSquare::PCSquare(SDL_Renderer* p_rend) {
		rect.SetRenderer(p_rend);
		rect.SetPosition(PVector2f(300, 200));

	}

	PCSquare::~PCSquare(){}
	void PCSquare::Update()
	{
	
	}
	void PCSquare::Start()
	{

	}
	

}
