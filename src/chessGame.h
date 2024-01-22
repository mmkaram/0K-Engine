#include <string>

#include "chessBoard.h"

class Chess
{
private:
    Board *board;

public:
    Chess()
    {
        board = new Board();
    }
    Chess(std::string FEN)
    {
        board = new Board(FEN);
    }
    ~Chess()
    {
        delete board;
        board = nullptr;
    }
    std::string getBoard()
    {
        return board->toString();
    }
    getMoves()
    {
        return generateMoves(this->board, COLOR::WHITE);
    }
};