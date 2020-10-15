#include "Networking.h"

namespace Pine{
	
	bool Networking::InitNetwork()
	{
		if (enet_initialize() != 0)
		{
			return false;
		}
		return true;
	}

}