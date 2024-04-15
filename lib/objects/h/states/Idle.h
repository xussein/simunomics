#ifndef LIB_OBJECTS_H_STATES_IDLE_H
#define LIB_OBJECTS_H_STATES_IDLE_H


#include <iostream>     // TODO: consider removal, just testing

#include "../State.h"

class Idle: public State {
public:
    void handle() override;
};


#endif  // LIB_OBJECTS_H_STATES_IDLE_H