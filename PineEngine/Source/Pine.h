/*
INCLUDE ALL HEADERS HERE THAT THE USER WILL NEED
*/

#pragma once

#include "Pine/Core/Core.h"
#include "Pine/Core/Game.h"
#include "Pine/Networking/Networking.h"
#include "Pine/Logging/Log.h"
#include "Pine/Core/Input.h"
#include "Pine/Rendering/Shader.h"

#ifdef DEBUG
	#define PINE_ASSERT(message, functionReturn) PineAssert(message, functionReturn)
#endif // DEBUG

//Custom Assert Macro
inline void PineAssert(const char* p_Message, bool functionReturn)
{
	if (!functionReturn) {
		std::cerr << "Error:\t" << p_Message << "\n";
		abort();
	}
}



