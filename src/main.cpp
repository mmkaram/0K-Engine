#include <iostream>
#include <chrono>
#include "engine.cpp"

using namespace chess;

int const DEPTH = 5;

int main(int argc, char *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    Board stdGame;

    if (argc > 1)
    {
        // If a FEN string was provided as an argument, use it to set up the board
        std::string fen = argv[1];
        stdGame = Board(fen);
    }
    else
    {
        // Otherwise, use the standard starting position
        std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        stdGame = Board(fen);
    }

    // set up the alpha and beta values for the first call to alphaBeta
    int alpha = std::numeric_limits<int>::lowest();
    int beta = std::numeric_limits<int>::max();
    std::pair<Node, Move> tree = alphaBeta(stdGame, DEPTH,
                                           true, alpha, beta);
    std::cout << "best move: " << tree.second << std::endl;

    // cound how many seconds it took to run
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double seconds = duration.count() / 1e6; // convert microseconds to seconds
    std::cout << "Time to execute: " << seconds << " seconds" << std::endl;

    return 0;
}