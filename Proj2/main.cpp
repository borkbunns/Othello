#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

int main(int argc, char* argv[]) {
	// Initialization
	auto board = std::make_shared<OthelloBoard>(); // the state of the game board
	OthelloView v(board); // a View for outputting the board via operator<<
	string userInput; // a string to hold the user's command choice
    vector<unique_ptr<OthelloMove>> possibleMoves; // the list of possible moves
    unique_ptr<OthelloMove> m; // the position to make a move on

	do {
        cout << v << endl;
        possibleMoves = board->GetPossibleMoves();
        cout << "Possible moves:";
        if (string(*possibleMoves[0]) == "(-1,-1)") {
            cout << "pass" << endl;
        } else {
            for (auto & possibleMove : possibleMoves) {
                cout << *possibleMove << " ";
            }
            cout << endl << endl;
        }
        cout << "Commands: move (x,y) | undo n-times | showHistory | showValue | quit" << endl;
        cout << "Enter a command: ";
        getline(cin, userInput);
        cout << "you chose " << userInput << endl;

        istringstream parser{ userInput };
        string command, num;
        parser >> command >> num;

        if (command == "move") {
            if (num == "pass") {
                m = v.ParseMove("(-1, -1)");
                board->ApplyMove(std::move(m));
                continue;
            }
            bool validMove = false;
            for (auto & possibleMove : possibleMoves) {
                if (num == string(*possibleMove)) {
                    validMove = true;
                    break;
                }
            }
            if (validMove) {
                m = v.ParseMove(num);
                board->ApplyMove(std::move(m));
            } else {
                cout << "That wasn't a valid move." << endl;
            }
        } else if (command == "undo") {
            istringstream parse{ num };
            int n;
            parse >> n;
            for (int i = 0; i < n; i++) {
                if (board->GetMoveHistory().empty()) {
                    break;
                }
                board->UndoLastMove();
            }
        } else if (command == "showHistory") {
            auto & history = board->GetMoveHistory();
            auto player = board->GetCurrentPlayer();
            int x = int(player);
            for (auto i = history.rbegin(); i != history.rend(); ++i) {
                if (x == -1) {
                    cout << "Black" << " : " << **i << endl;
                }
                if (x == 1) {
                    cout << "White" << " : " << **i << endl;
                }
                x = x * -1;
            }
        } else if (command == "showValue") {
            cout << "Value: " << board->GetValue() << endl;
        } else if (command == "quit") {
            break;
        } else {
            cout << "invalid move" << endl;
        }

	} while (!board->IsFinished());
    int winner = board->GetValue();
    if (winner > 0) {
        cout << "Game over. Black wins!";
    } else if (winner < 0) {
        cout << "Game over. White wins!";
    } else {
        cout << "Game over. It's a tie!";
    }
}