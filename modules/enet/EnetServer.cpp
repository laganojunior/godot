#include "EnetServer.h"

void EnetServer :: _bind_methods()
{
    ObjectTypeDB::bind_method("listen", &EnetServer::listen);
}

EnetServer :: ~EnetServer()
{
    if (server)
        enet_host_destroy(server);
}

Error EnetServer :: listen(uint16_t port)
{
    if (server)
        enet_host_destroy(server);

    address.host = ENET_HOST_ANY;
    address.port = port;

    server = enet_host_create(&address, MAX_CONNECTIONS, MAX_CHANNELS, IN_BANDWIDTH, OUT_BANDWIDTH);

    if (server == NULL)
        return FAILED;

    return OK;
}
