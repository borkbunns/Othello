cmake_minimum_required(VERSION 3.16)
project(Proj2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Proj2
        BoardDirection.cpp
        BoardDirection.h
        BoardPosition.cpp
        BoardPosition.h
        main.cpp
        OthelloBoard.cpp
        OthelloBoard.h
        OthelloMove.cpp
        OthelloMove.h
        OthelloView.cpp
        OthelloView.h)
