cmake_minimum_required(VERSION 3.0)

project(simunomics)

set(EXE_PATH app)
set(PLAYER_LIB_PATH lib/player)
set(GENERATOR_LIB_PATH lib/generator)
set(REGISTRY_LIB_PATH lib/registry)
set(OBJECT_LIB_PATH lib/objects)
set(MISC_LIB_PATH lib/misc)

add_subdirectory(${PROJECT_SOURCE_DIR}/${EXE_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${PLAYER_LIB_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${GENERATOR_LIB_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${REGISTRY_LIB_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${OBJECT_LIB_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${MISC_LIB_PATH})
