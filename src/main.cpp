/* main.cpp */

#include <iostream>
#include <string>
#include <utility>

#include "move_gen.h"

void print_board(const board &b)
{
	for (int i = 0; i < b.get_height(); i++)
	{
		for (int j = 0; j < b.get_width(); j++)
			std::cout << static_cast<std::uint32_t>(to_underlying(b.at(i, j))) << ' ';
		std::cout << std::endl;
	}
}

std::vector<std::string> legal_moves(std::string &FEN, bool whites_turn)
{
	move_gen mg = move_gen(FEN, whites_turn);
	return mg.all_legal_moves();
}

void print_FEN(const std::string &FEN)
{
	board b = board::from_fen(FEN);
	print_board(b);
}

void test_board(const std::string &fen)
{
	board b = board::from_fen(fen);

	std::cout << "Loaded board from FEN: " << fen << std::endl;

	print_board(b);

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

	std::string FEN_EXAMPLE1 = "rkr/ppp/3/PPP/RKR"; /* The 5x3 example shown */

	test_board(FEN_START);
	test_board(FEN_DANISH);
	test_board(FEN_GRUENFELD);

	test_board(FEN_EXAMPLE1);

	std::vector<std::string> legal_moves_test = legal_moves(FEN_EXAMPLE1, true);
	std::vector<std::string> legal_moves_test2 = legal_moves(legal_moves_test[0], false);

	std::cout << std::endl;
	print_FEN(legal_moves_test[0]);
	std::cout << std::endl;
	
	for (size_t i = 0; i < legal_moves_test2.size(); i++) {
		print_FEN(legal_moves_test2[i]);
		std::cout << std::endl;
	}

	return 0;
};
