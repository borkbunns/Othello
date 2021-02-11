#pragma once
#include <iostream>
#include <array>

class BoardDirection {
private:
    char mRowDir;
    char mColDir;

public:
    BoardDirection();
    BoardDirection(char rowDir, char colDir);

    inline char GetRowDir() const { return  mRowDir; }
    inline char GetColDir() const { return  mColDir; }

    static std::array<BoardDirection, 8> CARDINAL_DIRECTIONS;

};
