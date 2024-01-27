#include <iostream>

#include "chessGame.h"

int main() {
    // Example usage
    ChessBoard chessBoard;

    // Set pieces on the board
    chessBoard.setPiece(0, 0, ChessBoard::WHITE_COLOR, ChessBoard::ROOK);
    chessBoard.setPiece(7, 7, ChessBoard::BLACK_COLOR, ChessBoard::QUEEN);

    // Get and print pieces from the board
    std::cout << "Piece at (0, 0): " << chessBoard.getPiece(0, 0) << std::endl;
    std::cout << "Piece at (7, 7): " << chessBoard.getPiece(7, 7) << std::endl;

    return 0;
}