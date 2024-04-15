#include "h/Factory.h"

void Factory::init() {
    dailyProductProductivity = 100;
    location = 200;
}

int Factory::getProductivity() const {
    return dailyProductProductivity;
}

int Factory::getLocation() const {
    return location;
}

void Factory::setState(std::shared_ptr<State> & state) {
    this->state = state;
}

void Factory::update() {
    if (state) {
        state->handle();
    } else {
        // TODO: throw exception?
    }
}
