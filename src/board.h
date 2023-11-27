/* board.h */

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <memory>
#include <cstdint>
#include <vector>

#include "piece.h"

class board
{
public:

	board(std::uint8_t width, std::uint8_t height, const std::string &FEN) :
		m_width(width),
		m_height(height),
		m_board(
			std::make_unique<piece[]>(
				width * height
			)
		)
	{
		load_fen(FEN);
	}

	std::string to_fen() const;

	static board from_fen(const std::string &);

	/* Performs no check at the moment */
	piece at(std::uint8_t row, std::uint8_t col) const { return m_board[row * m_width + col]; }
	piece& at(std::uint8_t row, std::uint8_t col) { return m_board[row * m_width + col]; }
	piece at(std::uint8_t index) const { return m_board[index]; }

	/* Hacky solution and doesn't perform any checks atm */
	const piece * operator[](std::uint8_t row) const { return m_board.get() + row * m_width; }
	piece * operator[](std::uint8_t row) { return m_board.get() + row * m_width; }

	std::vector<std::uint8_t> to_row_col(std::uint8_t index) const;

	std::uint8_t get_width() const noexcept { return m_width; }
	std::uint8_t get_height() const noexcept { return m_height; }

private:

	void load_fen(const std::string &);

	std::uint8_t m_width;
	std::uint8_t m_height;
	std::unique_ptr<piece[]> m_board;

};

#endif /* BOARD_H */

