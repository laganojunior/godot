#ifndef __GODOT_MODULE_ENET_HOST_WRAPPER_H__
#define __GODOT_MODULE_ENET_HOST_WRAPPER_H__

#include "reference.h"

#include <enet/enet.h>

class ENetHostWrapper : public Reference
{
    OBJ_TYPE(ENetHostWrapper, Reference);

    ENetAddress address;
    ENetHost * host = NULL;

    int next_peer_id = 0;
    Map<ENetPeer*, uint32_t> peer_id_map;
    Map<uint32_t, ENetPeer*> id_peer_map;

    uint32_t add_peer(ENetPeer* peer);
    void remove_peer_id(uint32_t peer_id);

    public:

    virtual ~ENetHostWrapper();

    Error init_as_client(int max_connections, int max_channels);
    Error init_as_server(int max_connections, int max_channels, int port);
    void tick();

    Error send_connection_request(String hostname, int port, int max_channels);
    Error send_disconnection_request_to(uint32_t peer_id);
    Error send_data_to(uint32_t peer_id, Variant& var, int channel, bool reliable);

    // on_disconnection(int peer_id) {}

    protected:
    static void _bind_methods();
};

#endif
