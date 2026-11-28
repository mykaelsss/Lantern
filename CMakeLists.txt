cmake_minimum_required(VERSION 3.21)   # oldest CMake version this file supports
project(Lantern LANGUAGES CXX) # project name. CXX means C++

set(CMAKE_CXX_STANDARD 20)             # use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)    # fail instead of silently using an older version
set(CMAKE_AUTOMOC ON)                  # run Qt's moc automatically (needed for signals and slots)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # write build/compile_commands.json so clangd can find Qt headers

find_package(Qt6 REQUIRED COMPONENTS Widgets)   # find the Qt that Homebrew installed

# The engine: plain C++, no Qt. Built as a library so the other two targets can use it
add_library(engine
    engine/engine.cpp                  # add each new engine .cpp file to this list
)
target_include_directories(engine PUBLIC engine)   # lets other targets #include engine headers

# Command-line program for testing the engine without the UI
add_executable(engine_cli cli/main.cpp)
target_link_libraries(engine_cli PRIVATE engine)

# The Qt app
add_executable(app app/main.cpp)
target_link_libraries(app PRIVATE engine Qt6::Widgets)
