set(
    GENERATOR_LIB_FILES
    Generator.cpp
        ../misc/ConsoleDebugOutput.cpp ../misc/h/ConsoleDebugOutput.h)

add_library(generator_lib ${GENERATOR_LIB_FILES})