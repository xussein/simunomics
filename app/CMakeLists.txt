add_executable(executable main.cpp functions.cpp)

target_link_libraries(executable
    generator_lib
    player_lib
    registry_lib
    object_lib
)