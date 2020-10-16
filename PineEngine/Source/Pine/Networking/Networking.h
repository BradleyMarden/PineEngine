#pragma once
#include "enet/enet.h"

namespace Pine {
	
	class Networking
	{

		Networking();
		~Networking();
	public:
		static bool InitNetwork();
		static bool DeInitNetwork();
	



	};

}