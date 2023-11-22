/* board.cc */

#include <cctype>
#include <algorithm>

#include "board.h"

std::string board::to_fen() const
{
	return ""; /* TODO */
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
				0
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
				m_board[current_index++] = 1;
				break;
			case 'n':
				m_board[current_index++] = 2;
				break;
			case 'b':
				m_board[current_index++] = 3;
				break;
			case 'r':
				m_board[current_index++] = 4;
				break;
			case 'q':
				m_board[current_index++] = 5;
				break;
			case 'k':
				m_board[current_index++] = 6;
				break;
			case 'P':
				m_board[current_index++] = (1 << 3) | 1;
				break;
			case 'N':
				m_board[current_index++] = (1 << 3) | 2;
				break;
			case 'B':
				m_board[current_index++] = (1 << 3) | 3;
				break;
			case 'R':
				m_board[current_index++] = (1 << 3) | 4;
				break;
			case 'Q':
				m_board[current_index++] = (1 << 3) | 5;
				break;
			case 'K':
				m_board[current_index++] = (1 << 3) | 6;
				break;
			/* TODO, check error */
			default:
				break;
		}
	}
	/* TODO, handle case when current_index != m_width * m_height */
}
