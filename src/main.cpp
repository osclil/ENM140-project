/* main.cpp */

#include <iostream>
#include <string>
#include <utility>

#include "move_gen.h"
#include "minmax_impl.h"

void print_board(const board &b)
{
	for (int i = 0; i < b.get_height(); i++)
	{
		for (int j = 0; j < b.get_width(); j++)
			std::cout << static_cast<std::uint32_t>(to_underlying(b.at(i, j))) << ' ';
		std::cout << std::endl;
	}
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
	// std::string FEN_START = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	// std::string FEN_EXAMPLE1 = "rkr/ppp/3/PPP/RKR"; /* The 5x3 example shown */
	// std::string FEN_CHECKMATE = "K7/1q6/2k5/8/8/8/8/8";

	// /* This FEN should have 23 moves to make for black and 38 for white */
	// std::string FEN_TESTING = "rnbqk1rQ/4bn2/pppp1p2/4R2B/B3p1pp/PPPPPPPP/8/1NB1K1NR";

	// board b = board::from_fen(FEN_TESTING);
	// move_gen mg = move_gen(&b, true);
	// std::vector<board::move> num_legal_moves_test_w = mg.all_legal_moves();

	// std::cout << "Number of legal moves for white: " << num_legal_moves_test_w.size() << std::endl;

	// b.move_piece(num_legal_moves_test_w[0]);
	// mg.change_turn();
	// std::vector<board::move> num_legal_moves_test_b = mg.all_legal_moves();
	// std::cout << "FEN after first move: " << b.to_fen() << std::endl;
	// std::cout << "Number of legal moves for black: " << num_legal_moves_test_b.size() << std::endl;

	// b.undo_move(num_legal_moves_test_w[0], piece::e_VOID);
	// mg.change_turn();
	// std::cout << "FEN after undoing first move: " << b.to_fen() << std::endl;
	// std::cout << "Number of legal moves for white: " << num_legal_moves_test_w.size() << std::endl;

	// std::cout << "Outcome: " << mg.evaluate() << std::endl;

	std::string MINMAX_TEST; 
	int depth;
	// MINMAX_TEST = "k/p/P/K";
	std::cout << "FEN: ";
	std::cin >> MINMAX_TEST;
	std::cout << "Depth: ";
	std::cin >> depth;
	board b2 = board::from_fen(MINMAX_TEST);
	move_gen mg2 = move_gen(&b2, true);
	MinMax mm(mg2);

	std::cout << "Board: " << std::endl;
	print_board(b2);

	auto p = mm.comparePruning(b2, depth, true);
	std::cout << "Time taken for simple minmax: " << p.first.count() << std::endl;
	std::cout << "Time taken for alpha-beta minmax: " << p.second.count() << std::endl;
	std::cout << "Ratio: " << p.first.count()/p.second.count() << std::endl;
	
	// int i = 20;
	// while (i--)
	// {
	// 	mg2 = move_gen(&b2, mg2.m_whites_turn);
	// 	std::pair<bool, std::pair<int, board::move>> best_move = mm.findBestMove(b2, depth, mg2.m_whites_turn, true);
	// 	std::cout << "Player's turn: " << (mg2.m_whites_turn ? "white" : "black") << std::endl;
	// 	std::cout << "Current evaluation: " << best_move.second.first << std::endl;
	// 	if (!best_move.first){
	// 		std::cout << "No legal moves!" << std::endl;
	// 		break;
	// 	}
	// 	b2.move_piece(best_move.second.second);
	// 	std::cout << "Board: " << std::endl;
	// 	print_board(b2);
	// 	mg2.change_turn();
	// }

	// Depth limit test
	if (mm.depth_limit_reached)
		std::cout << "Depth limit reached!" << std::endl;
	else
		std::cout << "Depth limit not reached!" << std::endl;

	return 0;
};
