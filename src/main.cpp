#include <iostream>
#include <chrono>
#include "engine.cpp"

using namespace chess;

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    int const DEPTH = 5; 
    Board endGame = Board("8/8/8/8/8/8/P7/1k1K4 w - - 0 1");
    Board onePawn = Board("8/6k1/8/8/8/2K5/P7/8 w - - 0 1");
    Board stdGame = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Board OkGame = Board("r2qkb1r/ppp2ppp/2n1pn2/3pN3/3P1Bb1/4P3/PPP1BPPP/RN1QK2R b KQkq - 1 6");

    // std::cout << "number of positions analyzed: " << perft(OkGame, 2) << std::endl;
    treeGen(stdGame, DEPTH);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // To get the value of duration use the count()
    // member function on the duration object
    std::cout << "Time to execute: " << duration.count() << " microseconds" << std::endl;

    return 0;
}