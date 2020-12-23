#pragma once
//#include "../Logging/log.h"
namespace Pine {

	struct PVector2f
	{
		float X;
		float Y;

		PVector2f(float p_X, float p_Y) : X(p_X), Y(p_Y){}
		PVector2f() : X(0), Y(0) {}
		
		
	};
	struct PColourf
	{
		float R;
		float G;
		float B;
		float W;

		PColourf(float p_R, float p_G, float p_B, float p_W) : R(p_R), G(p_G), B(p_B), W(p_W) {}
		PColourf() : R(0), G(0),B(0) ,W(0) {}

	};


}

