cmake_minimum_required(VERSION 3.8.2)

project(asyncgl)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Gui)
find_package(OpenGL REQUIRED)

add_executable(asyncgl
    main.cpp
    thread.cpp
    window.cpp
)

target_link_libraries(asyncgl Qt5::Gui OpenGL)
