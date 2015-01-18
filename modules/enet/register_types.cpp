#include "register_types.h"
#include "object_type_db.h"

#include "EnetServer.h"

void register_enet_types()
{
    ObjectTypeDB::register_type<EnetServer>();
}

void unregister_enet_types()
{}
