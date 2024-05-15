set(
    GRAPHICS_LIB_FILES
    Map.cpp
    Tile.cpp
#    ElevationPointer.cpp
        ElevationPointer.cpp ElevationPointer.h)

add_library(graphics_lib ${GRAPHICS_LIB_FILES})

if (DEBUG)
    message("SFML LIBRARIES: ${SFML_LIBRARIES}")
endif()

# TODO: learn about PUBLIC/PRIVATE
if (REQUIRED_SFML_VERSION EQUAL 2.6.1)
    target_link_libraries(
            graphics_lib
            PUBLIC
            sfml-graphics
            sfml-window
    )
elseif(REQUIRED_SFML_VERSION EQUAL 3.0)
    target_link_libraries(
            graphics_lib
            PUBLIC
            SFML::Graphics
            SFML::Window
    )
endif()