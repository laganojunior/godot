#ifndef __GODOT_MODULE_ENET_PEER_H__
#define __GODOT_MODULE_ENET_PEER_H__

#include "reference.h"

#include <enet/enet.h>

class EnetServer : public Reference
{
    OBJ_TYPE(EnetServer, Reference);

    ENetAddress address;
    ENetHost * server = NULL;

    const int MAX_CONNECTIONS = 32;
    const int MAX_CHANNELS = 2;
    const int IN_BANDWIDTH = 0; // Infinite
    const int OUT_BANDWIDTH = 0; // Infinite

    protected:

    static void _bind_methods();

    public:

    virtual ~EnetServer();

    Error listen(uint16_t port);

};

#endif
