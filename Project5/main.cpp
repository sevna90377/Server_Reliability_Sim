#include <iostream>
#include "Simulation.h"

int main() {
    std::cout << "Poczatek symulacji dla standardowego grafu serwerow, przy liczbie graczy 10000. Planowana liczba krokow: 1000" << std::endl;
    Simulation* simulation = new Simulation(1000, 100);
    simulation->start();
    return 0;
}