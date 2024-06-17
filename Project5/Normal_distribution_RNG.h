#pragma once

#include "Box_Muller_Transform.h"

class RNG {
private:
    static BoxMullerTransform* bmt;
    static bool initiated;
public:
    static void init();
    static double getNormal();
    static double getLinear();
};