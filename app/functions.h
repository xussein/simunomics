#ifndef APP_FUNCTIONS_H
#define APP_FUNCTIONS_H


#include <iostream>
#include <memory>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include "../lib/objects/h/ObjectFactory.h"
#include "../lib/objects/h/Factory.h"
#include "../lib/objects/h/StateFactory.h"
#include "../lib/objects/h/states/Idle.h"
#include "../lib/objects/h/states/Operating.h"

void play();


#endif  // APP_FUNCTIONS_H