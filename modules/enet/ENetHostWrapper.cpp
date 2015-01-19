#include "ENetHostWrapper.h"

#include "print_string.h"

#include <iostream>

ENetHostWrapper :: ~ENetHostWrapper()
{
    if (host)
        enet_host_destroy(host);
}

Error ENetHostWrapper :: init(int max_connections, int max_channels, int port)
{
    if (host)
    {
        enet_host_destroy(host);
    }

    if (port == -1)
    {
        // Don't listen on any port
        host = enet_host_create(NULL, max_connections, max_channels, 0, 0);
    }
    else
    {
        // Listen to target port
        address.host = ENET_HOST_ANY;
        address.port = port;

        host = enet_host_create(&address, max_connections, max_channels, 0, 0);
    }

    print_line("Hosted?");
    std :: cout << address.host << " " << address.port << std::endl;

    if (host == NULL)
        return FAILED;

    return OK;
}

bool ENetHostWrapper :: get_event(ENetEvent& event, int waitForMillis)
{
    bool received = (enet_host_service(host, &event, waitForMillis) > 0);
    return received;
}

void ENetHostWrapper :: disconnect_from(ENetPeer * peer)
{
    enet_peer_disconnect(peer, 0);
    enet_host_flush(host);
}

void ENetHostWrapper :: connect_to(ENetAddress& address, ENetPeer * peer)
{
    print_line("Connecting?");
    std :: cout << address.host << " " << address.port << std::endl;
    peer = enet_host_connect(host, &address, 1, 0);
    enet_host_flush(host);
}

//Error ENetHostWrapper :: send_packet_data(EnetPeerWrapper& peerWrapper, uint8_t * buffer, int buffer_length)
//{
//    ENetPacket * packet = enet_packet_create(buffer, buffer_length, ENET_PACKET_FLAG_RELIABLE);
//
//    if (enet_peer_send(peerWrapper.peer, 0, packet))
//        return FAILED;
//
//    return OK;
//}
