#include "piece.h"

// Pawn.h
class Pawn : public Piece
{
private:
    int direction;

public:
    char getRenderChar() const override { return 'P'; }

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