#include "PRect.h"

/*Pine::PRect::PRect(Pine::PVector2f p_Position, Pine::PVector2f p_Size, Pine::PVector2f p_Scale, SDL_Texture& p_texture, char* p_Path, PColourf p_Colour)
{
	Position = p_Position;
	Size = p_Size;
	Scale = p_Scale;
	Texture = &p_texture;
	path = p_Path;
	Colour = p_Colour;
	
}*/

Pine::PRect::PRect(Pine::PVector2f p_Position, Pine::PVector2f p_Size)
{
	Position = p_Position;
	Size = p_Size;
	Scale = Pine::PVector2f(1,1);
	Texture = nullptr;
	path = nullptr;
	Colour = Pine::PColourf(1, 0, 0, 255);
	
}
Pine::PRect::PRect()
{
	
	Scale = Pine::PVector2f(1,1);
	Texture = nullptr;
	path = nullptr;
	Colour = Pine::PColourf(1, 0, 0, 255);
	
}
Pine::PRect::~PRect()
{
	delete Texture;
	delete path;
}


bool Pine::PRect::Render(SDL_Renderer* renderer)
{
	if (renderer != nullptr)
	{
		//draw here
		Bounds.x = Position.X;
		Bounds.y = Position.Y;
		Bounds.w = Size.X;
		Bounds.h = Size.Y;

		//SDL_RenderCopy(renderer, Texture, &Bounds, &Bounds);
		SDL_RenderDrawRect(renderer, &Bounds);
		SDL_SetRenderDrawColor(renderer, Colour.R,Colour.G,Colour.B,Colour.W);
		SDL_RenderFillRect(renderer, &Bounds);

	}
	else
	{
		return false;
	}
	return true;
}