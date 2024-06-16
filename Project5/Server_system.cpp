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

void Server_system::print_info() {
    system("cls");
    std::cout << "Server\tTyp\tPojemnosc\n";

    for (auto& pair : server_graph.graph) {
        std::cout << pair.first->info();
    }
}
