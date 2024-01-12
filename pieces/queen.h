#include "piece.h"

class Queen : public Piece
{
public:
    Queen(Color color, int position) : Piece(color, position) {}

    char getRenderChar() const override { return 'Q'; }

    bool move(int newPosition) override
    {
        if (!inBoard(newPosition))
        {
            return false;
        }
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