/* test.cc */

#include <iostream>
#include <string>
#include <utility>

#include "board.h"

void test_board(const std::string &fen)
{
	board b = board::from_fen(fen);

	std::cout << "Loaded board from FEN: " << fen << std::endl;

	for (int i = 0; i < b.get_height(); i++)
	{
		for (int j = 0; j < b.get_width(); j++)
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

	const std::string FEN_EXAMPLE1 = "rkr/ppp/3/PPP/RKR"; /* The 5x3 example shown */

	test_board(FEN_START);
	test_board(FEN_DANISH);
	test_board(FEN_GRUENFELD);

	test_board(FEN_EXAMPLE1);

	for (std::size_t i = 0; i < 1000000; i++)
		test_board(FEN_EXAMPLE1);

	return 0;
}
