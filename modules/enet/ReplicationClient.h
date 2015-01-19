#ifndef __GODOT_MODULE_ENET_REPLICATION_CLIENT_H__
#define __GODOT_MODULE_ENET_REPLICATION_CLIENT_H__

#include "reference.h"
#include "ustring.h"

#include "ENetHostWrapper.h"
#include <enet/enet.h>

class ReplicationClient : public Reference
{
    OBJ_TYPE(ReplicationClient, Reference);

    ENetHostWrapper hostWrapper;
    ENetPeer * serverPeer = NULL;

    protected:
    static void _bind_methods();

    public:
    Error start();
    void disconnect();
    void connect_to(String host);
    void connect_locally();
    void service_tick();
}

#endif
