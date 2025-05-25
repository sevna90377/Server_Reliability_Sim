#pragma once

#include <unordered_map>
#include "Server.h"
#include <queue>
#include <set>

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
    bool assign_server(Player* player, Server* server);
    Server* random_server();
    int calc_distance(Server* start, Server* server);

    void print_info();
    //void tick();

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

        Server* find_closest(Server* start, Server::Type type) {
            if (start == nullptr) {
                find_closest(servers.begin()->first, type);
            }

            std::queue<Server*> to_visit;
            std::set<Server*> visited;

            to_visit.push(start);
            visited.insert(start);

            while (!to_visit.empty()) {
                Server* current = to_visit.front();
                to_visit.pop();

                if (current->joinable && current->type == type) {
                    return current;
                }

                Element* neighbors = servers[current];
                while (neighbors != nullptr) {
                    if (visited.find(neighbors->server) == visited.end()) {
                        to_visit.push(neighbors->server);
                        visited.insert(neighbors->server);
                    }
                    neighbors = neighbors->next;
                }
            }
            return nullptr; 
        }
        Server* find_closest(Server* start) {
            if (start == nullptr) {
                find_closest(servers.begin()->first);
            }

            std::queue<Server*> to_visit;
            std::set<Server*> visited;

            to_visit.push(start);
            visited.insert(start);

            while (!to_visit.empty()) {
                Server* current = to_visit.front();
                to_visit.pop();

                if (current->joinable) {
                    return current;
                }

                Element* neighbors = servers[current];
                while (neighbors != nullptr) {
                    if (visited.find(neighbors->server) == visited.end()) {
                        to_visit.push(neighbors->server);
                        visited.insert(neighbors->server);
                    }
                    neighbors = neighbors->next;
                }
            }
            return nullptr;
        }
        int calc_distance(Server* start, Server* end) {
            std::unordered_map<Server*, bool> visited;
            int distance = dfs_sum_of_distances(start, end, visited);
            return (distance == INT_MAX) ? -1 : distance;
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

        int dfs_sum_of_distances(Server* current, Server* end, std::unordered_map<Server*, bool>& visited) {
            if (current == end) {
                return 0;
            }

            visited[current] = true;
            int min_distance = INT_MAX;

            Element* neighbor = servers[current];
            while (neighbor != nullptr) {
                if (!visited[neighbor->server]) {
                    int dist = dfs_sum_of_distances(neighbor->server, end, visited);
                    if (dist != INT_MAX) {
                        min_distance = std::min(min_distance, dist + neighbor->weight);
                    }
                }
                neighbor = neighbor->next;
            }

            visited[current] = false;
            return min_distance;
        }
    };

    Graph server_graph;
    void make_sample();
};

