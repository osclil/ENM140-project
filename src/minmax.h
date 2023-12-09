#ifndef MINMAX_H
#define MINMAX_H

#include <utility> // std::pair
#include <unordered_map> // std::unordered_map
#include <chrono> // std::chrono
#include <string> // std::string
#include "board.h"
#include "move_gen.h"

// Generic MinMax algorithm with various optimizations
class MinMax {
public:
    MinMax(move_gen& mg) : mg(mg) {};
    
    int minmaxSimple(board& state, int maxDepth, bool maximizingPlayer, int depth);
    int minmaxAlphaBeta(board& state, int maxDepth, bool maximizingPlayer, int alpha, int beta, int depth);
    std::pair<bool, std::pair<int, board::move>> findBestMove(board& state, int maxDepth, bool maximizingPlayer, bool alpha_beta, std::unordered_map<std::string, int>& stateTable);
    std::pair<std::chrono::duration<double>, std::chrono::duration<double>> comparePruning(board& state, int maxDepth, bool maximizingPlayer);
    long long int getNodes(board &state, int maxDepth, bool maximizingPlayer, bool alpha_beta);
    long long int getNodesAtDepth(board& state, int maxDepth, bool maximizingPlayer);
    std::string result(int eval, int maxDepth);
    void optimalPlay(board& state, int maxDepth, bool maximizingPlayer, bool alpha_beta, int total_moves);
    bool isDepthLimitReached() { return depth_limit_reached; };
    void clearall() { checkDraw.clear(); depth_limit_reached = false; depth_limit = 0; };
    
    std::unordered_map<std::string, int> checkDraw;
    move_gen mg;
    bool depth_limit_reached = false;
    int depth_limit = 0;
};

#endif // MINMAX_H