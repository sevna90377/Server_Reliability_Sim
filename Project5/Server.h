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
        maintenance_time = 0;
    }
    ~Server() = default;

    bool joinable;
    int ping;

private:
    std::string name;
    bool running;
    Type type;
    int capacity;
    int currently;
    double maintenance_time;

    //Shutdown *
    std::list<Player*> current_players;

public:
    void addPlayer(Player* player);
    void removePlayer(Player* player);
    std::string info();

    //shutdown();


private:
    void turnOn();
    void turnOff();
    void ping_calc();
    std::string type_toString();
};

