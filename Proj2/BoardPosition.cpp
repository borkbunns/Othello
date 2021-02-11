#include "BoardPosition.h"
#include "BoardDirection.h"
#include <sstream>
BoardPosition::BoardPosition() : mRow(0), mColumn(0) {
}

BoardPosition::BoardPosition(char row, char column) : mRow(row), mColumn(column) {
}

BoardPosition::operator std::string() const {
    std::ostringstream os;
    os << "(" << int(mRow) << ", " << int(mColumn) << ")";
    return os.str();
}

std::istream &operator>>(std::istream &lhs, BoardPosition &rhs) {
    int row, col;
    char dummy;
    lhs >> dummy >> row >> dummy >> col >> dummy;
    rhs = BoardPosition(row, col);
    return lhs;
}

std::ostream& operator<<(std::ostream &lhs, BoardPosition rhs) {
    lhs << std::string(rhs);
    return lhs;
}

bool BoardPosition::operator==(BoardPosition rhs) {
    return (mRow == rhs.mRow) && (mColumn == rhs.mColumn);
}

bool BoardPosition::operator<(BoardPosition rhs) {
    if (mRow == rhs.mRow) {
        return mColumn < rhs.mColumn;
    }
    return mRow < rhs.mRow;
}

bool BoardPosition::InBounds(int boardSize) {
    return (mRow >= 0 && mRow < boardSize) && (mColumn >= 0 && mColumn < boardSize);
}

bool BoardPosition::InBounds(int rows, int columns) {
    return (mRow >= 0 && mRow <= rows) && (mColumn >= 0 && mColumn <= columns);
}

std::vector<BoardPosition> BoardPosition::GetRectangularPositions(int rows, int columns) {
    std::vector<BoardPosition> board;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
           BoardPosition coord = BoardPosition{static_cast<char>(r), static_cast<char>(c)};
           board.push_back(coord);
        }
    }
    return board;
}

BoardPosition BoardPosition::operator+(BoardDirection dir) {
    return {static_cast<char>(mRow + dir.GetRowDir()), static_cast<char>(mColumn + dir.GetColDir()) };
}

int BoardPosition::Test() {
    return 0;
}

