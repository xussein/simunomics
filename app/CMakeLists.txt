find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Audio Network Window System)

add_executable(executable main.cpp functions.cpp ../lib/Map.cpp ../lib/Tile.cpp)

target_link_libraries(executable
    generator_lib
    player_lib
    registry_lib
    object_lib
    misc_lib
    SFML::Graphics
    SFML::Audio
    SFML::Network
    SFML::Window
    SFML::System
)