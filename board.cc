/* board.cc */

#include <cctype>
#include <algorithm>
#include <sstream>

#include "board.h"

std::string board::to_fen() const
{
	std::stringstream stream{};

	for (std::size_t i = 0; i < m_height; i++)
	{
		for (std::size_t j = 0; j < m_width; j++)
		{
			std::size_t zero_cnt = 0;
			while (j < m_width && m_board[i * m_width + j] == 0)
			{
				zero_cnt++;
				j++;
			}
			if (zero_cnt > 0)
				stream << zero_cnt;
			if (j == m_width)
				break;
			/* Could be done with significantly less code */
			/* Might consider doing that later */
			switch (m_board[i * m_width + j])
			{
				case 1:
					stream << 'p';
					break;
				case 2:
					stream << 'n';
					break;
				case 3:
					stream << 'b';
					break;
				case 4:
					stream << 'r';
					break;
				case 5:
					stream << 'q';
					break;
				case 6: 
					stream << 'k';
					break;
				case (1 << 3) | 1:
					stream << 'P';
					break;
				case (1 << 3) | 2:
					stream << 'N';
					break;
				case (1 << 3) | 3:
					stream << 'B';
					break;
				case (1 << 3) | 4:
					stream << 'R';
					break;
				case (1 << 3) | 5:
					stream << 'Q';
					break;
				case (1 << 3) | 6:
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
