#include "normal_distribution_RNG.h"    


BoxMullerTransform* RNG::bmt = nullptr;
bool RNG::initiated = false;


void RNG::init(){
    bmt = new BoxMullerTransform();
    initiated = true;
}

double RNG::getNormal() {
    if(!initiated){
        init();
    }
    return bmt->next();
}

double RNG::getLinear() {
    if (!initiated) {
        init();
    }
    return bmt->nextLinear();
}