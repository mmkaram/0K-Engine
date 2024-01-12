#include "piece.h"

class Rook : public Piece
{
public:
    Rook(Color color, int position) : Piece(color, position)
    {
        //
    }

    char getRenderChar() const override { return 'R'; }

    std::array<int, 9> getPath(int newPosition) override
    {

        std::array<int, 9> path = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
        int pos = this->position;
        int i = 0;
        // Check if it's moving along a file
        if (abs(newPosition - this->position) % 8 == 0)
        {
            std::cout << "suck my dick you dumbass \n";

            if (this->position > newPosition) // if going upwards (backwards in the array)
            {

                while (pos != newPosition) // subtract 8 from pos until we get to newPosition
                {
                    pos -= 8;
                    path[i] = pos;
                    i++;
                }
            } else {
                while (pos != newPosition) // add 8 from pos until we get to newPosition
                {
                    pos += 8;
                    path[i] = pos;
                    i++;
                }
            }
        } else { // if it's moving along a rank
            if (this->position > newPosition) // if going left (backwards in the array)
            {
                while (pos != newPosition) // subtract 1 from pos until we get to newPosition
                {
                    pos -= 1;
                    path[i] = pos;
                    i++;
                }
            } else {
                while (pos != newPosition) // add 1 from pos until we get to newPosition
                {
                    pos += 1;
                    path[i] = pos;
                    i++;
                }
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

        // Check if the move is along a rank or file
        if (oldX == newX || // Same file
            oldY == newY)   // Same rank
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