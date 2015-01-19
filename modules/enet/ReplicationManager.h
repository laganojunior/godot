#ifndef __GODOT_MODULE_ENET_REPLICATION_MANAGER_H__
#define __GODOT_MODULE_ENET_REPLICATION_MANAGER_H__

#include "reference.h"

#include "ENetHostWrapper.h"
#include <enet/enet.h>

class ReplicationManager : public Reference
{
    OBJ_TYPE(ReplicationManager, Reference);

    ENetHostWrapper hostWrapper;

    protected:
    static void _bind_methods();

    public:
    Error start();

    void service_tick();
};

#endif
