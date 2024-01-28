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
int16_t eval(Board board)
{
    int score = 0;
    for (int i = 0; i < 64; i++)
    {
        switch (board.at(i))
        {
        case 0:
            score += pawnValue + whitePawn[i];
            break;
        case 1:
            score += knightValue + knight[i];
            break;
        case 2:
            score += bishopValue + bishop[i];
            break;
        case 3:
            score += rookValue + rook[i];
            break;
        case 4:
            score += queenValue;
            break;
        case 5:
            score += kingValue + whiteKing[i];
            break;
        case 6:
            score -= pawnValue - blackPawn[i];
            break;
        case 7:
            score -= knightValue - knight[i];
            break;
        case 8:
            score -= bishopValue - bishop[i];
            break;
        case 9:
            score -= rookValue - rook[i];
            break;
        case 10:
            score -= queenValue;
            break;
        case 11:
            score -= kingValue - blackKing[i];
            break;
        }
    }
    return score;
}

uint64_t perft(Board &board, int depth)
{
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
        move.setScore(eval(board));
        std::cout << "analyzed move: " << move << " and assinged score: " << eval(board) << std::endl;

        nodes += perft(board, depth - 1);
        board.unmakeMove(move);
    }

    return nodes;
}

std::pair<Node, Move> alphaBeta(Board &board, int depth, bool isMaximizingPlayer, int alpha, int beta)
{
    // TODO:
    // - order moves by high value captures, pawn promotions, checks, etc.
    // - search all captures even if the depth reaches 0
    // - implement transposition tables
    // - dynamic depth/iterative deepening (going through the tree once, stroing the best move
    //  and then going through the tree again with a higher depth)

    // init the movelist
    Movelist moves;
    movegen::legalmoves(moves, board);

    // init a node and a bestmove to return
    Node node;
    Move bestMove;
    int bestScore = isMaximizingPlayer ? -std::numeric_limits<int>::max() : std::numeric_limits<int>::max();

    // for every move in the movelist of the current node
    for (int i = 0; i < moves.size(); i++)
    {
        // make the move and evaluate the board
        auto move = moves[i];
        board.makeMove(move);
        move.setScore(eval(board));
        
        // if the depth is greater than 1, recurse
        // if not then just evaluate the board
        if (depth > 1)
        {
            auto child = alphaBeta(board, depth - 1, !isMaximizingPlayer, alpha, beta);
            node.children.push_back(child.first);
            int childScore = child.second.score();

            if (isMaximizingPlayer)
            {
                if (childScore > bestScore)
                {
                    bestScore = childScore;
                    bestMove = move;
                }
                alpha = std::max(alpha, bestScore);
            }
            else
            {
                if (childScore < bestScore)
                {
                    bestScore = childScore;
                    bestMove = move;
                }
                beta = std::min(beta, bestScore);
            }
        }
        else
        {
            int score = eval(board);
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

        // Alpha Beta Pruning
        if (beta <= alpha)
        {
            break;
        }
    }
    return {node, bestMove};
}