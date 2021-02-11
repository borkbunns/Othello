#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "BoardDirection.h"
class BoardPosition {
private:
    char mRow;
    char mColumn;
public:
    // Default constructor
    BoardPosition();
    // Constructor - Initialize instances to parameter values
    BoardPosition(char row, char column);

    // inline getters for row & column
    inline char GetRow() const { return mRow; }
    inline char GetColumn() const { return mColumn; }

    // operator functions
    operator std::string() const;
    friend std::istream& operator>>(std::istream &lhs, BoardPosition& rhs);
    bool operator==(BoardPosition rhs);
    bool operator<(BoardPosition rhs);
    BoardPosition operator+(BoardDirection dir);

    // Member methods
    static int Test();
    bool InBounds(int boardSize);
    bool InBounds(int rows, int columns);
    static std::vector<BoardPosition> GetRectangularPositions(int rows, int columns);
};

std::ostream& operator<<(std::ostream &lhs, BoardPosition rhs);



