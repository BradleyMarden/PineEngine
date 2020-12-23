#pragma once
#include "PObject.h"
#include <stdio.h>
#include <iostream>
#include "../../Core/Core.h"
namespace Pine {
	class PRect : public PObject
	{
		
	
		Pine::PVector2f Position;
		Pine::PColourf Colour;
		Pine::PVector2f Scale;
		Pine::PVector2f Size;
		SDL_Texture* Texture;
		char* path;
		SDL_Rect Bounds;
	public:

		//will implement below if need to controll rect texture. Otherwise use PEntity
		//PRect(Pine::PVector2f p_Position, Pine::PVector2f p_Size, Pine::PVector2f p_Scale, SDL_Texture& p_texture, char* p_Path, PColourf p_Colour);
		PRect(Pine::PVector2f p_Position, Pine::PVector2f p_Size);
		~PRect();
		void SetColour(Pine::PColourf p_Colour)			{ Colour = p_Colour; }
		void SetPosition(Pine::PVector2f p_Position)	{ Position = p_Position; }
		void SetScale(Pine::PVector2f p_Scale)			{ Scale = p_Scale; }
		void SetTexture(SDL_Texture *p_Texture)			{ Texture = p_Texture; }
		void SetTexturePath(char* p_Path)				{ path = p_Path; }
		
		
		

		Pine::PVector2f GetPosition()					{ return Position; }
		Pine::PColourf GetColour()						{ return Colour; }
		Pine::PVector2f GetScale()						{ return Scale; }
		SDL_Texture* GetTexture()						{ return Texture; }
		SDL_Rect GetBounds()							{ return Bounds; }
		bool Render(SDL_Renderer* renderer);

	private:
		void RecalculateBounds();






	};
}
