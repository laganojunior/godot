#include "register_types.h"
#include "object_type_db.h"

#include "ReplicationManager.h"
#include "ReplicationClient.h"

void register_enet_types()
{
    ObjectTypeDB::register_type<ReplicationManager>();
    ObjectTypeDB::register_type<ReplicationClient>();
}

void unregister_enet_types()
{}
