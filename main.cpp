#include "chess.h"
#include <iostream>

int main (int argc, char *argv[]) {
    Chess chess;
    // Testing pawn moves
    // std::cout << chess.getBoard();
    // chess.move(8, 16);
    // std::cout << chess.getBoard();
    // chess.move(16, 24);
    std::cout << chess.getBoard();

    // Testing queen moves
    if (chess.move(37, 38)){
        std::cout << "Queen moved successfully\n";
    }
    else {
        std::cout << "Queen move failed\n";
    }
    std::cout << chess.getBoard();
    
    // Testing rook moves
    if (chess.move(63, 57)) {
        std::cout << "Rook moved successfully\n";
    }
    else {
        std::cout << "Rook move failed\n";
    }
    std::cout << chess.getBoard();
}