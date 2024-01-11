#include "piece.h"

class Queen : public Piece
{
private:
    int direction;

public:
    Queen(Color color, int position) : Piece(color, position) {}

    bool move(int newPosition) override
    {
        int oldX = position % 8;
        int oldY = position / 8;
        int newX = newPosition % 8;
        int newY = newPosition / 8;

        // Check if the move is along a rank, file, or diagonal
        if (oldX == newX ||                       // Same file
            oldY == newY ||                       // Same rank
            abs(oldX - newX) == abs(oldY - newY)) // Diagonal
        {
            position = newPosition;
            return true;
        }
        else
        {
            return false;
        }
    }
};