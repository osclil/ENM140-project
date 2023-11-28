/* move_gen.cc */

#include "move_gen.h"
#include "piece.h"
#include <string>
#include <vector>

std::vector<std::string> move_gen::all_legal_moves() {
    std::vector<std::string> all_moves;
    std::uint8_t index = 0;
    std::vector<std::uint8_t> row_col;

    for (std::uint8_t i = 0; i < m_board.get_height() * m_board.get_width(); i++) {
        piece m_piece = m_board.at(index);
        
        if (m_piece != piece::e_EMPTY && ((m_whites_turn && is_white(m_piece)) || (!m_whites_turn && is_black(m_piece)))) {
            row_col = m_board.to_row_col(index);
            m_row = row_col[0];
            m_col = row_col[1];

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
        index++;
    }

    return all_moves;
}

// Temporarily move piece, convert m_board to FEN, then move piece back
std::string move_gen::gen_FEN(std::uint8_t row_to, std::uint8_t col_to) {
    piece captured = m_board.at(row_to, col_to);
    
    m_board.at(m_row, m_col) = piece::e_EMPTY;
    m_board.at(row_to, col_to) = m_piece;

    std::string move = m_board.to_fen();

    m_board.at(m_row, m_col) = m_piece;
    m_board.at(row_to, col_to) = captured;

    return move;
}

std::vector<std::string> move_gen::legal_moves_pawn() {
    std::uint8_t offset = (is_black(m_piece)) ? 1 : -1;
    std::vector<std::string> moves;

    // Check if square in front is empty
    if (m_board.at(m_row + offset, m_col) == piece::e_EMPTY) {
        moves.push_back(this->gen_FEN(m_row + offset, m_col));
    }

    if ((m_whites_turn && is_black(m_board.at(m_row + offset, m_col - 1))) || (!m_whites_turn && is_white(m_board.at(m_row + offset, m_col - 1)))) {
        moves.push_back(this->gen_FEN(m_row + offset, m_col - 1));
    }
    
    return moves;
}

std::vector<std::string> move_gen::legal_moves_knight() {
    std::vector<std::string> moves;

    return moves;
}

std::vector<std::string> move_gen::legal_moves_bishop() {
    std::vector<std::string> moves;

    return moves;
}

std::vector<std::string> move_gen::legal_moves_rook() {
    std::vector<std::string> moves;

    return moves;
}

std::vector<std::string> move_gen::legal_moves_queen() {
    std::vector<std::string> moves;

    return moves;
}

std::vector<std::string> move_gen::legal_moves_king() {
    std::vector<std::string> moves;

    return moves;
}

