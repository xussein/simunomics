#include "functions.h"

void init() {
    // TODO: create Map (or World) class and apply Generator to it
    ObjectFactory::getInstance().registerObjectClass(ObjectClass::Factory, []() -> std::unique_ptr<Object> { return std::make_unique<Factory>(); });    // TODO: should move class registration away from main space back to Factory classes 
    ObjectFactory::getInstance().createObject(ObjectClass::Factory);        // TODO: create Generator class, for creating objects in game
    ObjectFactory::getInstance().createObject(ObjectClass::Factory);
    ObjectFactory::getInstance().createObject(ObjectClass::Factory);

    StateFactory::getInstance().registerStateClass(StateClass::Idle, []() -> std::unique_ptr<State> { return std::make_unique<Idle>(); });
    StateFactory::getInstance().registerStateClass(StateClass::Operating, []() -> std::unique_ptr<State> { return std::make_unique<Operating>(); });
}

void update() {    
    std::cout << "state: ";     // DEBUG
    int state;
    std::cin >> state;
    std::cout << "objectId: ";  // DEBUG
    int objectId;
    std::cin >> objectId;
    ObjectFactory::getInstance().updateObject(objectId, StateFactory::getInstance().createState(static_cast<StateClass>(state)));       // TODO: пиздец.
}

void play() {
    // TODO: keep working on SFML 
    auto window = sf::RenderWindow(sf::VideoMode({800, 600}), "Simunomics");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        for (auto event = sf::Event(); window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }

    std::cout << "Starting simunomics!" << std::endl;

    init();

    const static double frameRate = 60.0;                                       // TODO: consider making it possible for user to set framerate
    const static std::chrono::duration<double> frameDuration(1.0 / frameRate);  // our 60 fps in game

    while (true) {
        auto startTime = std::chrono::high_resolution_clock::now();

        update();

        auto endTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = endTime - startTime;

        if (elapsedTime < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsedTime);
        }
    }
}