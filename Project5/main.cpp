#include <iostream>
#include "Simulation.h"
#include <thread>


int main() {
    std::cout << "Poczatek symulacji dla standardowego grafu serwerow, przy liczbie graczy 10000. Planowana liczba krokow: 1000" << std::endl;
    Simulation* simulation = new Simulation(3, 1000);
    simulation->start();
    return 0;
}