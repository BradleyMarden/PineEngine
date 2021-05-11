#include "Networking.h"

namespace Pine{
	 ENetHost* Networking::host;
	 ENetPeer* Networking::peer;
	 bool Networking::isConnected = false;
	 bool Networking::isHosting = false;
	 char Networking::lastMessage[] = "";


	Networking::Networking()
	{
	
	}

	Networking::~Networking()
	{
	
	
	}
	//send packets
	void Networking::PineSendPacket(std::string text)
	{
		const char* s = text.c_str();
		ENetPacket* packet = enet_packet_create(s, strlen(s) + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		enet_host_flush(host);
	}

	void Networking::PineSendGlobalPacket(std::string text)
	{
		const char* s = text.c_str();
		ENetPacket* packet = enet_packet_create(s, strlen(s) + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_host_broadcast(host, 0, packet);
		enet_host_flush(host);

	}

	//client networking
	bool Networking::PineNetworkingInit()
	{
		PINE_SERVER_INFO("Initializing Network Functionality...");

		if (enet_initialize() != 0)
		{
			PINE_SERVER_CRITICAL("Failed Initializing Network Functionality... Closing");
			return EXIT_FAILURE;
		}
		atexit(enet_deinitialize);
		PINE_SERVER_INFO("Initialized Network Functionality!");
		return EXIT_SUCCESS;

	}

	int Networking::PineServerConnect(const char* ipAddress, unsigned int port)
	{
		ENetAddress address;
		ENetEvent event;

		host = enet_host_create(NULL, 1, 1, 0, 0);


		if (host == NULL)
		{
			PINE_SERVER_ERROR("Unable to find host");
			return EXIT_FAILURE;
		}
		//allocated ip and port to host
		enet_address_set_host(&address, ipAddress);
		address.port = port;


		peer = enet_host_connect(host, &address, 1, 0);
		if (peer == NULL)
		{
			PINE_SERVER_ERROR("Unable to Create a Client");
			return EXIT_FAILURE;
		}

		if (enet_host_service(host, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
		{
			PINE_SERVER_INFO("Connected to server: {}", ipAddress);
		}
		else
		{
			enet_peer_reset(peer);
			PINE_SERVER_WARN("Unable to connect...");
			return EXIT_FAILURE;
		}
		isConnected = true;

		return EXIT_SUCCESS;

	}
	void Networking::PineServerDisconnect()//use on client
	{

		if (!isConnected)
		{
			return;
		}
		PINE_INFO("Disconnecting");
		enet_peer_disconnect(peer, 0);
		ENetEvent event;

		if (enet_host_service(host, &event, 0) > 0 && event.type == ENET_EVENT_TYPE_DISCONNECT)
		{
			PINE_INFO("Disconnected from server.");

		}
	}
	bool Networking::PineClientNetworkLoop(int delayBetweenLoops)
	{
		if (!isConnected)
		{
			return EXIT_FAILURE;
		}
		ENetEvent event;

		while (enet_host_service(host, &event, delayBetweenLoops) > 0)
		{
			switch (event.type) {

			case ENET_EVENT_TYPE_NONE:
				break;
                    
                case ENET_EVENT_TYPE_CONNECT:
                    PINE_SERVER_INFO("CONNECTED: NOT TOO SURE IF THIS IS SERVER OR CLIENT AS I HAVE NO INTERNET!")

			case ENET_EVENT_TYPE_RECEIVE:
				PINE_SERVER_INFO("A Packet of length {} containing {} from {} on channel {}", event.packet->dataLength, event.packet->data, event.peer->data, event.channelID);
				{
					uint64_t lData = 0;
					lData = (uint64_t)event.packet->data;
					if (std::strcmp((const char*)event.packet->data, "close"))
					{
						PINE_SERVER_INFO("Server Closing...");
					}
					enet_packet_destroy(event.packet);
				}
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				PINE_SERVER_INFO("Server has Closed.");
				return EXIT_FAILURE;
				break;
			}
			return EXIT_SUCCESS;
		}
		return EXIT_SUCCESS;
	}

	//Server Networking
	int Networking::PineServerCreate(unsigned int port, unsigned int maxConnections)
	{
		ENetAddress address;
		ENetEvent event;

		address.host = ENET_HOST_ANY;
		address.port = port;
		host = enet_host_create(&address, maxConnections, 1, 0, 0);

		if (host == NULL)
		{
			PINE_SERVER_ERROR("Unable to create a host");
			return EXIT_FAILURE;
		}
	
		PINE_SERVER_INFO("Created host with {} slots, on port {}", maxConnections, port);
		isHosting = true;
		isConnected = true;
		return EXIT_SUCCESS;
	}
	

	 
	 void Networking::PineServerClose() 
	 {
		 if (!isConnected)
		 {
			 return;
		 }
		 PINE_SERVER_INFO("Closing Server");
		 PineSendGlobalPacket("close");
		 enet_host_destroy(host);
	 }
	 
	 void Networking::PineServerNetworkLoop(int delayBetweenLoops)//Use on server to check clients state
	 {
		 if (!isConnected)
		 {
			 return;

		 }
		 ENetEvent event;
		 while (enet_host_service(host,&event, delayBetweenLoops) > 0)
		 {
			 switch(event.type)
			 {
			 case ENET_EVENT_TYPE_CONNECT:
				 PINE_INFO("A Client has connected from: {}:{}", event.peer->address.host, event.peer->address.port);
				 break;
			 case ENET_EVENT_TYPE_DISCONNECT:
				 PINE_INFO("A Client has Disconnected from: {}:{}", event.peer->address.host, event.peer->address.port);
				 break;
			 case ENET_EVENT_TYPE_RECEIVE:
				 PINE_INFO("A Packet of length {} containing {} from {} on channel {}", event.packet->dataLength, event.packet->data, event.peer->data, event.channelID);
				 for (size_t i = 0; i < event.packet->dataLength; i++)
				 {
					 lastMessage[i] = static_cast<const char>(event.packet->data[i]);
				 }
				 
				enet_packet_destroy(event.packet);
				break;
			 case ENET_EVENT_TYPE_NONE:
				 break;
			 }
		 }
	 }
}
