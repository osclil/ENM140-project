/* main.cpp */

#include <iostream>
#include <string>
#include <utility>

#include "move_gen.h"
#include "minmax_impl.h"

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

	std::string MINMAX_TEST; 
	int maxDepth;
	std::cout << "FEN: ";
	std::cin >> MINMAX_TEST;
	std::cout << "Depth: ";
	std::cin >> maxDepth;
	std::cout << std::endl;

	std::cout << "White wins if evaluation is between " << 100000 - maxDepth << " to 100000" << std::endl;
	std::cout << "Black wins if evaluation is between " << -100000 - maxDepth << " to -100000" << std::endl;
	std::cout << "Draw if evaluation is between " << -maxDepth << " to 0" << std::endl;
	std::cout << std::endl;

	board b = board::from_fen(MINMAX_TEST);
	move_gen mg = move_gen(&b, true);
	MinMax mm(mg);

	std::cout << "Board: " << std::endl;
	print_board(b);

	// ------------------------------------------------------------

	// To test Minmax Simple, uncomment the following lines
	
	// int eval = mm.minmaxSimple(b, maxDepth, true, 0);
	// std::cout << "Evaluation: " << eval << std::endl;
	// std::cout << mm.result(eval, maxDepth) << std::endl;
	// mm.clearall();

	// ------------------------------------------------------------

	// To test Minmax Alpha-Beta with time, uncomment the following lines

	// std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	// int eval = mm.minmaxAlphaBeta(b, maxDepth, true, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 0);
	// std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	// std::cout << "Evaluation: " << eval << std::endl;
	// std::cout << mm.result(eval, maxDepth) << std::endl;
	// std::cout << "Depth limit: " << mm.depth_limit << std::endl;
	// std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[us]" << std::endl;
	// mm.clearall();

	// ------------------------------------------------------------

	// To test number of nodes, uncomment the following lines

	// std::cout << "Number of nodes: " << mm.getNodes(b, maxDepth, true, true) << std::endl;
	// mm.clearall();

	// ------------------------------------------------------------

	// To test compare pruning, uncomment the following lines

	// auto p = mm.comparePruning(b, maxDepth, true);
	// std::cout << "Time taken for simple minmax: " << p.first.count() << std::endl;
	// std::cout << "Time taken for alpha-beta minmax: " << p.second.count() << std::endl;
	// std::cout << "Ratio: " << p.first.count()/p.second.count() << std::endl;
	// mm.clearall();

	// ------------------------------------------------------------

	// To test getNodesAtDepth, uncomment the following lines

	// auto nodes = mm.getNodesAtDepth(b, maxDepth, true);
	// std::cout << "Number of nodes at maxDepth " << maxDepth << ": " << nodes << std::endl;
	// if (mm.isDepthLimitReached())
	// 	std::cout << "Depth limit reached!" << std::endl;
	// else
	// 	std::cout << "Depth limit not reached! All games ended before." << std::endl;
	
	// ------------------------------------------------------------

	// To test optimalPlay, uncomment the following lines

	// mm.optimalPlay(b, maxDepth, true, true, 100);

	// ------------------------------------------------------------

	// To test isDepthLimitReached, uncomment the following lines and comment
	// the mm.clearall() lines in the above tests

	// if (mm.isDepthLimitReached())
	// 	std::cout << "Depth limit reached!" << std::endl;
	// else
	// 	std::cout << "Depth limit not reached!" << std::endl;

	// ------------------------------------------------------------

	return 0;
};
