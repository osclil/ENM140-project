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
        move_gen(board* b , bool whites_turn) : m_board(b), m_pos({}), m_whites_turn(whites_turn) {};
        std::vector<board::move> all_legal_moves();
        int evaluate();

    private:
        bool in_check();
        std::vector<board::move> all_possible_moves();
        board* m_board;
        board::position m_pos;
        piece m_piece;
        bool m_whites_turn;
        bool square_is_empty(std::int8_t row, std::int8_t col);
        bool square_is_empty(board::position pos);
        bool square_is_enemy(std::int8_t row, std::int8_t col);
        bool square_is_moveable(std::int8_t row, std::int8_t col);
        bool square_is_movable(board::position pos);
        
        std::vector<board::move> check_file();
        std::vector<board::move> check_rank();
        std::vector<board::move> check_diagonal();

        std::vector<board::move> legal_moves_pawn();
        
        std::vector<board::move> legal_moves_knight();
        
        std::vector<board::move> legal_moves_bishop();
        
        std::vector<board::move> legal_moves_rook();
        
        std::vector<board::move> legal_moves_queen();
        
        std::vector<board::move> legal_moves_king();
};

#endif /* move_gen.h */
