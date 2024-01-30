#include <iostream>
#include <chrono>
#include "engine.cpp"

using namespace chess;

int const DEPTH = 6;

int main(int argc, char *argv[])
{
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

    while (stdGame.isGameOver().first == GameResultReason::NONE)
    {
        // bot moves
        auto start = std::chrono::high_resolution_clock::now();

        // set up the alpha and beta values for the first call to alphaBeta
        int alpha = std::numeric_limits<int>::lowest();
        int beta = std::numeric_limits<int>::max();
        Move move = alphaBetaTwo(stdGame, DEPTH,
                                               true, alpha, beta);
        stdGame.makeMove(move);
        std::cout << "-----------------------" << std::endl;
        std::cout << "best move: " << move << std::endl;
        std::cout << "score: " << move.score() << std::endl;
        std::cout << stdGame.getFen() << std::endl;

        // cound how many seconds it took to run
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        double seconds = duration.count() / 1e6; // convert microseconds to seconds
        std::cout << "Time to execute: " << seconds << " seconds" << std::endl;
        std::cout << "-----------------------" << std::endl;

        // player moves
        std::cout << "Enter move: ";
        std::string moveStr;
        std::cin >> moveStr;
        if (moveStr.empty() || moveStr == "exit" || moveStr == "q" || moveStr == "quit") break;
        // take move string and make it a UCI move
        // also called a "move object"
        Move moveObj = uci::uciToMove(stdGame, moveStr);
        stdGame.makeMove(moveObj);
    }
    return 0;
}