#include "Linear_Congruential_RNG.h"

double LinConRNG::next() {
    seed = (multiplier * seed + constant) % modulo;
    return static_cast<double>(seed) / modulo;
}