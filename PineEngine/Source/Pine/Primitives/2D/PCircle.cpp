#include "PCircle.h"
#include <algorithm>
namespace Pine
{
	PCircle::PCircle(int centerX, int centerY, int radius, int r, int g, int b)
	{
		m_Center.x = centerX;
		m_Center.y = centerY;
		cR = r;
		cG = g;
		cB = b;
		m_Radius = radius;

		RecalculateBounds();
	}
	PCircle::~PCircle()
	{
	
	}
	SDL_Point PCircle::GetCenter()
	{
		return m_Center;
	}

	void PCircle::RecalculateBounds()
	{
		int left = m_Center.x - m_Radius;
		int top = m_Center.y - m_Radius;
		int width = 2 * m_Radius;
		int height = 2 * m_Radius;
		m_Bounds.x = left;
		m_Bounds.y = top;
		m_Bounds.w = width;
		m_Bounds.h = height;
	
	}

	SDL_Rect PCircle::GetBounds()
	{
		return m_Bounds;
	}
	int PCircle::GetRadius()
	{
		return m_Radius;
	}

	bool PCircle::Render(SDL_Renderer *renderer)
	{
		if (renderer != nullptr)
		{
			int r = cR;
			int g = cG;
			int b = cB;

			SDL_SetRenderDrawColor(renderer, r, g, b, 255);
			
			int sX = m_Bounds.x;
			int eX = m_Bounds.x + m_Bounds.w;
			int sY = m_Bounds.y;
			int eY = m_Bounds.y = m_Bounds.h;
			int cX = m_Center.x;
			int cY = m_Center.y;

			int renderWidth, renderHeight;
			SDL_GetRendererOutputSize(renderer, &renderWidth, &renderHeight);

			for(int x=sX; x<eX;++x)
			{
				for(int y = sY; y<eY; ++y)
				{
					int circleV = (x - cX) * (x - cX) + (y - cY) * (y - cY) - m_Radius * m_Radius;
					if (circleV <=0)
					{
						SDL_RenderDrawPoint(renderer, x, y);
					}
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

}