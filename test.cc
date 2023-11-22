/* test.cc */

#include <iostream>
#include <string>
#include <utility>

#include "board.h"

void test_board(std::uint32_t width, std::uint32_t height, const std::string &fen)
{
	board b(width, height, fen);

	std::cout << "Loaded board from FEN: " << fen << std::endl;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			std::cout << static_cast<std::uint32_t>(std::to_underlying(b.at(i, j))) << ' ';
		std::cout << std::endl;
	}

	const std::string fen_test = b.to_fen();
	std::cout << "FEN computed from board: " << fen_test << std::endl;
	if (fen == fen_test)
		std::cout << "FEN checks out!" << std::endl;
	else
		std::cout << "FEN does not check out!" << std::endl;
	
}

int main()
{
	const std::string FEN_START = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	const std::string FEN_DANISH = "rnbqkbnr/pppp1ppp/8/8/3pP3/2P5/PP3PPP/RNBQKBNR";
	const std::string FEN_GRUENFELD = "rnbqkb1r/ppp1pp1p/5np1/3p4/2PP4/1QN5/PP2PPPP/R1B1KBNR";

	test_board(8, 8, FEN_START);
	test_board(8, 8, FEN_DANISH);
	test_board(8, 8, FEN_GRUENFELD);

	std::cout << (piece::e_BLACK_PAWN == piece::e_BLACK_PAWN) << std::endl;

	return 0;
}
