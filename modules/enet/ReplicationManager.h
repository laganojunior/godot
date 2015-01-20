#ifndef __GODOT_MODULE_ENET_REPLICATION_MANAGER_H__
#define __GODOT_MODULE_ENET_REPLICATION_MANAGER_H__

#include "scene/main/node.h"
#include "reference.h"

#include "ENetHostWrapper.h"
#include <enet/enet.h>

class ReplicationManager : public Reference
{
    OBJ_TYPE(ReplicationManager, Reference);

    ENetHostWrapper hostWrapper;
    Vector<ENetPeer*> client_peers;
    Map<String, Node*> replicate_nodes;

    void send_update_data_for_node(String name, Node * node);

    void broadcast_data(uint8_t * buffer, int len);

    protected:
    static void _bind_methods();

    public:
    Error start();
    void service_tick();
    void add_static_replicate_node(String name, Node * node);
};

#endif
