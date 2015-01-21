#include "ENetHostWrapper.h"

#include "io/marshalls.h"
#include "print_string.h"

uint32_t ENetHostWrapper :: add_peer(ENetPeer * peer)
{
    if (peer_id_map.has(peer))
    {
        // Peer already exists?
        return peer_id_map[peer];
    }

    uint32_t new_id = next_peer_id;
    next_peer_id++;

    peer_id_map[peer] = new_id;
    id_peer_map[new_id] = peer;

    return new_id;
}

void ENetHostWrapper :: remove_peer_id(uint32_t peer_id)
{
    if (!id_peer_map.has(peer_id))
        return;

    ENetPeer * peer = id_peer_map[peer_id];
    id_peer_map.erase(peer_id);
    peer_id_map.erase(peer);
}

ENetHostWrapper :: ~ENetHostWrapper()
{
    if (host)
        enet_host_destroy(host);
}

Error ENetHostWrapper :: init_as_client(int max_connections, int max_channels)
{
    if (host)
    {
        enet_host_destroy(host);
    }

    host = enet_host_create(NULL, max_connections, max_channels, 0, 0);

    if (host == NULL)
        return FAILED;

    return OK;
}

Error ENetHostWrapper :: init_as_server(int max_connections, int max_channels, int port)
{
    if (host)
    {
        enet_host_destroy(host);
    }

    // Listen to target port
    address.host = ENET_HOST_ANY;
    address.port = port;

    host = enet_host_create(&address, max_connections, max_channels, 0, 0);

    if (host == NULL)
        return FAILED;

    return OK;
}

void ENetHostWrapper :: tick()
{
    ENetEvent event;
    while (enet_host_service(host, &event, 0))
    {
        switch(event.type)
        {
            case ENET_EVENT_TYPE_CONNECT:
            {
                uint32_t peer_id = add_peer(event.peer);

                emit_signal("on_connection", peer_id);
            } break;

            case ENET_EVENT_TYPE_RECEIVE:
            {
                Map<ENetPeer *, uint32_t>::Element * elem = peer_id_map.find(event.peer);
                if (elem == NULL)
                {
                    print_line("ENetHostWrapper: packet from unknown peer");
                    break;
                }

                Variant var;
                Error err = decode_variant(var, event.packet->data, event.packet->dataLength);

                if (err != OK)
                {
                    print_line("ENetHostWrapper: error decoding packet");
                    enet_packet_destroy(event.packet);
                    break;
                }

                emit_signal("on_data_received", elem->value(), var);

                enet_packet_destroy(event.packet);
            } break;

            case ENET_EVENT_TYPE_DISCONNECT:
            {
                Map<ENetPeer *, uint32_t>::Element * elem = peer_id_map.find(event.peer);
                if (elem == NULL)
                {
                    print_line("ENetHostWrapper: received disconnect from unknown peer");
                    break;
                }

                uint32_t peer_id = elem->value();

                emit_signal("on_disconnection", peer_id);
                remove_peer_id(peer_id);
            } break;
        }
    }
}

Error ENetHostWrapper :: send_connection_request(String hostname, int port, int max_channels)
{
    ENetAddress peer_address;
    enet_address_set_host(&peer_address, hostname.utf8().get_data());
    peer_address.port = port;

    enet_host_connect(host, &peer_address, max_channels, 0);

    return OK;
}

Error ENetHostWrapper :: send_disconnection_request_to(uint32_t peer_id)
{
    Map<uint32_t, ENetPeer *>::Element * elem = id_peer_map.find(peer_id);

    if (elem == NULL)
        return FAILED;

    enet_peer_disconnect(elem -> value(), 0);

    return OK;
}

Error ENetHostWrapper :: send_data_to(uint32_t peer_id, Variant& var, int channel, bool reliable)
{
    Map<uint32_t, ENetPeer *>::Element * elem = id_peer_map.find(peer_id);

    if (elem == NULL)
        return FAILED;


    int len;
    Error err = encode_variant(var, NULL, len);

    if (err) {
        return err;
    }

    uint8_t * buffer = (uint8_t*)alloca(len);
    if (!buffer) {
        return ERR_OUT_OF_MEMORY;
    }

    err = encode_variant(var, buffer, len);
    if (err) {
        return err;
    }

    int packet_flags = 0;
    if (reliable)
        packet_flags |= ENET_PACKET_FLAG_RELIABLE;

    ENetPacket * packet = enet_packet_create(buffer, len, packet_flags);
    enet_peer_send(elem->value(), channel, packet);

    return OK;
}

void ENetHostWrapper :: _bind_methods()
{
    ObjectTypeDB::bind_method("init_as_client", &ENetHostWrapper :: init_as_client);
    ObjectTypeDB::bind_method("init_as_server", &ENetHostWrapper :: init_as_server);
    ObjectTypeDB::bind_method("tick", &ENetHostWrapper :: tick);
    ObjectTypeDB::bind_method("send_connection_request", &ENetHostWrapper :: send_connection_request);
    ObjectTypeDB::bind_method("send_disconnection_request_to", &ENetHostWrapper :: send_disconnection_request_to);
    ObjectTypeDB::bind_method("send_data_to", &ENetHostWrapper :: send_data_to);

    ADD_SIGNAL(MethodInfo("on_connection", PropertyInfo(Variant::INT, "peer_id")));
    ADD_SIGNAL(MethodInfo("on_data_received"));
    ADD_SIGNAL(MethodInfo("on_disconnection", PropertyInfo(Variant::INT, "peer_id")));
}
