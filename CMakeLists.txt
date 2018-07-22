cmake_minimum_required(VERSION 3.1)
project(ConwayLife)

set(CMAKE_CXX_STANDARD 17)

# Add definition for Linux
if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

add_definitions(-g) # TODO - Figure out what this does


# CMAKE_SOURCE_DIR refers to the directory with the top-level CMakeLists.txt
include_directories("${CMAKE_SOURCE_DIR}/include/")
if (NOT LINUX)
    include_directories("${CMAKE_SOURCE_DIR}/lib/SFML*/include")
    include_directories("${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2/include")
endif ()

# Create the executable. Make sure to list every source file (I generally add the headers as well)
add_executable(ConwayLife
    ${CMAKE_SOURCE_DIR}/src/funcs.cpp ${CMAKE_SOURCE_DIR}/include/funcs.h
    ${CMAKE_SOURCE_DIR}/src/debug.cpp ${CMAKE_SOURCE_DIR}/include/debug.h
    ${CMAKE_SOURCE_DIR}/src/Resource.cpp ${CMAKE_SOURCE_DIR}/include/Resource.h
    ${CMAKE_SOURCE_DIR}/src/World.cpp ${CMAKE_SOURCE_DIR}/include/World.h
    ${CMAKE_SOURCE_DIR}/src/game.cpp ${CMAKE_SOURCE_DIR}/include/game.h
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

if (NOT LINUX)
    link_directories("${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2/lib")
else ()
    link_directories("/usr/lib/x86_64-linux-gnu/")
endif ()

if (APPLE)
    message("Linking on macOS.")
    target_link_libraries(ConwayLife libsfml-graphics.2.4.dylib libsfml-window.2.4.dylib libsfml-system.2.4.dylib)
endif (APPLE)
if (WIN32)
    message("Linking on Windows.")
    target_link_libraries(ConwayLife libsfml-graphics-d.a libsfml-window-d.a libsfml-system-d.a)
endif (WIN32)
if (LINUX)
    message("Linking on Linux.")
    target_link_libraries(ConwayLife sfml-graphics sfml-window sfml-system)
endif ()
