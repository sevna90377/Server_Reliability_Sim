#pragma once

#include <unordered_map>
#include "Server.h"

class Server_system
{
public:
    explicit Server_system(bool sample) {
        if (sample) {
            make_sample();
        }
    }

    //dla graczy
    Server* join_server(Player* player, Server* server);
    Server* assign_server(Player* player);
    Server* random_server();

    void print_info();

private:
    class Graph {

    public:
        Graph() = default;
        ~Graph() {
            delete_graph();
        }

        struct Element {
            Server* server;
            int weight;
            Element* next;
        };

        std::unordered_map<Server*, Element*> servers;

        void add_edge(Server* v1, Server* v2, int distance) {

            Graph::Element* newElement = new Graph::Element{ v2, distance, nullptr };
            if (servers[v1] == nullptr) {
                servers[v1] = newElement;
            }
            else {
                Graph::Element* current = servers[v1];
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newElement;
            }

            newElement = new Graph::Element{ v1, distance, nullptr };

            if (servers[v2] == nullptr) {
                servers[v2] = newElement;
            }
            else {
                Graph::Element* current = servers[v2];
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newElement;
            }
        }

    private:
        void delete_graph() {
            Graph::Element* current;
            Graph::Element* next;
            for (auto& pair : servers) {
                current = pair.second;
                while (current != nullptr) {
                    next = current->next;
                    delete current;
                    current = next;
                }
            }
        }
    };

    Graph server_graph;
    void make_sample();
};

