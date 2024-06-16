#pragma once

#include <thread>
#include <vector>
#include "Player.h"
#include "Server_system.h"

class Simulation {

public:
    Simulation(int max_players, int max_ticks) {
        this->max_players = max_players;
        this->max_ticks = max_ticks;
        tick = 0;
        running = false;
    }
    ~Simulation() {
        this->stop();
        for (auto* player : players) {
            delete player;
        }
    };

    void start();
    void stop();

private:
    int max_players;
    int max_ticks;
    int tick;
    bool running;

    void run();

    //zmienne potrzebne do synchronizacji graczy
    std::thread simulationThread;
    std::vector<Player*> players;

    Server_system* servers;
};
