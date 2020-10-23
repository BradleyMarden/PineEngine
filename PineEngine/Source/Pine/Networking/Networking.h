#pragma once
#include "enet/enet.h"
#include "../Logging/Log.h"
#define PINE_MAX_NETWORK_MESSAGES 100000
namespace Pine {

	


	
	

	class Networking
	{

	public:
		Networking();

		~Networking();


		
		static bool PineNetworkInit();
		static int PineNetworkCreate(unsigned int port, unsigned int maxConnections);
		static int PineNetworkConnect(const char* ipAddress, unsigned int port);
		static void PineNetworkLoop();
		static int PineNetworkClose();
		static void PineSendPacket(const char* text);
		static void PineSendGlobalPacket(const char* text);
		static void PineNetworkDisconnect();
		

	protected:
		static ENetHost* host;
		static ENetPeer* peer;
		static bool isHosting;
		static 	bool isConnected;


	private:
		


	};

}