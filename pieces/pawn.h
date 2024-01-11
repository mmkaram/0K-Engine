#include "piece.cpp"

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

    int move(int newPosistion) override
    {
        if (newPosistion == position + direction)
        {
            position = newPosistion;
            return 0;
        }
        else { return 1; }
    }
};