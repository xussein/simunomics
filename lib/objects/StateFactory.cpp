#include "h/StateFactory.h"

StateFactory & StateFactory::getInstance(){
    static StateFactory instance;
    return instance;
}

void StateFactory::registerStateClass(StateClass stateClass, std::unique_ptr<State> (*creator)()) {
    stateClassRegistry[stateClass] = creator;
}

std::unique_ptr<State> StateFactory::createState(StateClass stateClass) {
    auto sC = stateClassRegistry.find(stateClass);
    if (sC != stateClassRegistry.end()) {
        return sC->second();
    } else {
        // TODO: throw exception if state class is unregistered
    }
    return nullptr;
}