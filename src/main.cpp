#include <iostream>
#include "chess.h"

int main(int argc, char *argv[])
{
    Chess chess;

    std::cout << chess.boardString() << "\n";
    
    std::cout << chess.canMovePiece(32, 32) << "\n";

    // std::cout << chess.boardString() << "\n";

    return 0;
}