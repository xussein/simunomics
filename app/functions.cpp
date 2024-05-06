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

bool isMouseClickedInsideTile(const sf::Vector2f & mousePos, const sf::VertexArray & tile) {
    bool isInside = false;

    for (size_t i = 0; i < tile.getVertexCount(); i++)
    {
        size_t nextIndex = (i + 1) % tile.getVertexCount();
        // TODO: need to understand the algorithm
        if (((tile[i].position.y > mousePos.y) != (tile[nextIndex].position.y > mousePos.y)) &&
            (mousePos.x < (tile[nextIndex].position.x - tile[i].position.x) * (mousePos.y - tile[i].position.y) / (tile[nextIndex].position.y - tile[i].position.y) + tile[i].position.x))
            isInside = !isInside;
    }

    return isInside;
}

void play() {
    std::mutex mtx;
    ConsoleDebugOutput consoleDebugOutput;     // DEBUG

    // SFMLTEST: clock test
    sf::Clock clock;    // DEBUG

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800, 600}), "Simunomics");
    window.setFramerateLimit(60);

    // SFMLTEST: view test
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(800.f, 600.f));
    window.setView(view);

    // SFMLTEST: context output
    sf::ContextSettings contextSettings = window.getSettings();
    std::cout << "depth bits:" << contextSettings.depthBits << std::endl;
    std::cout << "stencil bits:" << contextSettings.stencilBits << std::endl;
    std::cout << "antialiasing level:" << contextSettings.antialiasingLevel << std::endl;
    std::cout << "version:" << contextSettings.majorVersion << "." << contextSettings.minorVersion << std::endl;

    // SFMLTEST: texture test
    sf::Texture texture;
    if (!texture.loadFromFile("res/sprites/dickbutt.JPG")) {
        std::cerr << "[ERR] Texture loading failed!" << std::endl;
    }

    // SFMLTEST: sprite test
    sf::Sprite sprite = sf::Sprite(texture);

    // SFMLTEST: font and text test
    sf::Font font;
    if (!font.loadFromFile("res/fonts/cour.ttf")) {
        std::cerr << "[ERR] Font loading failed!" << std::endl;
    }
    sf::Text text(font);
    text.setString("Dickbutt!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // SFMLTEST: simple rectangle test
    sf::RectangleShape rectangle(sf::Vector2f(120.f, 120.f));
    rectangle.setPosition(sf::Vector2f(400, 300));
    rectangle.setFillColor(sf::Color::Green);

    // SFMLTEST: simple vertex array test
    sf::VertexArray vertexArray(sf::PrimitiveType::TriangleStrip, 4);
    vertexArray[0].position = sf::Vector2f(300, 300);
    vertexArray[1].position = sf::Vector2f(300, 400);
    vertexArray[2].position = sf::Vector2f(400, 400);
    vertexArray[3].position = sf::Vector2f(400, 250);
    vertexArray[0].color = sf::Color::Red;
    vertexArray[1].color = sf::Color::Green;
    vertexArray[2].color = sf::Color::Red;
    vertexArray[3].color = sf::Color::Blue;

    // SFMLTEST: custom entity test
//    const int level[] = {
//        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
//        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
//        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
//        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
//        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
//        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
//        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//    };
    const int level[] {
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1
    };

    Map map;
    if (!map.load("res/sprites/green-tile.png", sf::Vector2i(192, 96), level, 1, 1)) {
        std::cerr << "[ERR] Failed loading tileset!" << std::endl;
    }

    // SFMLTEST: creating isometric tile entity (triangles)
//    sf::VertexArray isoTileMap(sf::PrimitiveType::Triangles, 6);
//    isoTileMap[0].position = sf::Vector2f(100, 100);
//    isoTileMap[1].position = sf::Vector2f(100 - tileWidth / 2, 100 + tileHeight / 2);
//    isoTileMap[2].position = sf::Vector2f(100, 100 + tileHeight);
//    isoTileMap[3].position = sf::Vector2f(100, 100);
//    isoTileMap[4].position = sf::Vector2f(100 + tileWidth / 2, 100 + tileHeight / 2);
//    isoTileMap[5].position = sf::Vector2f(100, 100 + tileHeight);
//    isoTileMap[0].texCoords = sf::Vector2f(tileWidth / 2, 0);
//    isoTileMap[1].texCoords = sf::Vector2f(0, tileHeight / 2);
//    isoTileMap[2].texCoords = sf::Vector2f(tileWidth / 2, tileHeight);
//    isoTileMap[3].texCoords = sf::Vector2f(tileWidth / 2, 0);
//    isoTileMap[4].texCoords = sf::Vector2f(tileWidth, tileHeight / 2);
//    isoTileMap[5].texCoords = sf::Vector2f(tileWidth / 2, tileHeight);
//
//    sf::Texture tileTexture;
//    if (!tileTexture.loadFromFile("res/sprites/green-tile.png")) {
//        std::cerr << "[ERR] Couldn't load tile file." << std::endl;
//    }

//    std::thread simunomicsThread(simunomics, std::ref(mtx), std::ref(consoleDebugOutput));
    // main loop
    while (window.isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);     // constantly updating mouse position
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
                    break;
                case sf::Event::KeyReleased:
                    break;
                case sf::Event::MouseWheelScrolled:
                    break;
                case sf::Event::MouseButtonPressed:
                    map.isMapClicked(mousePos);
//                    if () {
//                        std::cout << "Mouse clicked inside map." << std::endl;
//                    }
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

//        window.draw(sprite);
//        window.draw(text);
//        window.draw(rectangle);
//        window.draw(rectangle, transform);
//        window.draw(vertexArray);
        map.draw(window);
//        window.draw(map);
//        window.draw(isoTileMap, & tileTexture);

        window.display();
    }

    sf::Time time = clock.getElapsedTime();
    std::cout << "Time elapsed for window opened: " << time.asSeconds() << std::endl;

//    simunomicsThread.join();
}