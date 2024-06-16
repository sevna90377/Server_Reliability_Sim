#include "Simulation.h"
#include <thread>

void Simulation::start() {
    running = true;
    
    servers = new Server_system(true);
    
    for (int i = 0; i < max_players; i++) {
        Player* p = new Player(i);
        players.emplace_back(p);
        p->start();
    }

    simulationThread = std::thread(&Simulation::run, this);
    simulationThread.join();
}

void Simulation::run() {
    while (running) {
        if (++tick >= max_ticks) stop();
        servers->print_info();
        for (Player* player : players) {
            player->synchronise();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Simulation::stop() {
    running = false;
}