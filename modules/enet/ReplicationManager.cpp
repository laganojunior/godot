#include "print_string.h"

#include "ReplicationManager.h"
#include "ReplicationConstants.h"

void ReplicationManager :: _bind_methods()
{
    ObjectTypeDB::bind_method("start", &ReplicationManager :: start);
    ObjectTypeDB::bind_method("service_tick", &ReplicationManager :: service_tick);
}

Error ReplicationManager :: start()
{
    Error err = hostWrapper.init(REPLICATION_MANAGER_SERVER_CONNECTIONS, 1, REPLICATION_MANAGER_PORT);


    if (err == OK)
        print_line("Replication manager started");
    else
        print_line("Error starting replication manager");

    return err;
}

void ReplicationManager :: service_tick()
{
    ENetEvent event;

    while (hostWrapper.get_event(event))
    {
        print_line("Got event?");

        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
            {
                print_line("Got connection!");
            } break;

            case ENET_EVENT_TYPE_RECEIVE:
            {
                print_line("Got packet????");
                enet_packet_destroy(event.packet);
            } break;

            case ENET_EVENT_TYPE_DISCONNECT:
            {
                print_line("Disconnect?!?!?!");
            } break;
        }
    }
}
