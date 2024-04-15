#ifndef LIB_OBJECTS_H_STATE_H
#define LIB_OBJECTS_H_STATE_H


#include <memory>
#include <unordered_map>

enum class StateClass {
    Operating,
    Idle
};

class State {
public:
    virtual void handle() = 0;
    virtual ~State() = default;
};


#endif  // LIB_OBJECTS_H_STATE_H