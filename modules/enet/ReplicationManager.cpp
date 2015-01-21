#include "io/marshalls.h"
#include "print_string.h"

#include "ReplicationManager.h"
#include "ReplicationConstants.h"

#include <iostream>
/*
void ReplicationManager :: send_update_data_for_node(String name, Node * node)
{
    Array empty_args;
    Variant update_data = node->callv("get_replicate_update_data", empty_args);

    if (update_data.get_type() != Variant::Type::NIL)
    {
        Dictionary full_packet;
        full_packet["type"] = (int)NODE_UPDATE;
        full_packet["name"] = name;
        full_packet["data"] = update_data;

        int len;
        Error err = encode_variant(full_packet, NULL, len);

        if (err) {
            print_line("Error during encoding update data");
            return;
        }

        uint8_t * buffer = (uint8_t*)alloca(len);
        if (!buffer) {
            print_line("Ran out of memory during encoding update data");
            return;
        }

        err = encode_variant(full_packet, buffer, len);
        if (err) {
            print_line("Error during encoding update data");
            return;
        }

        broadcast_data(buffer, len);
    }
}

void ReplicationManager :: broadcast_data(uint8_t * buffer, int len)
{
    for (int i = 0; i < client_peers.size(); i++)
    {
        hostWrapper.send_packet_data(client_peers[i], buffer, len);
    }
}

void ReplicationManager :: _bind_methods()
{
    ObjectTypeDB::bind_method("start", &ReplicationManager :: start);
    ObjectTypeDB::bind_method("service_tick", &ReplicationManager :: service_tick);
    ObjectTypeDB::bind_method("add_static_replicate_node", &ReplicationManager :: add_static_replicate_node);
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

    // Send update ticks from registered replicate nodes
    for (Map<String, Node*>::Element * elem = replicate_nodes.front();
         elem != NULL;
         elem = elem->next())
    {
        String name = elem->key();
        Node * node = elem->value();
        send_update_data_for_node(name, node);
    }

    // Process received events
    ENetEvent event;
    while (hostWrapper.get_event(event))
    {
        print_line("Got event?");

        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
            {
                print_line("Replication Manager got connection!");
                client_peers.push_back(event.peer);
            } break;

            case ENET_EVENT_TYPE_RECEIVE:
            {
                enet_packet_destroy(event.packet);
            } break;

            case ENET_EVENT_TYPE_DISCONNECT:
            {
                print_line("Replication Manager got disconnection!");
                client_peers.erase(event.peer);
            } break;
        }
    }
}

void ReplicationManager :: add_static_replicate_node(String name, Node * node)
{
    replicate_nodes.insert(name, node);
}
*/
