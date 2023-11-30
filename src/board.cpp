/* board.cc */

#include <cctype>
#include <algorithm>
#include <sstream>
#include "board.h"

/* TODO: 
	1. Skriva om från vector till pair för att hålla koll på positioner
	2. Lägga till pairs för kungarnas position i board.h
	3. Raycasting från kungen för att se om den är i schack
*/

/* Deduce width and height from the FEN and returns a board object */
board board::from_fen(const std::string &FEN)
{
	std::int8_t width = 0;
	std::int8_t height = FEN.size() > 0 ? 1 : 0;

	bool first_row = true;

	for (const char c : FEN)
	{
		if (c == '/')
		{
			height++;
			first_row = false;
			continue;
		}
		
		if (first_row)
		{
			if (std::isdigit(c))
				width += static_cast<std::int8_t>(c - '0');
			else
      				width++;
		}
	}

	return { width, height, FEN };
}

std::string board::to_fen() const
{
	std::stringstream stream{};

	for (std::size_t i = 0; i < m_height; i++)
	{
		for (std::size_t j = 0; j < m_width; j++)
		{
			std::size_t empty_cnt = 0;
			while (j < m_width && m_board[i * m_width + j] == piece::e_EMPTY)
			{
				empty_cnt++;
				j++;
			}
			if (empty_cnt > 0)
				stream << empty_cnt;
			if (j == m_width)
				break;
			/* Could be done with significantly less code */
			/* Might consider doing that later */
			switch (m_board[i * m_width + j])
			{
				case piece::e_BLACK_PAWN:
					stream << 'p';
					break;
				case piece::e_BLACK_KNIGHT:
					stream << 'n';
					break;
				case piece::e_BLACK_BISHOP:
					stream << 'b';
					break;
				case piece::e_BLACK_ROOK:
					stream << 'r';
					break;
				case piece::e_BLACK_QUEEN:
					stream << 'q';
					break;
				case piece::e_BLACK_KING: 
					stream << 'k';
					break;
				case piece::e_WHITE_PAWN:
					stream << 'P';
					break;
				case piece::e_WHITE_KNIGHT:
					stream << 'N';
					break;
				case piece::e_WHITE_BISHOP:
					stream << 'B';
					break;
				case piece::e_WHITE_ROOK:
					stream << 'R';
					break;
				case piece::e_WHITE_QUEEN:
					stream << 'Q';
					break;
				case piece::e_WHITE_KING:
					stream << 'K';
					break;
				/* TODO, check error */
				default:
       					break;
			}
		}

		if (i < m_height - 1)
			stream << '/';
	}

	return stream.str();
}

void board::load_fen(const std::string &FEN)
{
	std::size_t current_index = 0;
	for (const char c : FEN)
	{
		/* Check case when digit */
		if (std::isdigit(c))
		{
			std::size_t length = static_cast<std::size_t>(c - '0');
			std::fill(
      				m_board.get() + current_index,
      				m_board.get() + current_index + length,
				piece::e_EMPTY
			);
			current_index += length;
			continue;
      		}

		/* Check case when newline */
		switch(c)
      		{
			case '/':
				break;
			case 'p':
				m_board[current_index++] = piece::e_BLACK_PAWN;
				break;
			case 'n':
				m_board[current_index++] = piece::e_BLACK_KNIGHT;
				break;
			case 'b':
				m_board[current_index++] = piece::e_BLACK_BISHOP;
				break;
			case 'r':
				m_board[current_index++] = piece::e_BLACK_ROOK;
				break;
			case 'q':
				m_board[current_index++] = piece::e_BLACK_QUEEN;
				break;
			case 'k':
				m_board[current_index++] = piece::e_BLACK_KING;
				m_black_king_pos = {
					static_cast<std::int8_t>(current_index / m_width),
					static_cast<std::int8_t>(current_index % m_width)
				};
				break;
			case 'P':
				m_board[current_index++] = piece::e_WHITE_PAWN;
				break;
			case 'N':
				m_board[current_index++] = piece::e_WHITE_KNIGHT;
				break;
			case 'B':
				m_board[current_index++] = piece::e_WHITE_BISHOP;
				break;
			case 'R':
				m_board[current_index++] = piece::e_WHITE_ROOK;
				break;
			case 'Q':
				m_board[current_index++] = piece::e_WHITE_QUEEN;
				break;
			case 'K':
				m_board[current_index++] = piece::e_WHITE_KING;
				m_white_king_pos = {
					static_cast<std::int8_t>(current_index / m_width),
					static_cast<std::int8_t>(current_index % m_width)
				};
				break;
			/* TODO, check error */
			default:
				break;
		}
	}
	/* TODO, handle case when current_index != m_width * m_height */
}

