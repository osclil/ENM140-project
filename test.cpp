// Tic Tac Toe class implementation to test minmax

#include "minmax_impl.h"
#include <iostream>
#include <vector>
#include <algorithm>

// Tic Tac Toe class implementation to test minmax
class TicTacToe {
public:
    TicTacToe() {
        board = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
    }
    char currentPlayer = 'X';

    std::vector<std::vector<char>> getBoard() {
        return board;
    }

    std::vector<std::pair<int, int>> generateLegalMoves() {
        std::vector<std::pair<int, int>> legalMoves;

        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board[i][j] == ' ') {
                    legalMoves.push_back(std::make_pair(i, j));
                }
            }
        }

        return legalMoves;
    }

    void makeMove(std::pair<int, int> move) {
        board[move.first][move.second] = currentPlayer;
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void undoMove(std::pair<int, int> move) {
        board[move.first][move.second] = ' ';
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    bool isGameOver() {
        return (hasXWon() || hasOWon() || isDraw());
    }

    int evaluate() {
        if (hasXWon()) {
            return 10;
        }
        else if (hasOWon()) {
            return -10;
        }
        else {
            return 0;
        }
    }

private:
    bool hasXWon() {
        return hasPlayerWon('X');
    }

    bool hasOWon() {
        return hasPlayerWon('O');
    }

    bool hasPlayerWon(char player) {
        // Check rows
        for (int i = 0; i < board.size(); i++) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
                return true;
            }
        }

        // Check columns
        for (int i = 0; i < board.size(); i++) {
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
            return true;
        }

        if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
            return true;
        }

        return false;
    }

    bool isDraw() {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board.size(); j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }

        return true;
    }

    std::vector<std::vector<char>> board;
};

int main() {
    TicTacToe game;
    MinMax<TicTacToe, std::pair<int, int>> minmax;

    while (!game.isGameOver()) {
        std::pair<int, int> bestMove;
        // std::cout << game.currentPlayer << "'s turn" << std::endl;

        if (game.currentPlayer == 'X')
            bestMove = minmax.findBestMove(game, 9, true).second;
        else 
            bestMove = minmax.findBestMove(game, 9, false).second;
        
        game.makeMove(bestMove);

        std::vector<std::vector<char>> board = game.getBoard();
        for (int i = 0; i < board.size(); i++) {
            std::cout << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << std::endl;
        }
    }

    // std::vector<std::vector<char>> board = game.getBoard();

    // for (int i = 0; i < board.size(); i++) {
    //     std::cout << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << std::endl;
    // }

    return 0;
}