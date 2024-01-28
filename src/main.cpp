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
        // Board endGame = Board("8/8/8/8/8/8/P7/1k1K4 w - - 0 1");
        // Board onePawn = Board("8/6k1/8/8/8/2K5/P7/8 w - - 0 1");
        // Board GMGame = Board("r1bq1rk1/pp2b1pp/n3pp2/1N1p4/P1pP4/2P1PNP1/1P3PP1/R2QKB1R w KQ - 0 14");
        // Board OkGame = Board("r2qkb1r/ppp2ppp/2n1pn2/3pN3/3P1Bb1/4P3/PPP1BPPP/RN1QK2R b KQkq - 1 6");
        std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        stdGame = Board(fen);
    }

    // std::pair<Node, Move> tree = treeGen(stdGame, DEPTH, true);
    int alpha = std::numeric_limits<int>::lowest();
    int beta = std::numeric_limits<int>::max();
    std::pair<Node, Move> tree = alphaBeta(stdGame, DEPTH,
                                           true, alpha, beta);
    std::cout << "best move: " << tree.second << std::endl;

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double seconds = duration.count() / 1e6; // convert microseconds to seconds
    std::cout << "Time to execute: " << seconds << " seconds" << std::endl;

    return 0;
}