cmake_minimum_required(VERSION 3.0)

project(simunomics)

set(EXE_PATH app)
set(PLAYER_LIB_PATH lib/player)
set(GENERATOR_LIB_PATH lib/generator)
set(REGISTRY_LIB_PATH lib/registry)
set(OBJECT_LIB_PATH lib/objects)
set(MISC_LIB_PATH lib/misc)

set(REQUIRED_SFML_VERSION 2.6.1)
set(DEBUG TRUE)

if (REQUIRED_SFML_VERSION EQUAL 2.6.1)
    find_package(SFML 2.6.1 REQUIRED COMPONENTS graphics window)
elseif(REQUIRED_SFML_VERSION EQUAL 3.0)
    find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/${EXE_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${PLAYER_LIB_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${GENERATOR_LIB_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${REGISTRY_LIB_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${OBJECT_LIB_PATH})
add_subdirectory(${PROJECT_SOURCE_DIR}/${MISC_LIB_PATH})

file(COPY res/ DESTINATION app/res/)