# Chess_game
Here you have a chess game made entirely with Qt

Below is the CMakeList.txt file for compiling this project corectly.

cmake_minimum_required(VERSION 3.26)
project(CHESS_2_0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/path/to/Qt6.6.0/6.6.0/gcc_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(CHESS_2_0 main.cpp
        Piece.cpp
        Piece.h
        Box.cpp
        Box.h
        Board.cpp
        Board.h
        Queen.cpp
        Queen.h
        Rook.cpp
        Rook.h
        Bishop.cpp
        Bishop.h
        Horse.cpp
        Horse.h
        King.cpp
        King.h
        Pawn.cpp
        Pawn.h
        Game.cpp
        Game.h
        GUI.h
        GUI.cpp
        BoardSide.cpp
        BoardSide.h
        PieceDto.cpp
        PieceDto.h
)
target_link_libraries(CHESS_2_0
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
