#include <sstream>
#include "OthelloView.h"
#include "OthelloBoard.h"
#include "BoardDirection.h"


using namespace std;

void OthelloView::PrintBoard(std::ostream &s) const {
    cout << "- 0 1 2 3 4 5 6 7" << endl;
    // Loop thru board and place blank spots and player pieces where it's necessary
    for (int r = 0; r < mOthelloBoard->BOARD_SIZE; r++) {
        cout << r << " ";
        for(int c = 0; c <  mOthelloBoard->BOARD_SIZE; c++) {
            if (mOthelloBoard->mBoard[r][c] == OthelloBoard::Player::EMPTY) {
                cout << ". ";
            } else if (mOthelloBoard->mBoard[r][c] == OthelloBoard::Player::BLACK) {
                cout << "B ";
            } else if (mOthelloBoard->mBoard[r][c] == OthelloBoard::Player::WHITE) {
                cout << "W ";
            }
        }
        cout << endl;
    }
}

ostream& operator<<(std::ostream& lhs, const OthelloView& rhs) {
    rhs.PrintBoard(lhs);
    lhs << (rhs.mOthelloBoard->GetCurrentPlayer() == OthelloBoard::Player::WHITE ? "White's turn" : "Black's turn");
    return lhs;
}

unique_ptr<OthelloMove> OthelloView::ParseMove(const std::string& strFormat) {
    istringstream parser{ strFormat };
    char dummy;
    int row, col;
    parser >> dummy >> row >> dummy >> col >> dummy;
    unique_ptr<OthelloMove> move = make_unique<OthelloMove>(BoardPosition(row, col));
    return move;
}

ostream& operator<<(std::ostream &lhs, const OthelloMove &rhs) {
    return lhs << string(rhs);
}
