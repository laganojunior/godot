#include "register_types.h"
#include "object_type_db.h"

#include "ENetHostWrapper.h"

void register_enet_types()
{
    ObjectTypeDB::register_type<ENetHostWrapper>();
}

void unregister_enet_types()
{}
