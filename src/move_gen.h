/* move_gen.h */

#ifndef MOVE_GEN_H
#define MOVE_GEN_H

#include "board.h"
#include <string>
#include <vector>

class move_gen {
    public:
        move_gen(board &board) : m_board(board) {}

        std::vector<std::string> all_legal_moves();

    private:
        board &m_board;

        std::string gen_move(std::uint8_t row_from, std::uint8_t col_from, std::uint8_t row_to, std::uint8_t col_to, piece &p);

        std::vector<std::string> legal_moves_pawn(piece p, u_int8_t row, u_int8_t col);
        std::vector<std::string> legal_moves_knight(piece p, u_int8_t row, u_int8_t col);
        std::vector<std::string> legal_moves_bishop(piece p, u_int8_t row, u_int8_t col);
        std::vector<std::string> legal_moves_rook(piece p, u_int8_t row, u_int8_t col);
        std::vector<std::string> legal_moves_queen(piece p, u_int8_t row, u_int8_t col);
        std::vector<std::string> legal_moves_king(piece p, u_int8_t row, u_int8_t col);

        bool is_empty(piece p) { return p == piece::e_EMPTY; }
        bool is_black(piece p) { return p >= piece::e_BLACK_PAWN && p <= piece::e_BLACK_KING; }
        bool is_white(piece p) { return p >= piece::e_WHITE_PAWN && p <= piece::e_WHITE_KING; }  
};

#endif /* move_gen.h */