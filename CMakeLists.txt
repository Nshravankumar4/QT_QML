cmake_minimum_required(VERSION 3.19)

project(QtInterviewPrep VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 5.15 REQUIRED COMPONENTS
    Quick
    QuickControls2
)

add_executable(QtInterviewPrep
    src/main.cpp
    src/backend.h
    src/backend.cpp
    src/signal_slot_demo.h
    src/signal_slot_demo.cpp
    qml/qml.qrc
)

target_link_libraries(QtInterviewPrep
    PRIVATE
        Qt5::Quick
        Qt5::QuickControls2
)

install(TARGETS QtInterviewPrep
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin
)
