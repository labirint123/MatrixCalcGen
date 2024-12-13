cmake_minimum_required(VERSION 3.16)

project(MatrixCalcGen)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SOURCE_FILES
    src/main.cpp
    src/MainWindow.cpp
    src/Matrix.cpp
    src/Controller.cpp
    src/Generator.cpp
    src/SettingsDialog.h
)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})
else()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Widgets
)