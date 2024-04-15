#ifndef LIB_OBJECTS_H_STATES_OPERATING_H
#define LIB_OBJECTS_H_STATES_OPERATING_H


#include <iostream>     // TODO: consider removal, just testing

#include "../State.h"

class Operating: public State {
public:
    void handle() override;
};


#endif  // LIB_OBJECTS_H_STATES_OPERATING_H