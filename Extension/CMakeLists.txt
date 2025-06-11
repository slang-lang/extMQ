INCLUDE(${PROJECT_SOURCE_DIR}/CMake/Base.cmake)

SET(SOURCES
    Extension.cpp
    Types.cpp
)

SET(HEADERS
    Defines.h
    Extension.h
    MQClose.h
    MQOpen.h
    MQReceive.h
    MQSend.h
    Types.h
)

SET(DEPENDENCIES
    Core
)

SET(MODULES
    slang
)

add_include(Externals)

build_shared_lib(SlangMQ "${MODULES}")
