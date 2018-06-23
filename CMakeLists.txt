# Declare the minimum required cmake version; somewhat arbitrary unless you're using version-specific features.
# We use 3.1 for CMAKE_CXX_STANDARD
cmake_minimum_required(VERSION 3.1)

# Create a project. Find and replace ConwayLife to give the project your own title.
project(ConwayLife)

# Add definition for Linux
if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

add_definitions(-g)
set(_NO_LINK FALSE)

# Set the version of C++ being used. Here, C++17.
set(CMAKE_CXX_STANDARD 17)

# CMAKE_SOURCE_DIR refers to the directory with the top-level CMakeLists.txt
# Here, we're including include/ and lib/SFML-2.4.2/include
include_directories("${CMAKE_SOURCE_DIR}/include")
if (NOT LINUX)
# If we're not on linux, we use the headers from the library
include_directories("${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2/include")
# Sets the directory where the linker will search for libraries. Necessary to find the .a (or .dylib, etc) files for SFML.
link_directories("${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2/lib")
else ()
# If we're on linux, we have the headers, but need to specify where the .so files are
link_directories("/usr/lib/x86_64-linux-gnu/")
endif ()

# Create the executable. Make sure to list every source file (I generally add the headers as well)
add_executable(ConwayLife
    ${CMAKE_SOURCE_DIR}/src/funcs.cpp ${CMAKE_SOURCE_DIR}/include/funcs.h
    ${CMAKE_SOURCE_DIR}/src/debug.cpp ${CMAKE_SOURCE_DIR}/include/debug.h
    ${CMAKE_SOURCE_DIR}/src/Resource.cpp ${CMAKE_SOURCE_DIR}/include/Resource.h
    ${CMAKE_SOURCE_DIR}/src/game.cpp ${CMAKE_SOURCE_DIR}/include/game.h
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

# This links the executable on Windows and Mac - it shouldn't be too difficult to add Linux as well.
# If you've branched out into different parts of SFML, you might need different libraries; they can be added here.
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
