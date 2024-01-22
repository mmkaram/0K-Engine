#include <iostream>
#include <string>
#include "chessPiece.h"

class Board
{
private:
    // size of each one of the sides
    // 8x8 = 64 squares
    static const int SIZE = 8;
    Piece *board[SIZE][SIZE];

public:
    // Constructor that sets all the pointers to nullptr
    // TODO: Import FEN and set the board accordingly
    Board()
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                board[i][j] = nullptr;
            }
        }
        board[0][0] = new Piece(COLOR::WHITE, TYPE::KING);
    }
    Board(std::string FEN)
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                board[i][j] = nullptr;
            }
        }
    }
    // Destructor that deletes all the pointers
    ~Board()
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                delete board[i][j];
                board[i][j] = nullptr; // It's a good practice to set the pointer to nullptr after deleting
            }
        }
    }
    // return a string of all the board
    // Capital letters for white pieces
    // Lowercase letters for black pieces
    // Empty squares are represented by a dash
    std::string toString()
    {
        std::string result = "";
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                if (board[i][j] == nullptr)
                {
                    result += "-";
                }
                else
                {
                    if (board[i][j]->getSide() == COLOR::WHITE)
                    {
                        switch (board[i][j]->getType())
                        {
                        case TYPE::PAWN:
                            result += "P";
                            break;
                        case TYPE::KNIGHT:
                            result += "N";
                            break;
                        case TYPE::BISHOP:
                            result += "B";
                            break;
                        case TYPE::ROOK:
                            result += "R";
                            break;
                        case TYPE::QUEEN:
                            result += "Q";
                            break;
                        case TYPE::KING:
                            result += "K";
                            break;
                        }
                    }
                    else if (board[i][j]->getSide() == COLOR::BLACK)
                    {
                        switch (board[i][j]->getType())
                        {
                        case TYPE::PAWN:
                            result += "p";
                            break;
                        case TYPE::KNIGHT:
                            result += "n";
                            break;
                        case TYPE::BISHOP:
                            result += "b";
                            break;
                        case TYPE::ROOK:
                            result += "r";
                            break;
                        case TYPE::QUEEN:
                            result += "q";
                            break;
                        case TYPE::KING:
                            result += "k";
                            break;
                        }
                    }
                }
                result += " ";
            }
            result += "\n";
        }
        return result;
    }
};
