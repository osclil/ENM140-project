#ifndef MINMAX_H
#define MINMAX_H

#include <utility> // std::pair

// Generic MinMax algorithm with various optimizations
template <typename GameState, typename Move>
class MinMax {
public:
    int minmaxSimple(GameState& state, int depth, bool maximizingPlayer);
    int minmaxAlphaBeta(GameState& state, int depth, bool maximizingPlayer, int alpha, int beta);
    std::pair<int, Move> findBestMove(GameState& state, int depth, bool maximizingPlayer);
};

#endif // MINMAX_H
