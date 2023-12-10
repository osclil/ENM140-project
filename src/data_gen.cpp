/* main.cpp */

#include <iostream>
#include <string>
#include <utility>
#include <fstream>

#include "move_gen.h"
#include "minmax_impl.h"

void file_board(std::ofstream& outfile, board& b)
{
    for (int i = 0; i < b.get_height(); i++)
	{
		for (int j = 0; j < b.get_width(); j++)
			outfile << static_cast<std::uint32_t>(to_underlying(b.at(i, j))) << ' ';
		outfile << std::endl;
	}
}

int main()
{
    std::vector<std::string> FENs = {
        "k/p/P/K",
        "k/p/1/P/K",
        "k/p/1/1/P/K",
        "k/p/1/1/1/P/K",
        "k/p/1/1/1/1/P/K",
        "k/p/1/1/1/1/1/P/K",
        "k/p/1/1/1/1/1/1/P/K",
        "k/p/1/1/1/1/1/1/1/P/K"
    };

    int maxDepth = 100;

    // open a file in write mode.
    std::ofstream outfile;
    outfile.open("./data/data.csv");

    // output column names with seperator
    outfile << "FEN,Evaluation,MinMaxSimple Depth Limit,MinMaxAlphaBeta Depth Limit,MinMaxSimple Time,MinMaxAlphaBeta Time,Total Nodes" << std::endl;

    // ---------------------------------------------- //

    int i = 1;
    for (auto FEN : FENs) {
        board b = board::from_fen(FEN);
        move_gen mg = move_gen(&b, true);
        MinMax mm(mg);

        auto simple_start = std::chrono::high_resolution_clock::now();
        int eval = mm.minmaxSimple(b, maxDepth, true, 0);
        auto simple_stop = std::chrono::high_resolution_clock::now();
        auto simple_duration = std::chrono::duration_cast<std::chrono::duration<double>>(simple_stop - simple_start);
        int simple_depth_limit = mm.depth_limit;
        if (mm.isDepthLimitReached()) {
            std::cout << "Depth limit reached for " << FEN << " in simple minmax." << std::endl;
            std::cout << "Increase maxDepth or decrease branching factor for perfect results.";
            continue;
        }
        mm.clearall();

        auto alphabeta_start = std::chrono::high_resolution_clock::now();
        eval = mm.minmaxAlphaBeta(b, maxDepth, true, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 0);
        auto alphabeta_stop = std::chrono::high_resolution_clock::now();
        auto alphabeta_duration = std::chrono::duration_cast<std::chrono::duration<double>>(alphabeta_stop - alphabeta_start);
        int alphabeta_depth_limit = mm.depth_limit;
        if (mm.isDepthLimitReached()) {
            std::cout << "Depth limit reached for " << FEN << " in alpha-beta minmax." << std::endl;
            std::cout << "Increase maxDepth or decrease branching factor for perfect results.";
            continue;
        }
        mm.clearall();

        auto nodes = mm.getNodes(b, maxDepth, true);

        outfile << FEN << ',' << eval << ',' << simple_depth_limit << ',' << alphabeta_depth_limit << ',' << simple_duration.count() << ',' << alphabeta_duration.count() << ',' << nodes << std::endl;

        std::cout << i << " of " << FENs.size() << " done." << std::endl;
        i++;
    }

    outfile.close();

    return 0;
}