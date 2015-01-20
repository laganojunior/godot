#include "io/marshalls.h"
#include "print_string.h"

#include "ReplicationClient.h"
#include "ReplicationConstants.h"

void ReplicationClient :: handle_packet_data(uint8_t* data, int len)
{
    Variant packet_var;
    Error err = decode_variant(packet_var, data, len);

    if (err)
    {
        print_line("Replication Client: Error parsing packet data");
        return;
    }

    Dictionary packet_dict = (Dictionary)packet_var;

    if (!packet_dict.has("type"))
    {
        print_line("Replication Client: packet has no type!");
        return;
    }

    int type = (int)packet_dict["type"];

    switch(type)
    {
        case NODE_UPDATE:
        {
            if (!packet_dict.has("name"))
            {
                print_line("Replication Client: node update packet has no name!");
                return;
            }

            if (!packet_dict.has("data"))
            {
                print_line("Replication Client: node update packet has no data!");
                return;
            }

            Map<String, Node *>::Element * elem = replicate_nodes.find(packet_dict["name"]);

            if (elem == NULL)
            {
                print_line("Replication Client: node update packet node not found!");
                return;
            }

            Node * node = elem->value();
            Array args;
            args.push_back(packet_dict["data"]);

            node->callv("process_replicate_update_data", args);
        }break;

        default:
            print_line("Replication Client: unknown pakcet type!!");
    }
}

void ReplicationClient :: _bind_methods()
{
    ObjectTypeDB::bind_method("start", &ReplicationClient :: start);
    ObjectTypeDB::bind_method("disconnect", &ReplicationClient :: disconnect);
    ObjectTypeDB::bind_method("connect_to", &ReplicationClient :: connect_to);
    ObjectTypeDB::bind_method("connect_locally", &ReplicationClient :: connect_locally);
    ObjectTypeDB::bind_method("service_tick", &ReplicationClient :: service_tick);
    ObjectTypeDB::bind_method("add_static_replicate_node", &ReplicationClient :: add_static_replicate_node);
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
    enet_address_set_host(&server_address, host.utf8().get_data());
    server_address.port = REPLICATION_MANAGER_PORT;

    hostWrapper.connect_to(server_address, serverPeer);
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
                print_line("Replication client got connection!");
                serverPeer = event.peer;
            } break;

            case ENET_EVENT_TYPE_RECEIVE:
            {
                handle_packet_data(event.packet->data, event.packet->dataLength);
                enet_packet_destroy(event.packet);
            } break;

            case ENET_EVENT_TYPE_DISCONNECT:
            {
                print_line("Replication client got disconnect!");
                enet_peer_reset(serverPeer);
                serverPeer = NULL;
            } break;
        }
    }
}

void ReplicationClient :: add_static_replicate_node(String name, Node * node)
{
    replicate_nodes.insert(name, node);
}
