#include <iostream>
#include "board.h"

Board::Board() {
    board = vector<char>(9, ' ');
}

void Board::display(int lastMoveIndex, char lastMoveMarker, const std::vector<int>& winningLine) {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        if (i == lastMoveIndex) {
            if (lastMoveMarker == 'X') {
                cout << "\033[1;31m"; 
            }
            else if (lastMoveMarker == 'O') {
                cout << "\033[1;34m"; 
            }
        }

        if (std::find(winningLine.begin(), winningLine.end(), i) != winningLine.end()) {
            if (board[i] == 'X') {
                cout << "\033[1;31m"; 
            }
            else if (board[i] == 'O') {
                cout << "\033[1;34m";
            }
        }

        cout << board[i];

        cout << "\033[0m";

        cout << ((i % 3 == 2) ? "\n" : " | ");
        if (i % 3 == 2 && i != 8) cout << "---------\n";
    }
    cout << "\n";
}
bool Board::isEmpty(int index) const {
    return board[index] == ' ';
}
void Board::removeMarker(int index) {
    board[index] = ' ';
}
bool Board::placeMarker(int position, char marker) {
    if (position < 0 || position > 8 || board[position] != ' ') return false;
    board[position] = marker;
    return true;
}
bool Board::twoInARow(char marker) {
    const int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6} 
    };

    for (int i = 0; i < 8; ++i) {
        int count = 0;
        int emptyIndex = -1;

        for (int j = 0; j < 3; ++j) {
            if (board[winConditions[i][j]] == marker) {
                count++;
            }
            else if (board[winConditions[i][j]] == ' ') {
                emptyIndex = winConditions[i][j];
            }
        }

        if (count == 2 && emptyIndex != -1) {
            return true;
        }
    }
    return false;
}
bool Board::checkWin(char marker, std::vector<int>& winningLine) {
    const int winConditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, 
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, 
        {0, 4, 8}, {2, 4, 6} 
    };

    for (int i = 0; i < 8; ++i) {
        if (board[winConditions[i][0]] == marker &&
            board[winConditions[i][1]] == marker &&
            board[winConditions[i][2]] == marker) {
            winningLine = { winConditions[i][0], winConditions[i][1], winConditions[i][2] };
            return true;
        }
    }

    return false;
}
bool Board::isDraw() {
    return count(board.begin(), board.end(), ' ') == 0;
}

void Board::reset() {
    fill(board.begin(), board.end(), ' ');
}