#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <algorithm>

#include "board.h"

class Chess
{
private:
    Board board = Board();
    Color turn;

    std::array<int, 8> upMap = {8, 16, 24, 32, 40, 48, 56, 64};
    std::array<int, 8> downMap = {-8, -16, -24, -32, -40, -48, -56, -64};
    std::array<int, 8> leftMap = {-1, -2, -3, -4, -5, -6, -7, -8};
    std::array<int, 8> rightMap = {1, 2, 3, 4, 5, 6, 7, 8};

    std::array<int, 8> upLeftMap = {-9, -18, -27, -36, -45, -54, -63, -72};
    std::array<int, 8> upRightMap = {-7, -14, -21, -28, -35, -42, -49, -56};
    std::array<int, 8> downLeftMap = {7, 14, 21, 28, 35, 42, 49, 56};
    std::array<int, 8> downRightMap = {9, 18, 27, 36, 45, 54, 63, 72};

    std::array<int, 8> knightMap = {-17, -15, -10, -6, 6, 10, 15, 17};

    std::array<int, 8> pawnMap = {8};

    std::array<int, 8> kingMap = {-9, -8, -7, -1, 1, 7, 8, 9};

public:
    Chess() : turn(Color::WHITE) {}

    ~Chess() {}

    std::string boardString()
    {
        return board.boardString();
    }

    Color getTurn()
    {
        return turn;
    }

    std::map<int, std::vector<int>> getLegalMoves()
    {
        std::map<int, std::vector<int>> getLegalMoves;
        for (int i = 0; i < 64; i++)
        {
            // Check if there is a piece at the current position
            if (board.getSquare(i).getType() == PieceType::NONE)
            {
                continue;
            }
            // Check if the piece at the current position is of the correct color
            if (board.getSquare(i).getColor() != turn)
            {
                continue;
            }
            if (board.getSquare(i).getType() == PieceType::PAWN)
            {
                // Check if the pawn can move forward
                if (board.getSquare(i + pawnMap[0]).getType() == PieceType::NONE)
                {
                    getLegalMoves[i].push_back(i + pawnMap[0]);
                }
                // Check if the pawn can move diagonally
                if (board.getSquare(i + pawnMap[0] + 1).getColor() != turn && board.getSquare(i + pawnMap[0] + 1).getType() != PieceType::NONE)
                {
                    getLegalMoves[i].push_back(i + pawnMap[0] + 1);
                }
                if (board.getSquare(i + pawnMap[0] - 1).getColor() != turn && board.getSquare(i + pawnMap[0] - 1).getType() != PieceType::NONE)
                {
                    getLegalMoves[i].push_back(i + pawnMap[0] - 1);
                }
            }
            // Knight checking logic
            if (board.getSquare(i).getType() == PieceType::KNIGHT)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board.getSquare(i + knightMap[j]).getColor() != turn)
                    {
                        getLegalMoves[i].push_back(i + knightMap[j]);
                    }
                }
            }
            // Rook checking logic
            if (board.getSquare(i).getType() == PieceType::ROOK || board.getSquare(i).getType() == PieceType::QUEEN)
            {
                for (int j = 0; j < 8; j++)
                {

                    if (i + upMap[j] >= 0 && i + upMap[j] <= 63)
                    {
                        if (board.getSquare(i + upMap[j]).getColor() != turn)
                        {
                            getLegalMoves[i].push_back(i + upMap[j]);
                        }
                    }
                    if (i + downMap[j] >= 0 && i + downMap[j] <= 63)
                    {
                        if (board.getSquare(i + downMap[j]).getColor() != turn)
                        {
                            getLegalMoves[i].push_back(i + downMap[j]);
                        }
                    }
                    if (i + leftMap[j] >= 0 && i + leftMap[j] <= 63)
                    {
                        if (board.getSquare(i + leftMap[j]).getColor() != turn)
                        {
                            getLegalMoves[i].push_back(i + leftMap[j]);
                        }
                    }
                    if (i + rightMap[j] >= 0 && i + rightMap[j] <= 63)
                    {
                        if (board.getSquare(i + rightMap[j]).getColor() != turn)
                        {
                            getLegalMoves[i].push_back(i + rightMap[j]);
                        }
                    }
                }
            }
            // Bishop moves
            if (board.getSquare(i).getType() == PieceType::BISHOP || board.getSquare(i).getType() == PieceType::QUEEN)
            {
                for (int j = 0; j < 8; j++)
                {

                    if (i + upLeftMap[j] >= 0 && i + upLeftMap[j] <= 63)
                    {
                        if (board.getSquare(i + upLeftMap[j]).getColor() != turn)
                        {
                            getLegalMoves[i].push_back(i + upLeftMap[j]);
                        }
                    }
                    if (i + downLeftMap[j] >= 0 && i + downLeftMap[j] <= 63)
                    {
                        if (board.getSquare(i + downLeftMap[j]).getColor() != turn)
                        {
                            getLegalMoves[i].push_back(i + downLeftMap[j]);
                        }
                    }
                    if (i + upRightMap[j] >= 0 && i + upRightMap[j] <= 63)
                    {
                        if (board.getSquare(i + upRightMap[j]).getColor() != turn)
                        {
                            getLegalMoves[i].push_back(i + upRightMap[j]);
                        }
                    }
                    if (i + downRightMap[j] >= 0 && i + downRightMap[j] <= 63)
                    {
                        if (board.getSquare(i + downRightMap[j]).getColor() != turn)
                        {
                            getLegalMoves[i].push_back(i + downRightMap[j]);
                        }
                    }
                }
            }
        }
        return getLegalMoves;
    }

    bool canMovePiece(int currentPos, int newPos)
    {
        std::map<int, std::vector<int>> legalMoves = getLegalMoves();

        if (legalMoves[currentPos].empty())
        {
            return false;
        }
        else if (std::find(legalMoves[currentPos].begin(), legalMoves[currentPos].end(), newPos) == legalMoves[currentPos].end())
        {
            return false;
        }

        return true;
    }
};