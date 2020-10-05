cmake_minimum_required(VERSION 3.18.2)

set(CMAKE_CXX_STANDARD 17)
set(NAME app)
set(SOURCE_FILES
    mainwindow.ui
    mainwindow.cpp
    dialog.ui
    dialog.cpp
    file.cpp
    general.cpp
)

project(${NAME})

add_compile_options(
    -Wall
    -Wextra
    -Werror
    -Wpedantic
)

add_library(${NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${NAME} tag Qt5::Widgets)
