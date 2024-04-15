#ifndef LIB_OBJECTS_H_FACTORY_H
#define LIB_OBJECTS_H_FACTORY_H


#include "Object.h"

class Factory : public Object {
public:
    void init() override;
    [[nodiscard]] int getProductivity() const;
    [[nodiscard]] int getLocation() const;
    void setState(std::shared_ptr<State> & state) override;
    void update() override;
//    ~Factory() override = default;       TODO: read about implementations of virtual destructors
private:
    int location;                       // TODO: create proper struct for location
    int dailyProductProductivity;       // TODO: create proper class for productivity
};


#endif  // LIB_OBJECTS_H_FACTORY_H