#include "Server_system.h"

void Server_system::make_sample() {

    Server* NE = new Server("NE", Server::PvE, 150, 10);
    Server* SE = new Server("SE", Server::PvP, 200, 10);
    Server* EU = new Server("EU", Server::PvP, 170, 12);
    Server* AF = new Server("AF", Server::RP, 120, 15);
    Server* AS = new Server("AS", Server::PvE, 300, 11);
    Server* AU = new Server("AU", Server::PvP, 125, 18);

    server_graph.add_edge(NE, SE, 126);
    server_graph.add_edge(NE, AS, 236);
    server_graph.add_edge(NE, AU, 208);
    server_graph.add_edge(NE, EU, 104);
    server_graph.add_edge(AU, AS, 309);
    server_graph.add_edge(AS, EU, 199);
    server_graph.add_edge(AS, AF, 323);
    server_graph.add_edge(EU, AF, 170);
}

Server* Server_system::join_server(Player* player, Server* server) {
        if (!assign_server(player, server)) {
            Server* s_type = server_graph.find_closest(server, server->type);
            if (server_graph.calc_distance(server, s_type) - player->ping_tolerance < 100) {
                server = assign_server(player, s_type) ? s_type : nullptr;
                
            }
            else {
                Server* s_close = server_graph.find_closest(server);
                server = assign_server(player, s_close) ? s_close : nullptr;
            }
        }
    return server;
}

bool Server_system::assign_server(Player* player, Server* server)
{
    if (server == nullptr) {
        return false;
    }
    if (server->joinable) {
        server->addPlayer(player);
        return true;
    }
    else {
        return false;
    }
}

Server* Server_system::random_server()
{
    int index = int(RNG::getLinear() * 100) % server_graph.servers.size();
    auto it = server_graph.servers.begin();
    std::advance(it, index);
    return it->first;
}

int Server_system::calc_distance(Server* start, Server* server)
{
    return server_graph.calc_distance(start, server);
}

void Server_system::print_info() {
    system("cls");
    std::cout << "Server\tTyp\tPojemnosc\n";

    for (auto& pair : server_graph.servers) {
        std::cout << pair.first->info();
    }
}

//void Server_system::tick()
//{
//    for (auto server : server_graph.servers) {
//        server.first->tick();
//    }
//}
