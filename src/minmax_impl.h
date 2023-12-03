#ifndef MINMAX_IMPL_H
#define MINMAX_IMPL_H

#include "minmax.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>

// ToDo:
// Add Transposition Table

// Generic MinMax algorithm implementation
int MinMax::minmaxSimple(board& state, int depth, bool maximizingPlayer) {
    checkDraw[state.to_fen()]++;

    if (depth == 0 ||  checkDraw[state.to_fen()]>1 || mg.all_legal_moves().size() == 0)
        return mg.evaluate();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();

        for (board::move move : mg.all_legal_moves()) {
            state.move_piece(move);
            mg.change_turn();
            int eval = minmaxSimple(state, depth - 1, false);
            state.undo_move(move);
            mg.change_turn();
            maxEval = std::max(maxEval, eval);
        }
        checkDraw[state.to_fen()]--;
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();

        for (board::move move : mg.all_legal_moves()) {
            state.move_piece(move);
            mg.change_turn();
            int eval = minmaxSimple(state, depth - 1, true);
            state.undo_move(move);
            mg.change_turn();
            minEval = std::min(minEval, eval);
        }
        checkDraw[state.to_fen()]--;
        return minEval;
    }
}

// Generic MinMax algorithm implementation with alpha-beta pruning
int MinMax::minmaxAlphaBeta(board& state, int depth, bool maximizingPlayer, int alpha, int beta) {
    std::cout<<state.to_fen()<<std::endl;
    std::cout<<mg.all_legal_moves().size()<<std::endl;
    checkDraw[state.to_fen()]++;

    if (depth == 0 || checkDraw[state.to_fen()]>1 || mg.all_legal_moves().size() == 0)
        return mg.evaluate();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();

        for (board::move move : mg.all_legal_moves()) {
            state.move_piece(move);
            mg.change_turn();
            int eval = minmaxAlphaBeta(state, depth - 1, false, alpha, beta);
            state.undo_move(move);
            mg.change_turn();
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        checkDraw[state.to_fen()]--;
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();

        for (board::move move : mg.all_legal_moves()) {
            state.move_piece(move);
            mg.change_turn();
            int eval = minmaxAlphaBeta(state, depth - 1, true, alpha, beta);
            state.undo_move(move);
            mg.change_turn();
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if (beta <= alpha)
                break;
        }
        checkDraw[state.to_fen()]--;
        return minEval;
    }
}

// Generic MinMax with alpha-beta pruning to find best move 
std::pair<int, board::move> MinMax::findBestMove(board& state, int depth, bool maximizingPlayer) {
    std::vector<board::move> legalMoves = mg.all_legal_moves();
    std::pair<int, board::move> bestMove;

    if (maximizingPlayer){
        bestMove = std::make_pair(std::numeric_limits<int>::min(), legalMoves[0]);

        for (board::move move : legalMoves){
            state.move_piece(move);
            mg.change_turn();
            int eval = minmaxAlphaBeta(state, depth - 1, !maximizingPlayer, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            state.undo_move(move);
            mg.change_turn();
            if (eval > bestMove.first) {
                bestMove.first = eval;
                bestMove.second = move;
            }
        }
    }
    else {
        bestMove = std::make_pair(std::numeric_limits<int>::max(), legalMoves[0]);

        for (board::move move : legalMoves){
            state.move_piece(move);
            mg.change_turn();
            int eval = minmaxAlphaBeta(state, depth - 1, !maximizingPlayer, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            state.undo_move(move);
            mg.change_turn();
            if (eval < bestMove.first) {
                bestMove.first = eval;
                bestMove.second = move;
            }
        }
    }

    return bestMove;
}

#endif // MINMAX_IMPL_H