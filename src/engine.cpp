#include <iostream>
#include "lib/chess.hpp"

using namespace chess;

const int DEPTH = 3;

// define piece values in centipawns
const int pawnValue = 100;
const int knightValue = 300;
const int bishopValue = 300;
const int rookValue = 500;
const int queenValue = 900;
const int kingValue = 1000000000;

struct Node {
    Move move;
    std::vector<Node> children;
};

Movelist getMoves(Board board)
{
    Movelist moves;
    Movelist empty;
    movegen::legalmoves(moves, board);

    if (moves.empty())
    {
        std::cout << "No moves found" << std::endl;
        return empty;
    }
    return moves;
}

// @brief evaluate the board position
int16_t eval(Board board)
{
    int score = 0;
    for (int i = 0; i < 64; i++)
    {
        switch (board.at(i))
        {
        case 0:
            score += pawnValue;
            break;
        case 1:
            score += knightValue;
            break;
        case 2:
            score += bishopValue;
            break;
        case 3:
            score += rookValue;
            break;
        case 4:
            score += queenValue;
            break;
        case 5:
            score += kingValue;
            break;
        case 6:
            score -= pawnValue;
            break;
        case 7:
            score -= knightValue;
            break;
        case 8:
            score -= bishopValue;
            break;
        case 9:
            score -= rookValue;
            break;
        case 10:
            score -= queenValue;
            break;
        case 11:
            score -= kingValue;
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


Node treeGen(Board &board, int depth)
{
    Movelist moves;
    movegen::legalmoves(moves, board);

    Node node;

    for (int i = 0; i < moves.size(); i++)
    {
        auto move = moves[i];
        board.makeMove(move);
        move.setScore(eval(board));
        
        if (depth > 1)
        {
            node.children.push_back(treeGen(board, depth - 1));
        }
        
        board.unmakeMove(move);
    }

    return node;
}

Move treeTraverse(Node node)
{
    Move bestMove;
    int bestScore = 0;

    for (int i = 0; i < node.children.size(); i++)
    {
        auto child = node.children[i];
        if (child.move.score() > bestScore)
        {
            bestScore = child.move.score();
            bestMove = child.move;
        }
    }

    return bestMove;
}