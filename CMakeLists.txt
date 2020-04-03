cmake_minimum_required(VERSION 3.5)

project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT TARGET uninstall)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

  add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

configure_file(${PROJECT_SOURCE_DIR}/res/DejaVuSansMono.ttf ${PROJECT_BINARY_DIR}/res/DejaVuSansMono.ttf COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/res/back.png ${PROJECT_BINARY_DIR}/res/back.png COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/res/background.png ${PROJECT_BINARY_DIR}/res/background.png COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/res/body.png ${PROJECT_BINARY_DIR}/res/body.png COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/res/eat.png ${PROJECT_BINARY_DIR}/res/eat.png COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/res/head.png ${PROJECT_BINARY_DIR}/res/head.png COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/res/snake.png ${PROJECT_BINARY_DIR}/res/snake.png COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/res/Fluffing.ogg ${PROJECT_BINARY_DIR}/res/Fluffing.ogg COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/res/icon.svg ${PROJECT_BINARY_DIR}/res/icon.svg COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/res/snake.desktop ${PROJECT_BINARY_DIR}/res/snake.desktop COPYONLY)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(snake src/main.cpp src/game.hpp src/game.cpp src/snake.hpp src/snake.cpp)

target_link_libraries(snake sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

install(TARGETS snake DESTINATION /usr/bin)

install(FILES ${PROJECT_SOURCE_DIR}/res/DejaVuSansMono.ttf ${PROJECT_SOURCE_DIR}/res/snake.png ${PROJECT_SOURCE_DIR}/res/back.png ${PROJECT_SOURCE_DIR}/res/head.png ${PROJECT_SOURCE_DIR}/res/eat.png ${PROJECT_SOURCE_DIR}/res/background.png ${PROJECT_SOURCE_DIR}/res/body.png ${PROJECT_SOURCE_DIR}/res/icon.svg ${PROJECT_SOURCE_DIR}/res/Fluffing.ogg DESTINATION /usr/share/snake/res/)

install(FILES ${PROJECT_SOURCE_DIR}/res/snake.desktop DESTINATION ~/.local/share/applications/)
