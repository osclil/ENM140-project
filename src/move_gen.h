/* move_gen.h */

#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include "board.h"
#include <string>
#include <vector>


/*
An instance of this class is created for each position where we want to generate
all possible moves. The constructor takes a FEN and a boolean indicating whose
turn it is and constructs the board. The object has row and col members which are
used to keep track of the position of the piece we are currently generating moves
for, as well as a piece member to keep track of the piece itself.
*/
class move_gen {
    public:
        move_gen(std::string &FEN , bool whites_turn) : m_board(board::from_fen(FEN)), m_pos({}), m_whites_turn(whites_turn) {};

        std::vector<std::string> all_legal_moves();

    private:

	board m_board;
	board::position m_pos;
	piece m_piece;
        bool m_whites_turn;

        std::string gen_FEN(std::uint8_t row_to, std::uint8_t col_to);
        bool square_is_empty(std::uint8_t row, std::uint8_t col);
        bool square_is_enemy(std::uint8_t row, std::uint8_t col);
        bool square_is_moveable(std::uint8_t row, std::uint8_t col);
        bool square_is_movable(board::position pos);

        std::vector<std::string> legal_moves_pawn();
        std::vector<std::string> legal_moves_knight();
        std::vector<std::string> legal_moves_bishop();
        std::vector<std::string> legal_moves_rook();
        std::vector<std::string> legal_moves_queen();
        std::vector<std::string> legal_moves_king();
};

#endif /* move_gen.h */
