#include "chess.h"
#include <iostream>

int main (int argc, char *argv[]) {
    Chess chess;
    // Testing pawn moves
    // std::cout << chess.getBoard();
    // chess.move(8, 16);
    // std::cout << chess.getBoard();
    // chess.move(16, 24);
    // std::cout << chess.getBoard();

    // Testing queen moves
    chess.move(37, 36+7);
    std::cout << chess.getBoard();
    
    // Testing rook moves
    chess.move(0, 7);
    std::cout << chess.getBoard();
}