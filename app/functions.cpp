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

void simunomics(std::mutex & mtx, ConsoleDebugOutput & consoleDebugOutput) {
    std::cout << "Starting simunomics!" << std::endl;

    init();

    const static double frameRate = 60.0;                                       // TODO: consider making it possible for user to set framerate
    const static std::chrono::duration<double> frameDuration(1.0 / frameRate);  // our 60 fps in game

    while (true) {
        std::cout << "Window focus status: " << (consoleDebugOutput.isWindowInFocus ? "Focused" : "Not Focused") << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
//        update();
    }
}

void play() {
    std::mutex mtx;
    ConsoleDebugOutput consoleDebugOutput;     // DEBUG

    // SFMLTEST: clock test
    sf::Clock clock;    // DEBUG

    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 16;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "Simunomics", sf::Style::Default, contextSettings);
    window.setFramerateLimit(60);

    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(800.f, 600.f));
    window.setView(view);

    const int level[] = {
        0, 1, 2, 3, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };
    Map map;
    if (!map.load("res/sprites/tileset.png", sf::Vector2i(192, 96), level, 3, 2)) {
        std::cerr << "[ERR] Failed loading tileset!" << std::endl;
    }

//    std::thread simunomicsThread(simunomics, std::ref(mtx), std::ref(consoleDebugOutput));

    // main loop
    while (window.isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);     // constantly updating mouse position
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        for (sf::Event event = sf::Event(); window.pollEvent(event);) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::LostFocus:
                    consoleDebugOutput.isWindowInFocus = false;
                    break;
                case sf::Event::Resized:
                    break;
                case sf::Event::GainedFocus:
                    consoleDebugOutput.isWindowInFocus = true;
                    break;
                case sf::Event::TextEntered:
                    break;
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        Map::move(view, sf::Vector2f(.0f, -10.0f));
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        Map::move(view, sf::Vector2f(.0f, 10.0f));
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                        Map::move(view, sf::Vector2f(-10.0f, .0f));
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        Map::move(view, sf::Vector2f(10.0f, .0f));
                    }
                    window.setView(view);
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseWheelScrolled:
                    if (event.mouseWheelScroll.delta > 0) {
                        view.zoom(0.9f);
                    } else if (event.mouseWheelScroll.delta < 0) {
                        view.zoom(1.1f);
                    }
                    window.setView(view);
                    break;
                case sf::Event::MouseButtonPressed:
//                    map.isMapClicked(worldPos);
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseMoved:
//                    map.isMapHovered(worldPos);
                    map.getNearestVertex(worldPos);
                    break;
                case sf::Event::MouseEntered:
                    break;
                case sf::Event::MouseLeft:
                    break;
                case sf::Event::JoystickButtonPressed:
                    break;
                case sf::Event::JoystickButtonReleased:
                    break;
                case sf::Event::JoystickMoved:
                    break;
                case sf::Event::JoystickConnected:
                    break;
                case sf::Event::JoystickDisconnected:
                    break;
                case sf::Event::TouchBegan:
                    break;
                case sf::Event::TouchMoved:
                    break;
                case sf::Event::TouchEnded:
                    break;
                case sf::Event::SensorChanged:
                    break;
                case sf::Event::Count:
                    break;
            }
        }
        window.clear();

//        map.draw(window);
        window.draw(map);

        window.display();
    }

    sf::Time time = clock.getElapsedTime();
    std::cout << "Time elapsed for window opened: " << time.asSeconds() << std::endl;

//    simunomicsThread.join();
}