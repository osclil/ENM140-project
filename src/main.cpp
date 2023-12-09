/* main.cpp */

#include <iostream>
#include <string>
#include <utility>

#include "move_gen.h"
#include "minmax_impl.h"

// void print_board(const board &b)
// {
// 	for (int i = 0; i < b.get_height(); i++)
// 	{
// 		for (int j = 0; j < b.get_width(); j++)
// 			std::cout << static_cast<std::uint32_t>(to_underlying(b.at(i, j))) << ' ';
// 		std::cout << std::endl;
// 	}
// }

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
	std::cout << std::endl;

	std::cout << "White wins if evaluation is between " << 100000 - depth << " to 100000" << std::endl;
	std::cout << "Black wins if evaluation is between " << -100000 - depth << " to -100000" << std::endl;
	std::cout << "Draw if evaluation is between " << -depth << " to 0" << std::endl;
	std::cout << std::endl;

	board b2 = board::from_fen(MINMAX_TEST);
	move_gen mg2 = move_gen(&b2, true);
	MinMax mm(mg2);

	std::cout << "Board: " << std::endl;
	print_board(b2);

	// int eval = mm.minmaxSimple(b2, depth, true, 0);
	// std::cout << "Evaluation: " << eval << std::endl;
	// std::cout << mm.result(eval, depth) << std::endl;
	// mm.clearall();

	// std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	// int eval = mm.minmaxAlphaBeta(b2, depth, true, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 0);
	// std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	// std::cout << "Evaluation: " << eval << std::endl;
	// std::cout << mm.result(eval, depth) << std::endl;
	// std::cout << "Depth limit: " << mm.depth_limit << std::endl;
	// std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
	// mm.clearall();

	// std::cout << "Number of nodes: " << mm.getNodes(b2, depth, true, true) << std::endl;
	// mm.clearall();

	// auto p = mm.comparePruning(b2, depth, true);
	// std::cout << "Time taken for simple minmax: " << p.first.count() << std::endl;
	// std::cout << "Time taken for alpha-beta minmax: " << p.second.count() << std::endl;
	// std::cout << "Ratio: " << p.first.count()/p.second.count() << std::endl;
	// mm.clearall();

	// auto nodes = mm.getNodesAtDepth(b2, depth, true);
	// std::cout << "Number of nodes at depth " << depth << ": " << nodes << std::endl;
	// if (mm.isDepthLimitReached())
	// 	std::cout << "Depth limit reached!" << std::endl;
	// else
	// 	std::cout << "Depth limit not reached! All games ended before." << std::endl;
	
	mm.optimalPlay(b2, depth, true, true, 100);

	// Depth limit test
	// if (mm.isDepthLimitReached())
	// 	std::cout << "Depth limit reached!" << std::endl;
	// else
	// 	std::cout << "Depth limit not reached!" << std::endl;

	return 0;
};
