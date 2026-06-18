#include <iostream>
using namespace std;

char board[3][3] = {{'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'}};

void displayBoard() {
    cout << " ";
    for (int i = 0; i < 3; ++i)
        cout << " _";
    cout << endl;
    for (int i = 0; i < 3; ++i) {
        cout << " |";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j] << "|";
        }
        cout << endl;
    }
}

bool checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }

    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }

    return false;
}

bool isBoardFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '_') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    char currentPlayer = 'X';

    do {
        displayBoard();
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        // Check if the move is valid
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '_') {
            board[row][col] = currentPlayer;

            if (checkWin(currentPlayer)) {
                displayBoard();
                cout << "Player " << currentPlayer << " wins!" << endl;
                return 0;
            }

            if (isBoardFull()) {
                displayBoard();
                cout << "It's a draw!" << endl;
                return 0;
            }

            // Switch player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid move. Try again." << endl;
        }

    } while (true);

    return 0;
}
