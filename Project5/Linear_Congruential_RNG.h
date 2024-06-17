#pragma once

class LinConRNG {

private:
    unsigned long multiplier, constant, modulo;
    unsigned long seed;

public:
    LinConRNG(unsigned long m, unsigned long c, unsigned long mod, unsigned long seed) {
        this->multiplier = m;
        this->constant = c;
        this->modulo = mod;
        this->seed = seed;
    }

    double next();
};
