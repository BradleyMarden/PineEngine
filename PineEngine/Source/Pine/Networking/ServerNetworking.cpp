#include "ServerNetworking.h"
#include "../Logging/Log.h"
namespace Pine {

	ServerNetworking::ServerNetworking()
	{
	
	}
	bool ServerNetworking::PineNetworkInit()
	{
		PINE_SERVER_INFO("Initializing Network...");

		if (enet_initialize() !=0)
		{
			PINE_SERVER_CRITICAL("Failed Initializing Network... Closing");
			return false;
		}
		atexit(enet_deinitialize);
		PINE_SERVER_INFO("Initialized Network!");
		return true;

	}
	int ServerNetworking::PineNetworkCreate(unsigned int port, unsigned int maxConnections)
	{
		return 1;
	}

	int ServerNetworking::PineNetworkClose()
	{
		return 1;

	}
}