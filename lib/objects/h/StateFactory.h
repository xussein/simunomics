#ifndef LIB_OBJECTS_H_STATEFACTORY_H
#define LIB_OBJECTS_H_STATEFACTORY_H


#include "State.h"

class StateFactory {
public:
    static StateFactory & getInstance();
    void registerStateClass(StateClass stateClass, std::unique_ptr<State> (* creator)());
    std::unique_ptr<State> createState(StateClass stateClass);
    StateFactory(const StateFactory & stateFactory) = delete;            // deleting copy constructor to prevent multiple instances
    StateFactory operator=(const StateFactory & stateFactory) = delete;  // deleting operator= to prevent multiple instances
private:
    StateFactory() = default;
    std::unordered_map<StateClass, std::unique_ptr<State>(*)()> stateClassRegistry;
};


#endif  // LIB_OBJECTS_H_STATEFACTORY_H