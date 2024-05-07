if (DEBUG)
    message("SFML LIBRARIES: ${SFML_LIBRARIES}")
endif()

add_executable(executable main.cpp functions.cpp ../lib/Map.cpp ../lib/Tile.cpp)

target_link_libraries(
    executable
    PRIVATE
    generator_lib
    player_lib
    registry_lib
    object_lib
    misc_lib
)
# TODO: learn about PUBLIC/PRIVATE
if (REQUIRED_SFML_VERSION EQUAL 2.6.1)
    target_link_libraries(
        executable
        PUBLIC
        sfml-graphics
        sfml-window
    )
elseif(REQUIRED_SFML_VERSION EQUAL 3.0)
    target_link_libraries(
        executable
        PUBLIC
        SFML::Graphics
        SFML::Window
    )
endif()

