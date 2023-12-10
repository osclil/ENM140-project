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
    // Global variables to change as needed
    const std::vector<std::string> FENs = {
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

    std::ofstream outfile;
    outfile.open("./data/data.csv");

    // ---------------------------------------------- //

    // Stores result in the following format:
    // FEN, Evaluation, MinMaxAlphaBeta Depth Limit, MinMaxAlphaBeta Time, MinMaxSimple Depth Limit, MinMaxSimple Time, Total Nodes

    std::unordered_map<std::string, std::vector<std::string>> output;
    for (auto FEN : FENs) output[FEN] = std::vector<std::string>({});

    // ---------------------------------------------- //

    #pragma omp parallel for
    for (auto FEN : FENs){
        board b = board::from_fen(FEN);
        move_gen mg = move_gen(&b, true);
        MinMax mm(mg);

        auto alphabeta_start = std::chrono::high_resolution_clock::now();
        int eval = mm.minmaxAlphaBeta(b, maxDepth, true, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 0);
        auto alphabeta_stop = std::chrono::high_resolution_clock::now();
        auto alphabeta_duration = std::chrono::duration_cast<std::chrono::duration<double>>(alphabeta_stop - alphabeta_start);
        int alphabeta_depth_limit = mm.depth_limit;

        #pragma omp critical (output)
        output[FEN].push_back(std::to_string(eval));
        output[FEN].push_back(std::to_string(alphabeta_depth_limit));
        output[FEN].push_back(std::to_string(alphabeta_duration.count()));

        if (mm.isDepthLimitReached()) {
            std::cout << "Depth limit reached for " << FEN << " in alpha-beta minmax." << std::endl;
            std::cout << "Increase maxDepth or decrease branching factor for perfect results.";
            continue;
        }
    }

    std::cout << "Alpha-beta minmax done." << std::endl;

    #pragma omp parallel for
    for (auto FEN : FENs){
        board b = board::from_fen(FEN);
        move_gen mg = move_gen(&b, true);
        MinMax mm(mg);

        auto simple_start = std::chrono::high_resolution_clock::now();
        int eval = mm.minmaxSimple(b, maxDepth, true, 0);
        auto simple_stop = std::chrono::high_resolution_clock::now();
        auto simple_duration = std::chrono::duration_cast<std::chrono::duration<double>>(simple_stop - simple_start);
        int simple_depth_limit = mm.depth_limit;

        #pragma omp critical (output)
        output[FEN].push_back(std::to_string(simple_depth_limit));
        output[FEN].push_back(std::to_string(simple_duration.count()));

        if (mm.isDepthLimitReached()) {
            std::cout << "Depth limit reached for " << FEN << " in simple minmax." << std::endl;
            std::cout << "Increase maxDepth or decrease branching factor for perfect results.";
            continue;
        }
    }

    std::cout << "Simple minmax done." << std::endl;

    #pragma omp parallel for
    for (auto FEN : FENs){
        board b = board::from_fen(FEN);
        move_gen mg = move_gen(&b, true);
        MinMax mm(mg);

        auto nodes = mm.getNodes(b, maxDepth, true);

        #pragma omp critical (output)
        output[FEN].push_back(std::to_string(nodes));
    }

    std::cout << "Nodes counted." << std::endl;

    // ---------------------------------------------- //

    outfile << "FEN,Evaluation,MinMaxAlphaBeta Depth Limit,MinMaxAlphaBeta Time,MinMaxSimple Depth Limit,MinMaxSimple Time,Total Nodes" << std::endl;

    for (auto FEN : FENs){
        outfile << FEN << ',';
        for (auto s : output[FEN]) outfile << s << ',';
        outfile << std::endl;
    }

    outfile.close();

    return 0;
}