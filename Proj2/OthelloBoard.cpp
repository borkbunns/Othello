#include "OthelloBoard.h"
#include "OthelloMove.h"
#include "BoardDirection.h"
#include "BoardPosition.h"

using namespace std;


OthelloBoard::OthelloBoard(): mCurrentValue(0), mCurrentPlayer(Player::BLACK) {
    mBoard = {Player::EMPTY}, mBoard[3][3] = {Player::WHITE}, mBoard[3][4] = {Player::BLACK},
    mBoard[4][3] = {Player::BLACK}, mBoard[4][4] = {Player::WHITE};
}


void OthelloBoard::ApplyMove(std::unique_ptr<OthelloMove> m) {
    if (!m->IsPass()) {
        mBoard[m->mPosition.GetRow()][m->mPosition.GetColumn()] = mCurrentPlayer;
        mCurrentValue += (GetCurrentPlayer() == Player::BLACK) ? 1 : -1;
        BoardPosition ogPosition = BoardPosition{m->mPosition.GetRow(), m->mPosition.GetColumn()};
        for (BoardDirection direction : BoardDirection::CARDINAL_DIRECTIONS) {
            BoardPosition currentPosition = ogPosition;
            int counter = 0;
            int row = direction.GetRowDir();
            int col = direction.GetColDir();
            while (InBounds(currentPosition + direction) &&
                   PositionIsEnemy(currentPosition + direction, mCurrentPlayer)) {
                counter++;
                currentPosition = currentPosition + direction;
            }
            if (counter == 0 || !InBounds(currentPosition + direction) ||
            mBoard[currentPosition.GetRow() + row][currentPosition.GetColumn() + col] == Player::EMPTY) {
                continue;
            }
            currentPosition = ogPosition;
            m->AddFlipSet(OthelloMove::FlipSet{(char) counter, direction});
            for (int i = counter; i > 0; i--) {
                currentPosition = currentPosition + direction;
                mBoard[currentPosition.GetRow()][currentPosition.GetColumn()] = mCurrentPlayer;
                mCurrentValue += (GetCurrentPlayer() == Player::BLACK) ? 2 : -2;
            }
        }
    }
    mHistory.push_back(move(m));
    mCurrentPlayer = (GetCurrentPlayer() == Player::BLACK) ? Player::WHITE : Player::BLACK;
}


vector<unique_ptr<OthelloMove>> OthelloBoard::GetPossibleMoves() const {
    vector<unique_ptr<OthelloMove>> possibleMoves;
    for (int i = 0; i < mBoard.size(); i++) {
        for (int j = 0; j < mBoard[0].size(); j++) {
            BoardPosition ogPosition = BoardPosition{static_cast<char>(i), static_cast<char>(j)};
            for (BoardDirection dir : BoardDirection::CARDINAL_DIRECTIONS) {
                BoardPosition currPos = ogPosition;
                int count = 0, row = dir.GetRowDir(), col = dir.GetColDir();
                while (InBounds(currPos + dir) && PositionIsEnemy(currPos + dir, mCurrentPlayer)) {
                    count++;
                    currPos = currPos + dir;
                }
                if (!InBounds(currPos + dir) || mBoard[currPos.GetRow() + row][currPos.GetColumn() + col] == Player::EMPTY
                    || mBoard[ogPosition.GetRow()][ogPosition.GetColumn()] != Player::EMPTY || count == 0 ) {
                    continue;
                }
                possibleMoves.push_back(make_unique<OthelloMove> (OthelloMove(ogPosition)));
                break;
            }
        }
    }
    if (possibleMoves.empty()) {
        possibleMoves.push_back(make_unique<OthelloMove>(BoardPosition(-1, -1)));
    }
    return possibleMoves;
}

void OthelloBoard::UndoLastMove() {
    unique_ptr<OthelloMove> recentMove = move(mHistory.back());
    auto flipSet = recentMove->mFlips;
    mBoard[recentMove->mPosition.GetRow()][recentMove->mPosition.GetColumn()] = Player::EMPTY;
    mCurrentValue += (GetCurrentPlayer() == Player::BLACK) ? 1 : -1;
    for (auto currentFlip : flipSet) {
        BoardPosition current = BoardPosition{recentMove->mPosition.GetRow(), recentMove->mPosition.GetColumn()};
        for (int i = 0 ; i < int(currentFlip.mFlipCount); i++) {
            current = current + currentFlip.mDirection;
            mBoard[current.GetRow()][current.GetColumn()] = mCurrentPlayer;
            mCurrentValue += (GetCurrentPlayer() == Player::BLACK) ? 2 : -2;
        }
    }
    mCurrentPlayer = (GetCurrentPlayer() == Player::BLACK) ? Player::WHITE : Player::BLACK;
    mHistory.pop_back();
}

bool OthelloBoard::IsFinished() {
    auto & twoMoves = GetMoveHistory();
    if (!twoMoves.empty()) {
        for (int i = 0; i < twoMoves.size() - 1; i++) {
            if (twoMoves[i]->IsPass() && twoMoves[i + 1]->IsPass()) {
                return true;
            }
        }
    }
    return false;
}