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

	struct position
	{
		std::uint8_t row;
		std::uint8_t col;
	};

	board(std::uint8_t width, std::uint8_t height, const std::string &FEN) :
		m_black_king_pos({}),
		m_white_king_pos({}),
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
	piece at(std::uint8_t row, std::uint8_t col) const {
		if (row > m_height - 1 || col > m_width - 1)
			return piece::e_VOID;
		
		return m_board[row * m_width + col]; 
	}
	
	
	piece& at(std::uint8_t row, std::uint8_t col) {
		if (row > m_height - 1 || col > m_width - 1)
			return m_void;
		
		return m_board[row * m_width + col];	
	}
	
	
	piece at(std::uint8_t index) const {
		if (index > m_height * m_width - 1)
			return piece::e_VOID;
		
		return m_board[index];
	}

	position to_pos(const std::uint8_t index) const noexcept
	{
		return {
			static_cast<std::uint8_t>(index / m_width),
			static_cast<std::uint8_t>(index % m_width)
		};
	}
		

	position get_black_king_pos() const noexcept
	{
		return m_black_king_pos;
	}

	position get_white_king_pos() const noexcept
	{
		return m_white_king_pos;
	}

	/* Hacky solution and doesn't perform any checks atm */
	const piece * operator[](std::uint8_t row) const { return m_board.get() + row * m_width; }
	piece * operator[](std::uint8_t row) { return m_board.get() + row * m_width; }

	std::uint8_t get_width() const noexcept { return m_width; }
	std::uint8_t get_height() const noexcept { return m_height; }

private:

	void load_fen(const std::string &);

	position m_black_king_pos;
	position m_white_king_pos;

	std::uint8_t m_width;
	std::uint8_t m_height;
	
	std::unique_ptr<piece[]> m_board;

	piece m_void = piece::e_VOID;

};

#endif /* BOARD_H */

