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
template <typename GameState, typename Move>
int MinMax<GameState, Move>::minmaxSimple(GameState& state, int depth, bool maximizingPlayer) {
    if (depth == 0 || state.isGameOver())
        return state.evaluate();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();

        for (Move move : state.generateLegalMoves()) {
            state.makeMove(move);
            int eval = minmaxSimple(state, depth - 1, false);
            state.undoMove(move);
            maxEval = std::max(maxEval, eval);
        }

        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();

        for (Move move : state.generateLegalMoves()) {
            state.makeMove(move);
            int eval = minmaxSimple(state, depth - 1, true);
            state.undoMove(move);
            minEval = std::min(minEval, eval);
        }

        return minEval;
    }
}

// Generic MinMax algorithm implementation with alpha-beta pruning
template <typename GameState, typename Move>
int MinMax<GameState, Move>::minmaxAlphaBeta(GameState& state, int depth, bool maximizingPlayer, int alpha, int beta) {
    if (depth == 0 || state.isGameOver())
        return state.evaluate();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();

        for (Move move : state.generateLegalMoves()) {
            state.makeMove(move);
            int eval = minmaxAlphaBeta(state, depth - 1, false, alpha, beta);
            state.undoMove(move);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }

        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();

        for (Move move : state.generateLegalMoves()) {
            state.makeMove(move);
            int eval = minmaxAlphaBeta(state, depth - 1, true, alpha, beta);
            state.undoMove(move);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }

        return minEval;
    }
}

// Generic MinMax with alpha-beta pruning to find best move 
template <typename GameState, typename Move>
std::pair<int, Move> MinMax<GameState, Move>::findBestMove(GameState& state, int depth, bool maximizingPlayer) {
    std::vector<Move> legalMoves = state.generateLegalMoves();
    std::pair<int, Move> bestMove;

    if (maximizingPlayer){
        bestMove = std::make_pair(std::numeric_limits<int>::min(), legalMoves[0]);

        for (Move move : legalMoves){
            state.makeMove(move);
            int eval = minmaxAlphaBeta(state, depth - 1, !maximizingPlayer, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            state.undoMove(move);
            if (eval > bestMove.first) {
                bestMove.first = eval;
                bestMove.second = move;
            }
        }
    }
    else {
        bestMove = std::make_pair(std::numeric_limits<int>::max(), legalMoves[0]);

        for (Move move : legalMoves){
            state.makeMove(move);
            int eval = minmaxAlphaBeta(state, depth - 1, !maximizingPlayer, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            state.undoMove(move);
            if (eval < bestMove.first) {
                bestMove.first = eval;
                bestMove.second = move;
            }
        }
    }

    return bestMove;
}

#endif // MINMAX_IMPL_H