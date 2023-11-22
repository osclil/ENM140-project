/* test.cc */

#include <iostream>
#include <string>

#include "board.h"

int main()
{
	const std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

	board b(8, 8, FEN);

	std::cout << "Loaded board" << std::endl;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			std::cout << b.at(i, j) << ' ';
		std::cout << std::endl;
	}
	return 0;
}
