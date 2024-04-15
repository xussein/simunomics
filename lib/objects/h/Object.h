#ifndef LIB_OBJECTS_H_OBJECT_H
#define LIB_OBJECTS_H_OBJECT_H


#include <memory>

#include "State.h"

struct Position {
    int x;
    int y;
    int z;
};

class Object {
public:
    virtual void init() = 0;
    virtual void setState(std::shared_ptr<State> & state) = 0;
    virtual void update() = 0;
    virtual ~Object() = default;
protected:
    std::shared_ptr<State> state;
    Position position;
};


#endif  // LIB_OBJECTS_H_OBJECT_H