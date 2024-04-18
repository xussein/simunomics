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

void sfmlTest() {

}

void sfmlPoll(sf::RenderWindow & window, std::mutex & mtx, bool & condition) {
    while (window.isOpen()) {
        std::unique_lock<std::mutex> lock(mtx);
        condition = window.hasFocus();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void simunomics(std::mutex & mtx, bool & condition) {
    std::cout << "Starting simunomics!" << std::endl;

    init();

    const static double frameRate = 60.0;                                       // TODO: consider making it possible for user to set framerate
    const static std::chrono::duration<double> frameDuration(1.0 / frameRate);  // our 60 fps in game

    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        std::cout << "Window focus status: " << (condition ? "Focused" : "Not Focused") << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
//        update();
    }
}

void play() {
    std::mutex mtx;
    bool condition;     // DEBUG

    // TODO: keep working on SFML
    sf::Clock clock;    // DEBUG

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "Simunomics");
    window.setFramerateLimit(60);

    std::thread sfmlPollThread(sfmlPoll, std::ref(window), std::ref(mtx), std::ref(condition));
    std::thread simunomicsThread(simunomics, std::ref(mtx), std::ref(condition));

    while (window.isOpen()) {
        for (sf::Event event = sf::Event(); window.pollEvent(event);) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::LostFocus:
                    break;
                case sf::Event::Resized:
                    break;
                case sf::Event::GainedFocus:
                    break;
                case sf::Event::TextEntered:
                    break;
                case sf::Event::KeyPressed:
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseWheelScrolled:
                    break;
                case sf::Event::MouseButtonPressed:
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseMoved:
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
        window.display();
    }

    sf::Time time = clock.getElapsedTime();
    std::cout << "Time elapsed for window opened: " << time.asSeconds() << std::endl;

    sfmlPollThread.join();
    simunomicsThread.join();
}