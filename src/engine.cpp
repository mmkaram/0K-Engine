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

std::pair<Node, Move> treeGen(Board &board, int depth, bool isMaximizingPlayer)
{
    // init movelist
    Movelist moves;
    movegen::legalmoves(moves, board);

    // init node, best move, and best score
    // (works by either maximizing or minimizing centipawn evaluation)
    Node node;
    Move bestMove;
    int bestScore = isMaximizingPlayer ? -std::numeric_limits<int>::max() : std::numeric_limits<int>::max();

    // Given length of moves, iterate through each move
    for (int i = 0; i < moves.size(); i++)
    {
        // given a move, make it and evaluate the board
        // set move's score to eval
        auto move = moves[i];
        board.makeMove(move);
        move.setScore(eval(board));

        // if depth is one, then we're at the end of the tree
        // TODO: make it so keeps going if there are possible captures
        if (depth > 1)
        {
            auto child = treeGen(board, depth - 1, !isMaximizingPlayer);
            node.children.push_back(child.first);
            int childScore = child.second.score();

            if (isMaximizingPlayer && childScore > bestScore)
            {
                bestScore = childScore;
                bestMove = move;
            }
            else if (!isMaximizingPlayer && childScore < bestScore)
            {
                bestScore = childScore;
                bestMove = move;
            }
        }
        else
        {
            int score = eval(board);
            if (isMaximizingPlayer && score > bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
            else if (!isMaximizingPlayer && score < bestScore)
            {
                bestScore = score;
                bestMove = move;
            }
        }

        board.unmakeMove(move);
    }
    return {node, bestMove};
}

std::pair<Node, Move> alphaBeta(Board &board, int depth, bool isMaximizingPlayer, int alpha, int beta)
{
    Movelist moves;
    movegen::legalmoves(moves, board);

    Node node;
    Move bestMove;
    int bestScore = isMaximizingPlayer ? -std::numeric_limits<int>::max() : std::numeric_limits<int>::max();

    for (int i = 0; i < moves.size(); i++)
    {
        auto move = moves[i];
        board.makeMove(move);
        move.setScore(eval(board));
        
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