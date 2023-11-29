/* move_gen.cc */

#include "move_gen.h"
#include <string>
#include <vector>
#include <iostream>

/* OSCAR WILL: 
    1. Do king raycasting
    2  Do eval function
*/

std::vector<std::string> move_gen::all_legal_moves() {
	std::vector<std::string> all_moves;

    // Loop all over all squares on the board
    for (std::uint8_t i = 0; i < m_board.get_height() * m_board.get_width(); i++) {
        m_piece = m_board.at(i);

        // If the square is a piece of the same color as the player whose turn it is, generate moves for it
        if ((m_whites_turn && is_white(m_piece)) || (!m_whites_turn && is_black(m_piece))) {
            m_pos = m_board.to_pos(i);

            std::vector<std::string> piece_moves;

			switch (m_piece)
			{
				case piece::e_BLACK_PAWN:
                    piece_moves = this->legal_moves_pawn();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_BLACK_KNIGHT:
                    piece_moves = this->legal_moves_knight();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_BLACK_BISHOP:
                    piece_moves = this->legal_moves_bishop();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_BLACK_ROOK:
                    piece_moves = this->legal_moves_rook();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_BLACK_QUEEN:
                    piece_moves = this->legal_moves_queen();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_BLACK_KING: 
                    piece_moves = this->legal_moves_king();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_WHITE_PAWN:
                    piece_moves = this->legal_moves_pawn();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_WHITE_KNIGHT:
                    piece_moves = this->legal_moves_knight();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_WHITE_BISHOP:
                    piece_moves = this->legal_moves_bishop();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_WHITE_ROOK:
                    piece_moves = this->legal_moves_rook();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_WHITE_QUEEN:
                    piece_moves = this->legal_moves_queen();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_WHITE_KING:
                    piece_moves = this->legal_moves_king();
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				default:
       					break;
			}
        }
    }

    return all_moves;
}

// Temporarily move piece, convert m_board to FEN, then move piece back
std::string move_gen::gen_FEN(std::uint8_t row_to, std::uint8_t col_to) {
    piece captured = m_board.at(row_to, col_to);

    m_board.at(m_pos.row, m_pos.col) = piece::e_EMPTY;
    m_board.at(row_to, col_to) = this->m_piece;

    std::string move = m_board.to_fen();

    m_board.at(m_pos.row, m_pos.col) = this->m_piece;
    m_board.at(row_to, col_to) = captured;

    return move;
}

bool move_gen::square_is_empty(std::uint8_t row, std::uint8_t col) {
    return m_board.at(row, col) == piece::e_EMPTY;
}

bool move_gen::square_is_enemy(std::uint8_t row, std::uint8_t col) {
    return (m_whites_turn && is_black(m_board.at(row, col))) || (!m_whites_turn && is_white(m_board.at(row, col)));
}

bool move_gen::square_is_moveable(std::uint8_t row, std::uint8_t col) {
    return square_is_empty(row, col) || square_is_enemy(row, col);
}

bool move_gen::square_is_movable(board::position pos) {
    return square_is_moveable(pos.row, pos.col);
}

/* SAMUEL */
std::vector<std::string> move_gen::legal_moves_pawn() {
    std::uint8_t offset = (is_black(m_piece)) ? 1 : -1;
    std::vector<std::string> moves;

    // Check if square in front is empty
    if (square_is_empty(m_pos.row + offset, m_pos.col)) {
        moves.push_back(this->gen_FEN(m_pos.row + offset, m_pos.col));
    }

    if (square_is_enemy(m_pos.row + offset, m_pos.col - 1)) {
        moves.push_back(this->gen_FEN(m_pos.row + offset, m_pos.col - 1));
    }

    if (square_is_enemy(m_pos.row + offset, m_pos.col + 1)) {
        moves.push_back(this->gen_FEN(m_pos.row + offset, m_pos.col + 1));
    }

    return moves;
}

/* SAMUEL */
std::vector<std::string> move_gen::legal_moves_knight() {
    std::vector<std::string> moves;
    board::position pos;

    // Knight moves: eight possible movements
    const int rowOffsets[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    const int colOffsets[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (uint8_t i = 0; i < 8; ++i) {
        pos.row = m_pos.row + rowOffsets[i];
        pos.col = m_pos.col + colOffsets[i];

        if (square_is_movable(pos)) {
            moves.push_back(this->gen_FEN(pos.row, pos.col));
        }
    }

    return moves;
}



/* ANYONE */
std::vector<std::string> move_gen::legal_moves_bishop() {
    std::vector<std::string> moves;

    return moves;
}

/* ANYONE */
std::vector<std::string> move_gen::legal_moves_rook() {
    std::vector<std::string> moves;

    return moves;
}

/* ANYONE */
std::vector<std::string> move_gen::legal_moves_queen() {
    std::vector<std::string> moves;

    return moves;
}

/* SAMUEL */
std::vector<std::string> move_gen::legal_moves_king() {
    std::vector<std::string> moves;

    return moves;
}

