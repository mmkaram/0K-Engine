#include "chess.h"
#include <iostream>

int main(int argc, char *argv[])
{
    Chess chess;

    // Testing queen moves
    std::cout << chess.colorToString(chess.getTurn()) << " to move\n";
    std::cout << chess.getBoard();
    chess.move(37, 53);

    // Testing knight moves
    std::cout << chess.colorToString(chess.getTurn()) << " to move\n";
    std::cout << chess.getBoard();
    chess.move(17, 0);

    // Testing rook moves
    std::cout << chess.colorToString(chess.getTurn()) << " to move\n";
    std::cout << chess.getBoard();
    chess.move(63, 55);
    std::cout << chess.numberBoard();
}