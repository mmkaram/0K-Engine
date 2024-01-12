#include "piece.h"

class Queen : public Piece
{
public:
    Queen(Color color, int position) : Piece(color, position) {}

    char getRenderChar() const override { return 'Q'; }

    std::array<int, 9> getPath(int newPosition) override
    {
        std::array<int, 9> path = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
        int pos = this->position;
        int i = 0;

        // Check if the move is along a rank or file
        if (abs(newPosition - this->position) % 8 == 0 || abs(newPosition - this->position) % 9 == 0 || abs(newPosition - this->position) % 7 == 0)
        {
            int step = this->position < newPosition ? 1 : -1;
            if (abs(newPosition - this->position) % 8 == 0)
                step *= 8; // moving vertically
            else if (abs(newPosition - this->position) % 9 == 0)
                step *= 9; // moving diagonally right
            else if (abs(newPosition - this->position) % 7 == 0)
                step *= 7; // moving diagonally left

            while (pos != newPosition)
            {
                pos += step;
                path[i] = pos;
                i++;
            }
        }

        return path;
    }

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