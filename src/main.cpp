#include <iostream>
#include "engine.cpp"

using namespace chess;

int main()
{
    // Board board = Board("7k/5KQ1/8/8/8/8/8/8 b - - 0 1");
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // std::cout << eval(board) << std::endl;
    // Movelist moves = getMoves(board);
    
    std::cout << perft(board, 1) << std::endl;
    
    return 0;
}