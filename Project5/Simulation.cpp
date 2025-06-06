#include "Simulation.h"

void Simulation::start() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    running = true;
    
    servers = new Server_system(true);
    
    for (int i = 0; i < max_players; i++) {
        Player* p = new Player(i, servers);
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
    }
    double mean = 0;
    for (auto player : players) {
        mean += player->satisfaction;
    }
    std::cout << "�rednia satysfakcja graczy po zako�czeniu symulacji: " << mean / players.size() << std::endl;
}

void Simulation::stop() {
    for (Player* player : players) {
        player->stop();
    }
    running = false;
}