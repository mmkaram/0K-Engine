#include <iostream>
#include "lib/chess.hpp"
#include "lib/positionValues.hpp"

using namespace chess;

// define piece values in centipawns
const int pawnValue = 100;
const int knightValue = 300;
const int bishopValue = 300;
const int rookValue = 500;
const int queenValue = 900;
const int kingValue = 1000000000;

struct Node
{
    Move move;
    std::vector<Node> children;
};

// @brief evaluate the board position
// TODO: Implement NNUE
int eval(Board board)
{
    int eval = 0;

    auto occ = board.occ();

    while (occ)
    {
        const auto pos = occ.pop();
        const auto piece = board.at(pos);

        switch (piece)
        {
        case 0:
            eval += pawnValue + whitePawn[pos];
            break;
        case 1:
            eval += knightValue + knight[pos];
            break;
        case 2:
            eval += bishopValue + bishop[pos];
            break;
        case 3:
            eval += rookValue + rook[pos];
            break;
        case 4:
            eval += queenValue;
            break;
        case 5:
            eval += kingValue + whiteKing[pos];
            break;
        case 6:
            eval -= pawnValue - blackPawn[pos];
            break;
        case 7:
            eval -= knightValue - knight[pos];
            break;
        case 8:
            eval -= bishopValue - bishop[pos];
            break;
        case 9:
            eval -= rookValue - rook[pos];
            break;
        case 10:
            eval -= queenValue;
            break;
        case 11:
            eval -= kingValue - blackKing[pos];
            break;
        }
    }
    return eval;
}

uint64_t perft(Board &board, int depth)
{
    // taken from the chess-engine docs
    Movelist moves;
    movegen::legalmoves(moves, board);

    if (depth == 1)
    {
        return moves.size();
    }

    uint64_t nodes = 0;

    for (int i = 0; i < moves.size(); i++)
    {
        auto move = moves[i];
        board.makeMove(move);
        // move.setScore(eval(board));

        nodes += perft(board, depth - 1);
        board.unmakeMove(move);
    }

    return nodes;
}

int qsearch(Board &board, int alpha, int beta)
{
    int stand_pat = eval(board);
    if (stand_pat >= beta)
        return beta;
    if (alpha < stand_pat)
        alpha = stand_pat;

    Movelist captures;
    movegen::legalmoves<movegen::MoveGenType::CAPTURE>(captures, board);

    for (auto move : captures)
    {
        board.makeMove(move);
        int score = -qsearch(board, -beta, -alpha);
        board.unmakeMove(move);

        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;
    }
    return alpha;
}

Move alphaBetaTwo(Board &board, int depth, bool isMaximizingPlayer, int alpha, int beta)
{
    // TODO:
    // - implement negamax
    // - search all captures even if the depth reaches 0
    // - order moves by high value captures, pawn promotions, checks, etc.
    // - implement transposition tables
    // - dynamic depth/iterative deepening (going through the tree once, stroing the best move
    //  and then going through the tree again with a higher depth)
    // - Multithreading
    
    // init movelist
    Movelist moves;
    movegen::legalmoves(moves, board);

    Move bestMove;
    int bestScore = isMaximizingPlayer ? -std::numeric_limits<int>::max() : std::numeric_limits<int>::max();

    // for each move in the movelist
    for (int i = 0; i < moves.size(); i++)
    {
        // make the move and evaluate the board
        auto move = moves[i];
        board.makeMove(move);
        move.setScore(eval(board));

        // if the depth is greater than 1, call alphaBetaTwo recursively
        if (depth > 1)
        {
            // call alphaBetaTwo recursively
            Move childMove = alphaBetaTwo(board, depth - 1, !isMaximizingPlayer, alpha, beta);
            int childScore = childMove.score();

            // if the child score is better than the best score
            // update the best score and best move
            if (isMaximizingPlayer && childScore > bestScore)
            {
                bestScore = childScore;
                bestMove = move;
                alpha = std::max(alpha, bestScore);
            }
            else if (!isMaximizingPlayer && childScore < bestScore)
            {
                bestScore = childScore;
                bestMove = move;
                beta = std::min(beta, bestScore);
            }
        }
        // if the depth is 0, call qsearch
        else
        {
            int score = qsearch(board, alpha, beta);
            if (isMaximizingPlayer && score > bestScore)
            {
                bestScore = score;
                bestMove = move;
                alpha = std::max(alpha, bestScore);
            }
            else if (!isMaximizingPlayer && score < bestScore)
            {
                bestScore = score;
                bestMove = move;
                beta = std::min(beta, bestScore);
            }
        }

        board.unmakeMove(move);

        if (beta <= alpha)
        {
            break;
        }
    }

    return bestMove;
}