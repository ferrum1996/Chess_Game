cmake_minimum_required(VERSION 3.9)
project(Chess_SFML_C__)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)
add_executable(Chess_SFML_C__ main.cpp Figure.cpp Figure.hpp Connector.hpp ChessBoard.cpp ChessBoard.hpp Game.cpp Game.hpp)

set(SFML_ROOT "D:/Libraries/64SFML")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED graphics network audio window system)

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()