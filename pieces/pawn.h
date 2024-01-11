#include "piece.h"

// Pawn.h
class Pawn : public Piece
{
private:
    int direction;

public:
    Pawn(Color color, int position) : Piece(color, position) { 
        if (color == Color::WHITE) { direction = 1; }
        else { direction = -1; }
    }

    bool move(int newPosistion) override
    {
        if (newPosistion == position + (direction * 8))
        {
            return true;
        }
        else { return false; }
    }
};