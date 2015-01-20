#ifndef __GODOT_MODULE_ENET_HOST_WRAPPER_H__
#define __GODOT_MODULE_ENET_HOST_WRAPPER_H__

#include "error_list.h"

#include <enet/enet.h>
#include <stdint.h>

class ENetHostWrapper
{
    ENetAddress address;
    ENetHost * host = NULL;

    public:

    virtual ~ENetHostWrapper();

    Error init(int max_connections, int max_channels, int port = -1);
    bool get_event(ENetEvent& event, int waitForMillis = 0);
    void disconnect_from(ENetPeer * peer);
    void connect_to(ENetAddress& address, ENetPeer * peer);
    Error send_packet_data(ENetPeer * peer, uint8_t * buffer, int buffer_length);
};

#endif
