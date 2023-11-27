/* move_gen.cc */

#include "move_gen.h"
#include "piece.h"
#include <string>
#include <vector>

std::vector<std::string> move_gen::all_legal_moves() {
    std::vector<std::string> all_moves;
    std::uint8_t index = 0;
    std::vector<std::uint8_t> row_col;
    std::uint8_t row = 0;
    std::uint8_t col = 0;

    for (uint8_t i = 0; i < m_board.get_height() * m_board.get_width(); i++) {
        piece p = m_board.at(index);
        
        if (p != piece::e_EMPTY) {
            row_col = m_board.to_row_col(index);
            row = row_col[0];
            col = row_col[1];

            std::vector<std::string> piece_moves;

			switch (p)
			{
				case piece::e_BLACK_PAWN:
                    piece_moves = legal_moves_pawn(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());
                    break;
				case piece::e_BLACK_KNIGHT:
                    piece_moves = legal_moves_knight(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_BLACK_BISHOP:
                    piece_moves = legal_moves_bishop(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_BLACK_ROOK:
                    piece_moves = legal_moves_rook(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_BLACK_QUEEN:
                    piece_moves = legal_moves_queen(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_BLACK_KING: 
                    piece_moves = legal_moves_king(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_WHITE_PAWN:
                    piece_moves = legal_moves_pawn(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_WHITE_KNIGHT:
                    piece_moves = legal_moves_knight(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_WHITE_BISHOP:
                    piece_moves = legal_moves_bishop(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_WHITE_ROOK:
                    piece_moves = legal_moves_rook(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_WHITE_QUEEN:
                    piece_moves = legal_moves_queen(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				case piece::e_WHITE_KING:
                    piece_moves = legal_moves_king(p, row, col);
					all_moves.insert(all_moves.end(), piece_moves.begin(), piece_moves.end());					break;
				/* TODO, check error */
				default:
       					break;
			}
        }
        index++;
    }

    return all_moves;
}

std::string move_gen::gen_move(std::uint8_t row_from, std::uint8_t col_from, std::uint8_t row_to, std::uint8_t col_to, piece &p) {
    piece captured = m_board.at(row_to, col_to);
    
    m_board.at(row_from, col_from) = piece::e_EMPTY;
    m_board.at(row_to, col_to) = p;

    std::string move = std::to_string(row_from) + std::to_string(col_from) + std::to_string(row_to) + std::to_string(col_to);

    m_board.at(row_from, col_from) = p;
    m_board.at(row_to, col_to) = captured;

    return move;
}

std::vector<std::string> move_gen::legal_moves_pawn(piece p, std::uint8_t row, std::uint8_t col) {
    std::uint8_t offset = (is_black(p)) ? 1 : -1;
    std::vector<std::string> moves;

    // Check if square in front is empty
    if (m_board.at(row + offset, col) == piece::e_EMPTY) {
        moves.push_back(gen_move(row, col, row + offset, col, p));
    }

    // Check if diagnoals are occupied by enemy
    

    return moves;
}

