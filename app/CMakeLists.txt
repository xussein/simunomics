add_executable(executable main.cpp functions.cpp ../lib/Constants.h)

target_link_libraries(
    executable
    PRIVATE
    generator_lib
    player_lib
    registry_lib
    object_lib
    misc_lib
    graphics_lib
)

