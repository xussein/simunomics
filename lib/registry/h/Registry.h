#ifndef LIB_REGISTRY_H_REGISTRY_H
#define LIB_REGISTRY_H_REGISTRY_H


#include "../../player/h/Company.h"

class Registry {
public:
    static Registry & getInstance();
private:
    Registry();
};


#endif  // LIB_REGISTRY_H_REGISTRY_H