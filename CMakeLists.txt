cmake_minimum_required(VERSION 3.12)
project(OpenNodeTraveler)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${project_SOURCE_DIR}/cmake")
file(GLOB SOURCES "src/*.cpp")
include_directories(include)
#					${SDL2_INCLUDE_DIR})
#find_package(SDL2 REQUIRED)

add_executable(RUN ${SOURCES})

#IF(MINGW)
#	target_link_libraries(RUN ${SDL2_LIBRARY} -lmingw32 -lSDL2main -lSDL2 -mwindows)
#ENDIF(MINGW)

#IF(UNIX)
#	target_link_libraries(RUN ${SDL2_LIBRARY} -lSDL2main -lSDL2)
#ENDIF(UNIX)

set_target_properties(RUN PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)