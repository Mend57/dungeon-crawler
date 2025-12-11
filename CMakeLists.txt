cmake_minimum_required(VERSION 3.30)
project(DungeonCrawler)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

file(GLOB SOURCES "*.cpp" "UI/*.cpp" "Tiles/*.cpp")

add_executable(DungeonCrawler ${SOURCES})

target_link_libraries(DungeonCrawler Qt6::Core Qt6::Gui Qt6::Widgets)