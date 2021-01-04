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

Pine::PRect::PRect(Pine::PVector2f p_Position, Pine::PVector2f p_Size, const char* p_Path)
{

	Position = p_Position;
	Size = p_Size;
	Scale = Pine::PVector2f(1, 1);
	Texture = nullptr;
	path = p_Path;
	Surface = nullptr;
	Colour = Pine::PColourf(1, 0, 0, 255);
	PINE_ENGINE_INFO("CREATED RECT");
}


Pine::PRect::PRect()
{

	Scale = Pine::PVector2f(1, 1);
	Texture = nullptr;
	path = nullptr;
	Surface = nullptr;
	Colour = Pine::PColourf(1, 0, 0, 255);
	//PINE_ENGINE_INFO("CREATED RECT");
}
Pine::PRect::~PRect()
{
	PINE_ENGINE_INFO("DESTROYED RECT");

	//delete Texture;
	//delete path;
}
void Pine::PRect::SetRenderer(SDL_Renderer* p_Renderer)
{
	renderer = p_Renderer;
	//load texture 
	if (path != nullptr)
	{
		Texture = IMG_LoadTexture(renderer, path);
		if (Texture == NULL)
		{
			PINE_ENGINE_ERROR("Could not find image: {0}. \nCheck file extention or path.\n", path);
		}
	}
}


bool Pine::PRect::Render()
{
	if (renderer != nullptr)
	{
		//draw here
		Bounds.x = Position.X;
		Bounds.y = Position.Y;
		Bounds.w = Size.X;//object size on screen
		Bounds.h = Size.Y;
		if (path != nullptr)//render Textured rect
		{
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			src.w = 959;//actual image resolution
			src.h = 828;//actual image resolution

			
			SDL_RenderCopy(renderer, Texture, &src, &Bounds);
			
			PINE_ENGINE_INFO("CREATED IMAGE");

		
		}
		else//render filled rect
		{
			PINE_ENGINE_INFO("CREATED RECT");
			//SDL_RenderCopy(renderer, Texture, &Bounds, &Bounds);
			SDL_RenderDrawRect(renderer, &Bounds);
			SDL_SetRenderDrawColor(renderer, Colour.R, Colour.G, Colour.B, Colour.W);
			SDL_RenderFillRect(renderer, &Bounds);

		}
	}
	else
	{
		return false;
	}
	return true;
}