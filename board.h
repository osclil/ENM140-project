/* board.h */

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <memory>
#include <cstdint>

/**
 *
 * Current internal representation of pieces
 * Subject to change
 * 0 - Empty square
 * Pieces:
 * 1 - Pawn
 * 2 - Knight
 * 3 - Bishop
 * 4 - Rook
 * 5 - Queen
 * 6 - King
 * For white pieces bit 4 == 1
 * For black pieces bit 4 == 0
 * */

class board
{
public:

	board(std::uint32_t width, std::uint32_t height, const std::string &FEN) :
		m_width(width),
		m_height(height),
		m_board(
			std::make_unique<std::int32_t[]>(
				width * height
			)
		)
	{
		load_fen(FEN);
	}

	std::string to_fen() const;

	std::int32_t at(std::uint32_t row, std::uint32_t col) const { return m_board[row * m_width + col]; }

private:

	void load_fen(const std::string &);

	std::uint32_t m_width;
	std::uint32_t m_height;
	std::unique_ptr<std::int32_t[]> m_board;

};

#endif /* BOARD_H */

