#include "h/ObjectFactory.h"

ObjectFactory & ObjectFactory::getInstance() {
    static ObjectFactory instance;
    return instance;
}

void ObjectFactory::registerObjectClass(const ObjectClass objectClass, std::unique_ptr<Object>(* creator)()) {    
    objectClassRegistry[objectClass] = creator;
}

// TODO: return version of the function, perhaps I should create other class for object registry
// std::unique_ptr<Object> ObjectFactory::createObject(const ObjectClass objectClass) {    
//     auto oC = objectClassRegistry.find(objectClass);
//     if (oC != objectClassRegistry.end()) {
//         return oC->second();
//     }
//     return nullptr;
// }

void ObjectFactory::createObject(ObjectClass objectClass) {
    auto oC = objectClassRegistry.find(objectClass);
    if (oC != objectClassRegistry.end()) {
        objectRegistry.push_back(oC->second());
    } else {
        std::cerr << "[ERROR] class name not found objectClassRegistry" << std::endl;
        // TODO: throw exception if class is not registered
    }
}

void ObjectFactory::updateObject(int objectId, std::shared_ptr<State> state) {
    if (objectId >= 0 && objectId < objectRegistry.size()) {
        objectRegistry[objectId]->setState(state);
        objectRegistry[objectId]->update();
    } else {
        std::cerr << "[ERROR] object id not found in objectRegistry" << std::endl;
        // TODO: throw exception if object with specified ID does not exist
    }
}
