#ifndef MINMAX_IMPL_H
#define MINMAX_IMPL_H

#include "minmax.h"
#include <vector>
#include <algorithm>
#include <limits>

// ToDo:
// Add Transposition Table
// Make it Chess specific after everything is done

// Generic MinMax algorithm implementation
template <typename GameState>
int MinMax<GameState>::minmaxSimple(GameState& state, int depth, bool maximizingPlayer) {
    if (depth == 0 || state.isGameOver())
        return state.evaluate();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();

        for (GameState newState : state.generateLegalMoves()) {
            int eval = minmaxSimple(newState, depth - 1, false);
            maxEval = std::max(maxEval, eval);
        }

        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();

        for (GameState newState : state.generateLegalMoves()) {
            int eval = minmaxSimple(newState, depth - 1, true);
            minEval = std::min(minEval, eval);
        }

        return minEval;
    }
}

// Generic MinMax algorithm implementation with alpha-beta pruning
template <typename GameState>
int MinMax<GameState>::minmaxAlphaBeta(GameState& state, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0 || state.isGameOver())
        return state.evaluate();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();

        for (GameState newState : state.generateLegalMoves()) {
            int eval = minmaxAlphaBeta(newState, depth - 1, false, alpha, beta);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }

        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();

        for (GameState newState : state.generateLegalMoves()) {
            int eval = minmaxAlphaBeta(newState, depth - 1, true, alpha, beta);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }

        return minEval;
    }
}

// Generic MinMax with alpha-beta pruning to find best move 
template <typename GameState>
std::pair<int, GameState> MinMax<GameState>::findBestMove(GameState& state, int depth, bool maximizingPlayer) {
    std::vector<GameState> legalMoves = state.generateLegalMoves();
    std::pair<int, GameState> bestMove;

    if (maximizingPlayer){
        bestMove = std::make_pair(std::numeric_limits<int>::min(), legalMoves[0]);

        for (GameState newState : legalMoves){
            int eval = minmaxAlphaBeta(newState, depth - 1, !maximizingPlayer, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            if (eval > bestMove.first) {
                bestMove.first = eval;
                bestMove.second = newState;
            }
        }
    }
    else {
        bestMove = std::make_pair(std::numeric_limits<int>::max(), legalMoves[0]);

        for (GameState newState : legalMoves){
            int eval = minmaxAlphaBeta(newState, depth - 1, !maximizingPlayer, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            if (eval < bestMove.first) {
                bestMove.first = eval;
                bestMove.second = newState;
            }
        }
    }

    return bestMove;
}

#endif // MINMAX_IMPL_H