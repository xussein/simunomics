#include "functions.h"
#include "Map.h"

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

    // TODO: keep working on SFML
    sf::Clock clock;    // DEBUG

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "Simunomics");
    window.setFramerateLimit(60);

    sf::View view(sf::Vector2f(400, 300), sf::Vector2f(800.f, 600.f));
    view.setRotation(sf::Angle(sf::degrees(45)));
    view.setSize(sf::Vector2f(400.f, 600.f));
    window.setView(view);

    sf::ContextSettings contextSettings = window.getSettings();
    std::cout << "depth bits:" << contextSettings.depthBits << std::endl;
    std::cout << "stencil bits:" << contextSettings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << contextSettings.antialiasingLevel << std::endl;
    std::cout << "version:" << contextSettings.majorVersion << "." << contextSettings.minorVersion << std::endl;

    sf::Texture texture;
    if (!texture.loadFromFile("res/sprites/dickbutt.JPG")) {
        std::cerr << "[ERR] Texture loading failed!" << std::endl;
    }

    sf::Sprite sprite = sf::Sprite(texture);

    sf::Font font;
    if (!font.loadFromFile("res/fonts/cour.ttf")) {
        std::cerr << "[ERR] Font loading failed!" << std::endl;
    }
    sf::Text text(font);
    text.setString("Dickbutt!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    sf::RectangleShape rectangle(sf::Vector2f(120.f, 120.f));
    rectangle.setPosition(sf::Vector2f(400, 300));
    rectangle.setFillColor(sf::Color::Green);

    sf::VertexArray vertexArray(sf::PrimitiveType::TriangleStrip, 4);
    vertexArray[0].position = sf::Vector2f(300, 300);
    vertexArray[1].position = sf::Vector2f(300, 400);
    vertexArray[2].position = sf::Vector2f(400, 400);
    vertexArray[3].position = sf::Vector2f(400, 250);
    vertexArray[0].color = sf::Color::Red;
    vertexArray[1].color = sf::Color::Green;
    vertexArray[2].color = sf::Color::Red;
    vertexArray[3].color = sf::Color::Blue;

    const int level[] = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    Map map;
    if (!map.load("res/sprites/tileset.png", sf::Vector2u(32, 32), level, 16, 8)) {
        std::cerr << "[ERR] Failed loading tileset!" << std::endl;
    }

    sf::FloatRect bb = rectangle.getGlobalBounds();

//    std::thread simunomicsThread(simunomics, std::ref(mtx), std::ref(consoleDebugOutput));

    while (window.isOpen()) {

        // Получаем позицию мыши в мировых координатах
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // Получаем локальные границы прямоугольника
        sf::FloatRect localBounds = rectangle.getLocalBounds();

        // Применяем трансформацию к границам прямоугольника
        sf::Transform transform = rectangle.getTransform();
        sf::FloatRect transformedBounds = transform.transformRect(localBounds);

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
                    if (event.key.scancode == sf::Keyboard::Scan::Escape)
                    {
//                        std::cout << "the escape key was pressed" << std::endl;
////                        std::cout << "scancode: " << event.key.scancode << std::endl;
////                        std::cout << "code: " << event.key.code << std::endl;
//                        std::cout << "control: " << event.key.control << std::endl;
//                        std::cout << "alt: " << event.key.alt << std::endl;
//                        std::cout << "shift: " << event.key.shift << std::endl;
//                        std::cout << "system: " << event.key.system << std::endl;
//                        std::cout << "description: " << sf::Keyboard::getDescription(event.key.scancode).toAnsiString() << std::endl;
//                        std::cout << "localize: " << sf::Keyboard::localize(event.key.scancode) << std::endl;
//                        std::cout << "delocalize: " << sf::Keyboard::delocalize(event.key.code) << std::endl;
                    }
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseWheelScrolled:
//                    if (event.mouseWheelScroll.wheel == sf::Mouse::Wheel::Vertical)
//                        std::cout << "wheel type: vertical" << std::endl;
//                    else if (event.mouseWheelScroll.wheel == sf::Mouse::Wheel::Horizontal)
//                        std::cout << "wheel type: horizontal" << std::endl;
//                    else
//                        std::cout << "wheel type: unknown" << std::endl;
//                    std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
//                    std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
//                    std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
                    break;
                case sf::Event::MouseButtonPressed:
//                    if (event.mouseButton.button == sf::Mouse::Button::Left && bb.contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
//                        std::cout << "rect pressed!" << std::endl;
////                        rectangle.rotate(sf::Angle(sf::degrees(10.f)));
//                    }
//                    if (event.mouseButton.button == sf::Mouse::Button::Right)
//                    {
//                        std::cout << "the right button was pressed" << std::endl;
//                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
//                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
//                    }

                    // Проверяем, попадает ли мышь в область трансформированного прямоугольника
                    if (transformedBounds.contains(mousePos))
                    {
                        // Если мышь попадает, выводим сообщение в консоль
                        std::cout << "Mouse clicked inside the transformed rectangle!" << std::endl;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    break;
                case sf::Event::MouseMoved:
//                    std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
//                    std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                    break;
                case sf::Event::MouseEntered:
//                    std::cout << "the mouse cursor has entered the window" << std::endl;
                    break;
                case sf::Event::MouseLeft:
//                    std::cout << "the mouse cursor has left the window" << std::endl;
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

//        window.draw(sprite);
//        window.draw(text);
        window.draw(rectangle);
//        window.draw(rectangle, transform);

        bb = rectangle.getGlobalBounds();
//        window.draw(vertexArray);
//        window.draw(map);

        window.display();
    }

    sf::Time time = clock.getElapsedTime();
    std::cout << "Time elapsed for window opened: " << time.asSeconds() << std::endl;

//    simunomicsThread.join();
}