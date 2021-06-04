#include "Renderer.h"
namespace Pine {

	Renderer::Renderer(SDL_Window& p_Window)
	{
		m_SDL_Renderer = SDL_CreateRenderer(&p_Window, -1, 0);
		SDL_SetRenderDrawColor(m_SDL_Renderer, 21, 27, 31, 255);
		SDL_RenderClear(m_SDL_Renderer);
	}

	Renderer::~Renderer()
	{
	}
}