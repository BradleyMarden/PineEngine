#include "Networking.h"

namespace Pine{
	 ENetHost* Networking::host;
	 ENetPeer* Networking::peer;
	 bool Networking::isConnected = false;
	 bool Networking::isHosting = false;

	Networking::Networking()
	{
	
	}

	Networking::~Networking()
	{
	
	
	}

	bool Networking::PineNetworkInit()
	{
		PINE_SERVER_INFO("Initializing Network...");

		if (enet_initialize() != 0)
		{
			PINE_SERVER_CRITICAL("Failed Initializing Network... Closing");
			return EXIT_FAILURE;
		}
		atexit(enet_deinitialize);
		PINE_SERVER_INFO("Initialized Network!");
		return EXIT_SUCCESS;

	}
	int Networking::PineNetworkCreate(unsigned int port, unsigned int maxConnections)
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
	 int Networking::PineNetworkConnect(const char* ipAddress, unsigned int port) 
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
			 PINE_SERVER_INFO("Connected to server: {}",  ipAddress);
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

	 void Networking::PineNetworkDisconnect()
	 {
		 

		 if (!isConnected)
		 {
			 return;
		 }
		 PINE_SERVER_INFO("Disconnecting");
		 enet_peer_disconnect(peer, 0);
		 ENetEvent event;

		 if (enet_host_service(host, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_DISCONNECT)
		 {
			 PINE_SERVER_INFO("Disconnected from server.");

		 }

		
	 }
	 void Networking::PineNetworkLoop()
	 {
		 //PINE_SERVER_WARN("In WHILE LOOP");

		 if (!isConnected)
		 {
			 return;

		 }
		 ENetEvent event;
		 while (enet_host_service(host,&event,0) > 0)
		 {
			 switch(event.type)
			 {
			 case ENET_EVENT_TYPE_CONNECT:
				 PINE_SERVER_INFO("A Client has connected from: {}:{}", event.peer->address.host, event.peer->address.port);
				 break;
			 case ENET_EVENT_TYPE_DISCONNECT:
				 PINE_SERVER_INFO("A Client has Disconnected from: {}:{}", event.peer->address.host, event.peer->address.port);
				 break;
			 case ENET_EVENT_TYPE_RECEIVE:
				 PINE_SERVER_INFO("A Packet of length {} containing {} from {} on channel {}", event.packet->dataLength, event.packet->data, event.peer->data, event.channelID);
			
				enet_packet_destroy(event.packet);
				break;
			 }
		 }
	 
	 }

	 void Networking::PineSendPacket(const char* text)
	 {
		 ENetPacket* packet = enet_packet_create(text, strlen(text) + 1, ENET_PACKET_FLAG_RELIABLE);
		 enet_peer_send(peer, 0, packet);
		 enet_host_flush(host);
	 }

	 void Networking::PineSendGlobalPacket(const char* text)
	 {
		 ENetPacket* packet = enet_packet_create(text, strlen(text) + 1, ENET_PACKET_FLAG_RELIABLE);
		 enet_host_broadcast(host, 0, packet);
		 enet_host_flush(host);
	 }
	int Networking::PineNetworkClose()
	{
		return 1;

	}

}