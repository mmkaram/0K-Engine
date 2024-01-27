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
    // std::cout << "Moves found: " << moves.size() << std::endl;
    return moves;
}
// TODO: implement a tree of moves x levels deep
uint64_t perft(Board& board, int depth) {
    Movelist moves;
    movegen::legalmoves(moves, board);

    if (depth == 1) {
        return moves.size();
    }

    uint64_t nodes = 0;

    for (int i = 0; i < moves.size(); i++) {
        const auto move = moves[i];
        board.makeMove(move);
        nodes += perft(board, depth - 1);
        board.unmakeMove(move);
    }

    return nodes;
}

// @brief evaluate the board position
int eval(Board board)
{
    return 0;
}
