#ifndef APP_FUNCTIONS_H
#define APP_FUNCTIONS_H


#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>

#include <SFML/Graphics.hpp>

#include "../lib/objects/h/ObjectFactory.h"
#include "../lib/objects/h/Factory.h"
#include "../lib/objects/h/StateFactory.h"
#include "../lib/objects/h/states/Idle.h"
#include "../lib/objects/h/states/Operating.h"
#include "../lib/misc/h/ConsoleDebugOutput.h"
#include "../lib/Map.h"

void play();

static size_t tileWidth = 192;
static size_t tileHeight = 96;

#endif  // APP_FUNCTIONS_H