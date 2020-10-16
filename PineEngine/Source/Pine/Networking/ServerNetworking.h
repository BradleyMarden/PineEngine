#pragma once
#include "enet/enet.h"

namespace Pine{
	class ServerNetworking
	{
	public:
		ServerNetworking();
		~ServerNetworking();
		
			static bool PineNetworkInit();

			static int PineNetworkCreate(unsigned int port, unsigned int maxConnections);
			static int PineNetworkClose();



	};
}

