#include "Box_Muller_Transform.h"

double BoxMullerTransform::next()
{
    if (areThereLeftovers) {
        areThereLeftovers = false;
        return leftovers;
    }
    else {
        return calc();
    }
}

double BoxMullerTransform::nextLinear()
{
    return rng->next();
}

double BoxMullerTransform::calc()
{
    double U1 = rng->next();
    double U2 = rng->next();
    calcRadius(U1);
    calcTheta(U2);

    leftovers = ((radius * sin(theta)) + 2.5) / 5.0;
    areThereLeftovers = true;
    return ((radius * cos(theta)) + 2.5) / 5.0;
}

void BoxMullerTransform::calcRadius(double U)
{
    radius = sqrt(-2 * log(U));
}

void BoxMullerTransform::calcTheta(double U)
{
    theta = 2 * M_PI * U;
}