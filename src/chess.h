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

    std::map<int, std::vector<int>> getPseudoLegalMoves()
    {
        std::map<int, std::vector<int>> getLegalMoves;
        // get some popcorn and get comfortable, this is gonna be a long one
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
                // multiply by 1 if white, -1 if black
                int direction = (turn == Color::WHITE) ? 1 : -1;
                // TODO: Check for en passant
                // TODO: Check for promotion
                // Check if the pawn can move forward for white
                if (board.getSquare(i + pawnMap[0] * direction).getType() == PieceType::NONE)
                {
                    getLegalMoves[i].push_back(i + pawnMap[0] * direction);
                    if ( (turn == Color::WHITE && i > 7 && i < 16) && (board.getSquare(i + pawnMap[0] * direction * 2).getType() == PieceType::NONE))
                    {
                        getLegalMoves[i].push_back(i + (pawnMap[0] * direction * 2));
                    }
                    else if ( (turn == Color::BLACK && i < 56 && i > 47) && (board.getSquare(i + pawnMap[0] * direction * 2).getType() == PieceType::NONE))
                    {
                        getLegalMoves[i].push_back(i + (pawnMap[0] * direction * 2));
                    }
                }
                // Check if the pawn can move diagonally
                if (board.getSquare((i + (pawnMap[0] * direction)) + 1).getColor() != turn && board.getSquare((i + (pawnMap[0] * direction)) + 1).getType() != PieceType::NONE)
                {
                    getLegalMoves[i].push_back((i + (pawnMap[0] * direction)) + 1);
                }
                if (board.getSquare((i + (pawnMap[0] * direction)) - 1).getColor() != turn && board.getSquare((i + (pawnMap[0] * direction)) - 1).getType() != PieceType::NONE)
                {
                    getLegalMoves[i].push_back((i + (pawnMap[0] * direction)) - 1);
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
                bool up = true;
                bool down = true;
                bool left = true;
                bool right = true;

                for (int j = 0; j < 8; j++)
                {

                    if (i + upMap[j] >= 0 && i + upMap[j] <= 63 && up)
                    {
                        // if enemy piece is found, add it to the vector and stop checking in that direction
                        if (board.getSquare(i + upMap[j]).getColor() != turn && board.getSquare(i + upMap[j]).getType() != PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + upMap[j]);
                            up = false;
                            // if no enemy piece is found, add it to the vector
                        }
                        else if (board.getSquare(i + upMap[j]).getType() == PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + upMap[j]);
                        }
                        // if the piece is the same color, stop checking in that direction
                        else if (board.getSquare(i + upMap[j]).getColor() == turn)
                        {
                            up = false;
                        }
                    }
                    //

                    if (i + downMap[j] >= 0 && i + downMap[j] <= 63 && down)
                    {
                        // if enemy piece is found, add it to the vector and stop checking in that direction
                        if (board.getSquare(i + downMap[j]).getColor() != turn && board.getSquare(i + downMap[j]).getType() != PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + downMap[j]);
                            down = false;
                            // if no enemy piece is found, add it to the vector
                        }
                        else if (board.getSquare(i + downMap[j]).getType() == PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + downMap[j]);
                        }
                        // if the piece is the same color, stop checking in that direction
                        else if (board.getSquare(i + downMap[j]).getColor() == turn)
                        {
                            down = false;
                        }
                    }

                    //
                    if (i + leftMap[j] >= 0 && i + leftMap[j] <= 63 && left)
                    {
                        // if enemy piece is found, add it to the vector and stop checking in that direction
                        if (board.getSquare(i + leftMap[j]).getColor() != turn && board.getSquare(i + leftMap[j]).getType() != PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + leftMap[j]);
                            left = false;
                            // if no enemy piece is found, add it to the vector
                        }
                        else if (board.getSquare(i + leftMap[j]).getType() == PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + leftMap[j]);
                        }
                        // if the piece is the same color, stop checking in that direction
                        else if (board.getSquare(i + leftMap[j]).getColor() == turn)
                        {
                            left = false;
                        }
                    }

                    //
                    if (i + rightMap[j] >= 0 && i + rightMap[j] <= 63 && right)
                    {
                        // if enemy piece is found, add it to the vector and stop checking in that direction
                        if (board.getSquare(i + rightMap[j]).getColor() != turn && board.getSquare(i + rightMap[j]).getType() != PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + rightMap[j]);
                            right = false;
                            // if no enemy piece is found, add it to the vector
                        }
                        else if (board.getSquare(i + rightMap[j]).getType() == PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + rightMap[j]);
                        }
                        // if the piece is the same color, stop checking in that direction
                        else if (board.getSquare(i + rightMap[j]).getColor() == turn)
                        {
                            right = false;
                        }
                    }
                }
            }
            // Bishop moves
            if (board.getSquare(i).getType() == PieceType::BISHOP || board.getSquare(i).getType() == PieceType::QUEEN)
            {
                bool upLeft = true;
                bool downLeft = true;
                bool upRight = true;
                bool downRight = true;

                for (int j = 0; j < 8; j++)
                {

                    //
                    if (i + upLeftMap[j] >= 0 && i + upLeftMap[j] <= 63 && upLeft)
                    {
                        if (board.getSquare(i + upLeftMap[j]).getColor() != turn && board.getSquare(i + upLeftMap[j]).getType() != PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + upLeftMap[j]);
                            upLeft = false;
                        }
                        else if (board.getSquare(i + upLeftMap[j]).getType() == PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + upLeftMap[j]);
                        }
                        else if (board.getSquare(i + upLeftMap[j]).getColor() == turn)
                        {
                            upLeft = false;
                        }
                    }

                    //
                    if (i + downLeftMap[j] >= 0 && i + downLeftMap[j] <= 63 && downLeft)
                    {
                        if (board.getSquare(i + downLeftMap[j]).getColor() != turn && board.getSquare(i + downLeftMap[j]).getType() != PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + downLeftMap[j]);
                            downLeft = false;
                        }
                        else if (board.getSquare(i + downLeftMap[j]).getType() == PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + downLeftMap[j]);
                        }
                        else if (board.getSquare(i + downLeftMap[j]).getColor() == turn)
                        {
                            downLeft = false;
                        }
                    }

                    //
                    if (i + upRightMap[j] >= 0 && i + upRightMap[j] <= 63 && upRight)
                    {
                        if (board.getSquare(i + upRightMap[j]).getColor() != turn && board.getSquare(i + upRightMap[j]).getType() != PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + upRightMap[j]);
                            upRight = false;
                        }
                        else if (board.getSquare(i + upRightMap[j]).getType() == PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + upRightMap[j]);
                        }
                        else if (board.getSquare(i + upRightMap[j]).getColor() == turn)
                        {
                            upRight = false;
                        }
                    }

                    //
                    if (i + downRightMap[j] >= 0 && i + downRightMap[j] <= 63 && downRight)
                    {
                        if (board.getSquare(i + downRightMap[j]).getColor() != turn && board.getSquare(i + downRightMap[j]).getType() != PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + downRightMap[j]);
                            downRight = false;
                        }
                        else if (board.getSquare(i + downRightMap[j]).getType() == PieceType::NONE)
                        {
                            getLegalMoves[i].push_back(i + downRightMap[j]);
                        }
                        else if (board.getSquare(i + downRightMap[j]).getColor() == turn)
                        {
                            downRight = false;
                        }
                    }
                }

                // King moves
                if (board.getSquare(i).getType() == PieceType::KING)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        if (i + kingMap[j] >= 0 && i + kingMap[j] <= 63)
                        {
                            if (board.getSquare(i + kingMap[j]).getColor() != turn)
                            {
                                getLegalMoves[i].push_back(i + kingMap[j]);
                            }
                        }
                    }
                }
            }
        }
        printMap(getLegalMoves);
        return getLegalMoves;
    }

    std::map<int, std::vector<int>> getLegalMoves()
    {
        // this function extends the getPseudoLegalMoves function by removing moves that would put the king in check
        std::map<int, std::vector<int>> getLegalMoves = getPseudoLegalMoves();

        // TODO: Check for checks
        
        return getLegalMoves;
    }

    void printMap(const std::map<int, std::vector<int>> &m)
    {
        for (const auto &pair : m)
        {
            std::cout << "Key: " << pair.first << " Values: ";
            for (const auto &val : pair.second)
            {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
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