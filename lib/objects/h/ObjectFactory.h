#ifndef LIB_OBJECTS_H_OBJECTFACTORY_H
#define LIB_OBJECTS_H_OBJECTFACTORY_H


#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>      // TODO: for debugging

#include "Object.h"

enum class ObjectClass {
    House,
    HighwaySection,
    RailwaySection,
    Factory,
    Mine
};

class ObjectFactory {
public:
    static ObjectFactory & getInstance();
    ObjectFactory(const ObjectFactory & objectFactory) = delete;            // deleting copy constructor to prevent multiple instances
    ObjectFactory operator=(const ObjectFactory & objectFactory) = delete;  // deleting operator= to prevent multiple instances

    // std::unique_ptr<Object> createObject(ObjectClass objectClass);       // TODO: return version of the function, perhaps I should create other class for object registry
    void createObject(ObjectClass objectClass);
    void updateObject(int objectId, std::shared_ptr<State> state);          // TODO: create State class for objects (and maybe more)
    void registerObjectClass(ObjectClass objectClass, std::unique_ptr<Object> (* creator)());    
private:
    ObjectFactory() = default;

    std::vector<std::unique_ptr<Object>> objectRegistry;
    std::unordered_map<ObjectClass, std::unique_ptr<Object>(*)()> objectClassRegistry;
};


#endif  // LIB_OBJECTS_H_OBJECTFACTORY_H