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

    if (depth == 0)
        depth_limit_reached = true;

    if (depth == 0 ||  checkDraw[state.to_fen()]>1 || mg.all_legal_moves().size() == 0)
        return mg.evaluate();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();

        for (board::move move : mg.all_legal_moves()) {
            piece p = state.move_piece(move);
            mg.change_turn();
            int eval = minmaxSimple(state, depth - 1, false);
            state.undo_move(move, p);
            mg.change_turn();
            maxEval = std::max(maxEval, eval);
        }
        checkDraw[state.to_fen()]--;
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();

        for (board::move move : mg.all_legal_moves()) {
            piece p = state.move_piece(move);
            mg.change_turn();
            int eval = minmaxSimple(state, depth - 1, true);
            state.undo_move(move, p);
            mg.change_turn();
            minEval = std::min(minEval, eval);
        }
        checkDraw[state.to_fen()]--;
        return minEval;
    }
}

// Generic MinMax algorithm implementation with alpha-beta pruning
int MinMax::minmaxAlphaBeta(board& state, int depth, bool maximizingPlayer, int alpha, int beta) {
    // std::cout << state.to_fen() << " " << depth << std::endl;
    checkDraw[state.to_fen()]++;

    if (depth == 0)
        depth_limit_reached = true;

    if (depth == 0 || checkDraw[state.to_fen()]>1 || mg.all_legal_moves().size() == 0)
        return mg.evaluate();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();

        for (board::move move : mg.all_legal_moves()) {
            piece p = state.move_piece(move);
            mg.change_turn();
            int eval = minmaxAlphaBeta(state, depth - 1, false, alpha, beta);
            state.undo_move(move, p);
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
            piece p = state.move_piece(move);
            mg.change_turn();
            int eval = minmaxAlphaBeta(state, depth - 1, true, alpha, beta);
            state.undo_move(move, p);
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
std::pair<bool, std::pair<int, board::move>> MinMax::findBestMove(board& state, int depth, bool maximizingPlayer, bool alpha_beta) {
    checkDraw[state.to_fen()]++;
    mg.m_whites_turn = maximizingPlayer;

    if (depth == 0)
        depth_limit_reached = true;

    if (depth == 0 || checkDraw[state.to_fen()]>1 || mg.all_legal_moves().size() == 0)
        return {false, std::make_pair(mg.evaluate(), board::move())};

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        board::move bestMove;

        for (board::move move : mg.all_legal_moves()) {
            piece p = state.move_piece(move);
            mg.change_turn();
            int eval;
            if (alpha_beta)
                eval = minmaxAlphaBeta(state, depth - 1, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            else 
                eval = minmaxSimple(state, depth - 1, false);
            state.undo_move(move, p);
            mg.change_turn();
            if (eval > maxEval) {
                maxEval = eval;
                bestMove = move;
            }
        }

        return {true, std::make_pair(maxEval, bestMove)};
    }
    else {
        int minEval = std::numeric_limits<int>::max();
        board::move bestMove;

        for (board::move move : mg.all_legal_moves()) {
            piece p = state.move_piece(move);
            mg.change_turn();
            int eval;
            if (alpha_beta)
                eval = minmaxAlphaBeta(state, depth - 1, true, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
            else 
                eval = minmaxSimple(state, depth - 1, true);
            state.undo_move(move, p);
            mg.change_turn();
            if (eval < minEval) {
                minEval = eval;
                bestMove = move;
            }
        }
        
        return {true, std::make_pair(minEval, bestMove)};
    }
}

// Compare pruning with and without alpha-beta pruning
std::pair<std::chrono::duration<double>, std::chrono::duration<double>> MinMax::comparePruning(board& state, int depth, bool maximizingPlayer) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    minmaxSimple(state, depth, maximizingPlayer);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // std::cout << "Time without pruning = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    std::chrono::steady_clock::time_point begin2 = std::chrono::steady_clock::now();
    minmaxAlphaBeta(state, depth, maximizingPlayer, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    std::chrono::steady_clock::time_point end2 = std::chrono::steady_clock::now();
    // std::cout << "Time by pruning = " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - begin2).count() << "[ms]" << std::endl;

    return std::make_pair((end - begin), (end2 - begin2));
}

// Get number of nodes at a given depth
long long int MinMax::getNodesAtDepth(board& state, int depth, bool maximizingPlayer) {
    checkDraw[state.to_fen()]++;
    mg.m_whites_turn = maximizingPlayer;

    if (depth == 0){
        depth_limit_reached = true;
        return 1;
    }

    if (checkDraw[state.to_fen()]>1 || mg.all_legal_moves().size() == 0)
        return 0;

    long long int nodes = 0;

    if (maximizingPlayer) {
        for (board::move move : mg.all_legal_moves()) {
            piece p = state.move_piece(move);
            mg.change_turn();
            nodes += getNodesAtDepth(state, depth - 1, false);
            state.undo_move(move, p);
            mg.change_turn();
        }
    }
    else {
        for (board::move move : mg.all_legal_moves()) {
            piece p = state.move_piece(move);
            mg.change_turn();
            nodes += getNodesAtDepth(state, depth - 1, true);
            state.undo_move(move, p);
            mg.change_turn();
        }
    }

    return nodes;
}

#endif // MINMAX_IMPL_H