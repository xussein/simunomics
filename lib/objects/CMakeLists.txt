set(
    OBJECT_LIB_FILES
    ObjectFactory.cpp
    Factory.cpp
    StateFactory.cpp
    states/Idle.cpp
    states/Operating.cpp
)

add_library(object_lib SHARED ${OBJECT_LIB_FILES})