#pragma once

#include <string>
#include <list>

#include "Player.h"

class Server {

public:
    enum Type {
        PvE,
        PvP,
        RP,
    };

    Server(std::string name, Type type, int capacity, float error_percent) : name(std::move(name)), type(type), capacity(capacity), running(false) {
        currently = 0;
        ping = 0;
        joinable = true;
        running = true;
        maintenance_time = 10;
    }
    ~Server() = default;

    bool joinable;
    int ping;
    Type type;

private:
    std::string name;
    bool running;
    int capacity;
    int currently;
    double maintenance_time;

    std::list<Player*> current_players;

public:
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    std::string info();
    void tick();

private:
    void ping_calc();
    std::string type_toString();
};

