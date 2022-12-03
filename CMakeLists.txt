cmake_minimum_required(VERSION 3.23)
project(Project_4)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Project_4 Button.cpp Button.h Minesweeper.cpp Minesweeper.h Tile.cpp Tile.h Toolbox.cpp Toolbox.h GameState.cpp GameState.h)
target_link_libraries(Project_4 sfml-graphics sfml-audio)