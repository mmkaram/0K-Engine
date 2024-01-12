#include "piece.h"

// Pawn.h
class Pawn : public Piece
{
private:
    int direction;
    bool firstMove = true;

public:
    char getRenderChar() const override { return 'P'; }

    std::array<int, 9> getPath(int newPosition) override
    {
        std::array<int, 9> path = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

        // Check if the move is valid for a pawn
        if (newPosition == this->position + (direction * 8) || newPosition == this->position + (direction * 7) || newPosition == this->position + (direction * 9))
        {
            path[0] = newPosition;
        }

        return path;
    }

    Pawn(Color color, int position) : Piece(color, position)
    {
        if (color == Color::WHITE)
        {
            direction = 1;
        }
        else
        {
            direction = -1;
        }
    }

    bool move(int newPosition) override
    {
        if (!inBoard(newPosition))
        {
            return false;
        }
        if (newPosition == position + (direction * 8))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};