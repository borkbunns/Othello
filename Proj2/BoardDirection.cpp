#include "BoardDirection.h"

BoardDirection::BoardDirection() : mRowDir(0), mColDir(0) {
}

BoardDirection::BoardDirection(char rowDir, char colDir) : mRowDir(rowDir), mColDir(colDir) {
}

std::array<BoardDirection, 8> BoardDirection::CARDINAL_DIRECTIONS =
        {BoardDirection(-1, -1), BoardDirection(-1, 0),
         BoardDirection(-1, 1), BoardDirection(0, -1),
         BoardDirection(0, 1), BoardDirection(1, -1),
         BoardDirection(1, 0), BoardDirection(1, 1)};



