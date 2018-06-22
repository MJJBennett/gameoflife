# Declare the minimum required cmake version; somewhat arbitrary unless you're using version-specific features.
# We use 3.1 for CMAKE_CXX_STANDARD
cmake_minimum_required(VERSION 3.1)

# Create a project. Find and replace ConwayLife to give the project your own title.
project(ConwayLife)

# Set the version of C++ being used. Here, C++17.
if(UNIX AND NOT APPLE)
SET(CMAKE_CXX_COMPILER /usr/bin/g++-7)
endif()
set(CMAKE_CXX_STANDARD 17)

# CMAKE_SOURCE_DIR refers to the directory with the top-level CMakeLists.txt
# Here, we're including include/ and lib/SFML-2.4.2/include
include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2/include")
link_directories("/usr/lib/x86_64-linux-gnu/")

# Sets the directory where the linker will search for libraries. Necessary to find the .a (or .dylib, etc) files for SFML.
link_directories("${CMAKE_SOURCE_DIR}/lib/SFML-2.4.2/lib")

# Create the executable. Make sure to list every source file (I generally add the headers as well)
add_executable(ConwayLife
    src/funcs.cpp include/funcs.h
    src/debug.cpp include/debug.h
    src/Resource.cpp include/Resource.h
    src/game.cpp include/game.h
    src/main.cpp
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
if (UNIX AND NOT APPLE)
  message("Linking on Linux.")
  target_link_libraries(ConwayLife sfml-graphics sfml-window sfml-system)
endif ()
