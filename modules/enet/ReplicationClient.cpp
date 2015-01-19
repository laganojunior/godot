#include "print_string.h"

#include "ReplicationClient.h"
#include "ReplicationConstants.h"

void ReplicationClient :: _bind_methods()
{
    ObjectTypeDB::bind_method("start", &ReplicationClient :: start);
    ObjectTypeDB::bind_method("disconnect", &ReplicationClient :: disconnect);
    ObjectTypeDB::bind_method("connect_to", &ReplicationClient :: connect_to);
    ObjectTypeDB::bind_method("connect_locally", &ReplicationClient :: connect_locally);
    ObjectTypeDB::bind_method("service_tick", &ReplicationClient :: service_tick);
}

Error ReplicationClient :: start()
{
    Error err = hostWrapper.init(1, 1);

    if (err == OK)
        print_line("Replication client started");
    else
        print_line("Error starting replication client");

    return err;
}

void ReplicationClient :: disconnect()
{
    hostWrapper.disconnect_from(serverPeer);
}

void ReplicationClient :: connect_to(String host)
{
    ENetAddress address;
    enet_address_set_host(&address, host.utf8().get_data());
    address.port = REPLICATION_MANAGER_PORT;

    hostWrapper.connect_to(address, serverPeer);
}

void ReplicationClient :: connect_locally()
{
    return connect_to("127.0.0.1");
}

void ReplicationClient :: service_tick()
{
    ENetEvent event;

    while (hostWrapper.get_event(event))
    {
        print_line("Client got event?");

        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
            {
                print_line("Client got connection!");
            } break;

            case ENET_EVENT_TYPE_RECEIVE:
            {
                print_line("Client got packet????");
                enet_packet_destroy(event.packet);
            } break;

            case ENET_EVENT_TYPE_DISCONNECT:
            {
                print_line("Client got disconnect?!?!?!");
            } break;
        }
    }
}
