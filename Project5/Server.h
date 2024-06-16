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

    Server(std::string name, Type type, int capacity, float error_percent) : name(std::move(name)), type(type), capacity(capacity), error_percent(error_percent), running(false) {
        currently = 0;
        ping = 0;
        joinable = true;
    }
    ~Server() = default;

    bool joinable;

private:
    std::string name;
    bool running;
    Type type;
    int capacity;
    int currently;
    int ping;
    float error_percent;

    //Shutdown *
    std::list<Player*> current_players;

public:
    void addPlayer(Player* player);
    void removePlayer();
    std::string info();

    //shutdown();


protected:
    void turnOn();
    void turnOff();
    void ping_calc();
    std::string type_toString();
};

