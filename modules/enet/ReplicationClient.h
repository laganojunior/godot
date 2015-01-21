#ifndef __GODOT_MODULE_ENET_REPLICATION_CLIENT_H__
#define __GODOT_MODULE_ENET_REPLICATION_CLIENT_H__
/*
#include "scene/main/node.h"
#include "reference.h"
#include "ustring.h"

#include "ENetHostWrapper.h"
#include <enet/enet.h>

class ReplicationClient : public Reference
{
    OBJ_TYPE(ReplicationClient, Reference);

    ENetHostWrapper hostWrapper;
    ENetAddress server_address;
    ENetPeer * serverPeer = NULL;
    Map<String, Node *> replicate_nodes;

    void handle_packet_data(uint8_t * data, int len);

    protected:
    static void _bind_methods();

    public:
    Error start();
    void disconnect();
    void connect_to(String host);
    void connect_locally();
    void service_tick();
    void add_static_replicate_node(String name, Node * node);
};
*/
#endif
