#pragma once
#include <array>

enum class Color
{
    WHITE,
    BLACK
};

class Piece
{
protected:
    Color color;
    int position;

public:
    Piece(Color color, int position)
    {
        this->color = color;
        this->position = position;
    }

    Color getColor() const { return color; }

    int getPosition() const { return position; }

    std::array<int, 2> getPositionXY() const
    {
        int x = position % 8; // Modulus operator gives the remainder of the division, which is the x coordinate
        int y = position / 8; // Integer division gives the quotient of the division, which is the y coordinate
        return std::array<int, 2>{x, y};
    }

    void setPosition(int position) { this->position = position; }

    virtual bool move(int newPosition) { return false; };
};