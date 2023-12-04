#ifndef MINMAX_H
#define MINMAX_H

#include <utility> // std::pair
#include <unordered_map> // std::unordered_map
#include "board.h"
#include "move_gen.h"

// Generic MinMax algorithm with various optimizations
class MinMax {
public:
    MinMax(move_gen& mg) : mg(mg) {};
    int minmaxSimple(board& state, int depth, bool maximizingPlayer);
    int minmaxAlphaBeta(board& state, int depth, bool maximizingPlayer, int alpha, int beta);
    std::pair<bool, std::pair<int, board::move>> findBestMove(board& state, int depth, bool maximizingPlayer);
    std::unordered_map<std::string, int> checkDraw;
    move_gen mg;
    bool depth_limit_reached = false;
};

#endif // MINMAX_H