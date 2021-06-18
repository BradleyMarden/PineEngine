#pragma once
#include "enet/enet.h"
#include "../Logging/Log.h"
#include <stdlib.h>
#include <string>

#define PINE_MAX_NETWORK_MESSAGES 100000
namespace Pine {

	


	
	

	class Networking
	{

	public:
		Networking();
		~Networking();


		static bool    PineNetworkingInit();//initialise Networking component
		static int	   PineServerCreate(unsigned int port, unsigned int maxConnections);//Create a server, specify the port and the number of maxConnections
		static void    PineServerNetworkLoop(int delayBetweenLoops);//Place in update, checks for incoming packets 
		static void    PineServerClose();//Closes the server
					   
		static int	   PineServerConnect(const char* ipAddress, unsigned int port);//Specify ipAddress and port of server to connect
		static bool    PineClientNetworkLoop(int delayBetweenLoops);//Place in update, checks for incoming packets 
		static void    PineSendPacket(std::string text);//send a packet containing text
		static void    PineSendGlobalPacket(std::string text);//Send a global packet containing text
		static void    PineServerDisconnect();//Disconnect from server
		inline static char* PineGetLastMessage() { return lastMessage; }//TEST returns last message

	private:
		static ENetHost* host;
		static ENetPeer* peer;

		static bool   isHosting;
		static 	bool  isConnected;
		static char   lastMessage[];

	};

}



