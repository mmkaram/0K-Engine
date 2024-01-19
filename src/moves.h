#include <map>
#include <vector>
#include "board.h"

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

std::map<int, std::vector<int>> getLegalMoves;

std::map<int, std::vector<int>> pawnMoves(Board operateBoard, Color operateTurn, int position)
{
    if (operateBoard.getSquare(position).getType() == PieceType::PAWN)
    {
        // multiply by 1 if white, -1 if black
        int direction = (operateTurn == Color::WHITE) ? 1 : -1;
        // TODO: Check for en passant
        // TODO: Check for promotion
        // Check if the pawn can move forward for white

        if (operateBoard.getSquare(position + pawnMap[0] * direction).getType() ==
            PieceType::NONE)
        {
            getLegalMoves[position].push_back(position + pawnMap[0] * direction);
            if ((operateTurn == Color::WHITE && position > 7 && position < 16) &&
                (operateBoard.getSquare(position + pawnMap[0] * direction * 2)
                     .getType() == PieceType::NONE))
            {
                getLegalMoves[position].push_back(position + (pawnMap[0] * direction * 2));
            }
            else if ((operateTurn == Color::BLACK && position < 56 && position > 47) &&
                     (operateBoard.getSquare(position + pawnMap[0] * direction * 2)
                          .getType() == PieceType::NONE))
            {
                getLegalMoves[position].push_back(position + (pawnMap[0] * direction * 2));
            }
        }

        // Check if the pawn can move diagonally
        if (operateBoard.getSquare((position + (pawnMap[0] * direction)) + 1)
                    .getColor() != operateTurn &&
            operateBoard.getSquare((position + (pawnMap[0] * direction)) + 1)
                    .getType() != PieceType::NONE)
        {
            getLegalMoves[position].push_back((position + (pawnMap[0] * direction)) + 1);
        }
        if (operateBoard.getSquare((position + (pawnMap[0] * direction)) - 1)
                    .getColor() != operateTurn &&
            operateBoard.getSquare((position + (pawnMap[0] * direction)) - 1)
                    .getType() != PieceType::NONE)
        {
            getLegalMoves[position].push_back((position + (pawnMap[0] * direction)) - 1);
        }
    }
    return getLegalMoves;
}
std::map<int, std::vector<int>> knightMoves(Board operateBoard, Color operateTurn, int position)
{
    // Knight checking logic
    if (operateBoard.getSquare(position).getType() == PieceType::KNIGHT)
    {
        for (int j = 0; j < 8; j++)
        {
            if (operateBoard.getSquare(position + knightMap[j]).getColor() !=
                operateTurn)
            {
                getLegalMoves[position].push_back(position + knightMap[j]);
            }
        }
    }
    return getLegalMoves;
}
std::map<int, std::vector<int>> rookMoves(Board operateBoard, Color operateTurn, int position)
{
    // Rook checking logic
    if (operateBoard.getSquare(position).getType() == PieceType::ROOK)
    {
        bool up = true;
        bool down = true;
        bool left = true;
        bool right = true;

        for (int j = 0; j < 8; j++)
        {

            if (position + upMap[j] >= 0 && position + upMap[j] <= 63 && up)
            {
                // if enemy piece is found, add it to the vector and stop checking
                // in that direction
                if (operateBoard.getSquare(position + upMap[j]).getColor() !=
                        operateTurn &&
                    operateBoard.getSquare(position + upMap[j]).getType() !=
                        PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + upMap[j]);
                    up = false;
                    // if no enemy piece is found, add it to the vector
                }
                else if (operateBoard.getSquare(position + upMap[j]).getType() ==
                         PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + upMap[j]);
                }
                // if the piece is the same color, stop checking in that direction
                else if (operateBoard.getSquare(position + upMap[j]).getColor() ==
                         operateTurn)
                {
                    up = false;
                }
            }
            //

            if (position + downMap[j] >= 0 && position + downMap[j] <= 63 && down)
            {
                // if enemy piece is found, add it to the vector and stop checking
                // in that direction
                if (operateBoard.getSquare(position + downMap[j]).getColor() !=
                        operateTurn &&
                    operateBoard.getSquare(position + downMap[j]).getType() !=
                        PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + downMap[j]);
                    down = false;
                    // if no enemy piece is found, add it to the vector
                }
                else if (operateBoard.getSquare(position + downMap[j]).getType() ==
                         PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + downMap[j]);
                }
                // if the piece is the same color, stop checking in that direction
                else if (operateBoard.getSquare(position + downMap[j]).getColor() ==
                         operateTurn)
                {
                    down = false;
                }
            }

            //
            if (position + leftMap[j] >= 0 && position + leftMap[j] <= 63 && left)
            {
                // if enemy piece is found, add it to the vector and stop checking
                // in that direction
                if (operateBoard.getSquare(position + leftMap[j]).getColor() !=
                        operateTurn &&
                    operateBoard.getSquare(position + leftMap[j]).getType() !=
                        PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + leftMap[j]);
                    left = false;
                    // if no enemy piece is found, add it to the vector
                }
                else if (operateBoard.getSquare(position + leftMap[j]).getType() ==
                         PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + leftMap[j]);
                }
                // if the piece is the same color, stop checking in that direction
                else if (operateBoard.getSquare(position + leftMap[j]).getColor() ==
                         operateTurn)
                {
                    left = false;
                }
            }

            //
            if (position + rightMap[j] >= 0 && position + rightMap[j] <= 63 && right)
            {
                // if enemy piece is found, add it to the vector and stop checking
                // in that direction
                if (operateBoard.getSquare(position + rightMap[j]).getColor() !=
                        operateTurn &&
                    operateBoard.getSquare(position + rightMap[j]).getType() !=
                        PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + rightMap[j]);
                    right = false;
                    // if no enemy piece is found, add it to the vector
                }
                else if (operateBoard.getSquare(position + rightMap[j]).getType() ==
                         PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + rightMap[j]);
                }
                // if the piece is the same color, stop checking in that direction
                else if (operateBoard.getSquare(position + rightMap[j]).getColor() ==
                         operateTurn)
                {
                    right = false;
                }
            }
        }
    }
    return getLegalMoves;
}
std::map<int, std::vector<int>> bishopMoves(Board operateBoard, Color operateTurn, int position)
{
    // Bishop moves
    if (operateBoard.getSquare(position).getType() == PieceType::BISHOP ||
        operateBoard.getSquare(position).getType() == PieceType::QUEEN)
    {
        bool upLeft = true;
        bool downLeft = true;
        bool upRight = true;
        bool downRight = true;

        for (int j = 0; j < 8; j++)
        {

            //
            if (position + upLeftMap[j] >= 0 && position + upLeftMap[j] <= 63 && upLeft)
            {
                if (operateBoard.getSquare(position + upLeftMap[j]).getColor() !=
                        operateTurn &&
                    operateBoard.getSquare(position + upLeftMap[j]).getType() !=
                        PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + upLeftMap[j]);
                    upLeft = false;
                }
                else if (operateBoard.getSquare(position + upLeftMap[j]).getType() ==
                         PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + upLeftMap[j]);
                }
                else if (operateBoard.getSquare(position + upLeftMap[j]).getColor() ==
                         operateTurn)
                {
                    upLeft = false;
                }
            }

            //
            if (position + downLeftMap[j] >= 0 && position + downLeftMap[j] <= 63 && downLeft)
            {
                if (operateBoard.getSquare(position + downLeftMap[j]).getColor() !=
                        operateTurn &&
                    operateBoard.getSquare(position + downLeftMap[j]).getType() !=
                        PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + downLeftMap[j]);
                    downLeft = false;
                }
                else if (operateBoard.getSquare(position + downLeftMap[j]).getType() ==
                         PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + downLeftMap[j]);
                }
                else if (operateBoard.getSquare(position + downLeftMap[j]).getColor() ==
                         operateTurn)
                {
                    downLeft = false;
                }
            }

            //
            if (position + upRightMap[j] >= 0 && position + upRightMap[j] <= 63 && upRight)
            {
                if (operateBoard.getSquare(position + upRightMap[j]).getColor() !=
                        operateTurn &&
                    operateBoard.getSquare(position + upRightMap[j]).getType() !=
                        PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + upRightMap[j]);
                    upRight = false;
                }
                else if (operateBoard.getSquare(position + upRightMap[j]).getType() ==
                         PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + upRightMap[j]);
                }
                else if (operateBoard.getSquare(position + upRightMap[j]).getColor() ==
                         operateTurn)
                {
                    upRight = false;
                }
            }

            //
            if (position + downRightMap[j] >= 0 && position + downRightMap[j] <= 63 &&
                downRight)
            {
                if (operateBoard.getSquare(position + downRightMap[j]).getColor() !=
                        operateTurn &&
                    operateBoard.getSquare(position + downRightMap[j]).getType() !=
                        PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + downRightMap[j]);
                    downRight = false;
                }
                else if (operateBoard.getSquare(position + downRightMap[j]).getType() ==
                         PieceType::NONE)
                {
                    getLegalMoves[position].push_back(position + downRightMap[j]);
                }
                else if (operateBoard.getSquare(position + downRightMap[j]).getColor() ==
                         operateTurn)
                {
                    downRight = false;
                }
            }
        }
    }
    return getLegalMoves;
}
std::map<int, std::vector<int>> bishopMoves(Board operateBoard, Color operateTurn, int position)
{
    // King moves
    if (operateBoard.getSquare(position).getType() == PieceType::KING)
    {
        for (int j = 0; j < 8; j++)
        {
            if (position + kingMap[j] >= 0 && position + kingMap[j] <= 63)
            {
                if (operateBoard.getSquare(position + kingMap[j]).getColor() !=
                    operateTurn)
                {
                    getLegalMoves[position].push_back(position + kingMap[j]);
                }
            }
        }
    }
    return getLegalMoves;
}