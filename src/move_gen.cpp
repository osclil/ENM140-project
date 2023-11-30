/* move_gen.cc */

#include "move_gen.h"
#include <string>
#include <vector>
#include <iostream>

void append_moves(std::vector<board::move> &moves, std::vector<board::move> &new_moves) {
    moves.insert(moves.end(), new_moves.begin(), new_moves.end());
}

void append_FENs(std::vector<std::string> &FENs, std::vector<std::string> &new_FENs) {
    FENs.insert(FENs.end(), new_FENs.begin(), new_FENs.end());
}

std::vector<board::move> move_gen::all_possible_moves() {
	std::vector<board::move> all_possible_moves;

    // Loop all over all squares on the board
    // TODO: Implement so we don't have to loop over empty squares
    for (std::int8_t i = 0; i < m_board.get_height() * m_board.get_width(); i++) {
        m_piece = m_board.at(i);

        // If the square is a piece of the same color as the player whose turn it is, generate moves for it
        if ((m_whites_turn && is_white(m_piece)) || (!m_whites_turn && is_black(m_piece))) {
            m_pos = m_board.to_pos(i);

            std::vector<board::move> piece_moves;

			switch (m_piece)
			{
				case piece::e_BLACK_PAWN:
                    piece_moves = this->legal_moves_pawn();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_BLACK_KNIGHT:
                    piece_moves = this->legal_moves_knight();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_BLACK_BISHOP:
                    piece_moves = this->legal_moves_bishop();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_BLACK_ROOK:
                    piece_moves = this->legal_moves_rook();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_BLACK_QUEEN:
                    piece_moves = this->legal_moves_queen();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_BLACK_KING: 
                    piece_moves = this->legal_moves_king();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_WHITE_PAWN:
                    piece_moves = this->legal_moves_pawn();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_WHITE_KNIGHT:
                    piece_moves = this->legal_moves_knight();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_WHITE_BISHOP:
                    piece_moves = this->legal_moves_bishop();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_WHITE_ROOK:
                    piece_moves = this->legal_moves_rook();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_WHITE_QUEEN:
                    piece_moves = this->legal_moves_queen();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				case piece::e_WHITE_KING:
                    piece_moves = this->legal_moves_king();
                    append_moves(all_possible_moves, piece_moves);
                    break;
				default:
       					break;
			}
        }
    }

    return all_possible_moves;
}

std::vector<std::string> move_gen::all_legal_moves() {
    std::vector<std::string> FENs;
    std::vector<board::move> all_possible_moves = this->all_possible_moves();
    std::cout << "All possible moves: " << all_possible_moves.size() << std::endl;

    std::vector<board::move> counter_moves;

    for (auto move : all_possible_moves) {
        piece piece_from = m_board.at(move.from.row, move.from.col);
        piece piece_to = m_board.at(move.to.row, move.to.col);

        // Temporarily move piece
        m_board.at(move.from.row, move.from.col) = piece::e_EMPTY;
        m_board.at(move.to.row, move.to.col) = piece_from;
        
        // Calculate all possible moves from the new board from the opponent's perspective
        m_whites_turn = !m_whites_turn;
        counter_moves = this->all_possible_moves();
        m_whites_turn = !m_whites_turn;

        // Check if any of the counter moves captures the king
        piece king = (m_whites_turn) ? piece::e_WHITE_KING : piece::e_BLACK_KING;
        bool king_captured = false;

        for (auto counter_move : counter_moves) {
            if (m_board.at(counter_move.to.row, counter_move.to.col) == king) {
                king_captured = true;
                break;
            }
        }

        // If the king cannot be captured, we cannot be in check, so the move is legal
        if (!king_captured) {
            FENs.push_back(m_board.to_fen());
        }

        // Move piece back
        m_board.at(move.from.row, move.from.col) = piece_from;
        m_board.at(move.to.row, move.to.col) = piece_to;
    }

    return FENs;
}

bool move_gen::square_is_empty(std::int8_t row, std::int8_t col) {
    return m_board.at(row, col) == piece::e_EMPTY;
}

bool move_gen::square_is_enemy(std::int8_t row, std::int8_t col) {
    return (m_whites_turn && is_black(m_board.at(row, col))) || (!m_whites_turn && is_white(m_board.at(row, col)));
}

bool move_gen::square_is_moveable(std::int8_t row, std::int8_t col) {
    return square_is_empty(row, col) || square_is_enemy(row, col);
}

bool move_gen::square_is_movable(board::position pos) {
    return square_is_moveable(pos.row, pos.col);
}

std::vector<board::move> move_gen::legal_moves_pawn() {
    std::int8_t offset = (is_black(m_piece)) ? 1 : -1;
    std::vector<board::move> moves;

    std::int8_t to_row = static_cast<std::int8_t>(m_pos.row + offset);

    if (square_is_empty(m_pos.row + offset, m_pos.col)) {
        moves.push_back(board::move{m_pos, board::position{to_row, m_pos.col}});
    }

    if (square_is_enemy(m_pos.row + offset, m_pos.col - 1)) {
        moves.push_back(board::move{m_pos, board::position{to_row, static_cast<std::int8_t>(m_pos.col - 1)}});
    }

    if (square_is_enemy(m_pos.row + offset, m_pos.col + 1)) {
        moves.push_back(board::move{m_pos, board::position{to_row, static_cast<std::int8_t>(m_pos.col + 1)}});
    }

    return moves;
}

std::vector<board::move> move_gen::legal_moves_knight() {
    std::vector<board::move> moves;
    board::position to_pos;

    // Knight moves: eight possible movements
    const int8_t rowOffsets[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    const int8_t colOffsets[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for (std::int8_t i = 0; i < 8; ++i) {
        to_pos.row = m_pos.row + rowOffsets[i];
        to_pos.col = m_pos.col + colOffsets[i];

        if (square_is_movable(to_pos)) {
            moves.push_back({m_pos, to_pos});
        }
    }

    return moves;
}



/* ANYONE */
std::vector<board::move> move_gen::legal_moves_bishop() {
    std::vector<board::move> moves;

    return moves;
}

/* ANYONE */
std::vector<board::move> move_gen::legal_moves_rook() {
    std::vector<board::move> moves;

    return moves;
}

/* ANYONE */
std::vector<board::move> move_gen::legal_moves_queen() {
    std::vector<board::move> moves;

    return moves;
}

/* SAMUEL */
std::vector<board::move> move_gen::legal_moves_king() {
    std::vector<board::move> moves;

    return moves;
}

