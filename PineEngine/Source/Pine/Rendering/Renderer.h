#pragma once
#include <SDL.h>

namespace Pine {
	struct MyStruct
	{

	};

	class Renderer
	{
	public:
		Renderer();
		Renderer(SDL_Window& p_Window);
		~Renderer();
		



	private:
		SDL_Renderer* m_SDL_Renderer;

	};
}