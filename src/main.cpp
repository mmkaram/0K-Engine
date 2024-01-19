#include <iostream>
#include "chess.h"

int main(int argc, char *argv[])
{
    Chess chess;

    std::cout << chess.boardString() << "\n";

    chess.getPseudoLegalMoves(chess.getBoard(), Color::WHITE);

    return 0;
}
