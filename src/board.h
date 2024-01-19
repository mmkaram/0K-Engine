#include "piece.h"

class Board {
private:
  Piece *board[64];

public:
  Board() {
    for (int i = 0; i < 64; i++) {
      board[i] = new Piece(Color::NONE, PieceType::NONE);
    }

    for (int i = 8; i < 16; i++) {
      board[i] = new Piece(Color::WHITE, PieceType::PAWN);
    }
    for (int i = 48; i < 56; i++) {
      board[i] = new Piece(Color::BLACK, PieceType::PAWN);
    }

    // adding a test piece
    board[2 + 16] = new Piece(Color::WHITE, PieceType::KNIGHT);

    board[0] = new Piece(Color::WHITE, PieceType::ROOK);

    board[16 + 1] = new Piece(Color::WHITE, PieceType::BISHOP);

    board[32] = new Piece(Color::WHITE, PieceType::QUEEN);
  }
  ~Board() {
    for (int i = 0; i < 64; i++) {
      delete board[i];
    }
  }
  Piece getSquare(int pos) { return *board[pos]; }
  void movePiece(int from, int to) {
    board[to] = board[from];
    board[from] = new Piece(Color::NONE, PieceType::NONE);
  }

  std::string boardString() {
    std::string boardString = "";
    for (int i = 0; i < 64; i++) {
      if (i % 8 == 0) {
        boardString += "\n";
      }
      switch (board[i]->getType()) {
      case PieceType::KING:
        boardString += (board[i]->getColor() == Color::WHITE) ? "K" : "k";
        break;
      case PieceType::QUEEN:
        boardString += (board[i]->getColor() == Color::WHITE) ? "Q" : "q";
        break;
      case PieceType::ROOK:
        boardString += (board[i]->getColor() == Color::WHITE) ? "R" : "r";
        break;
      case PieceType::BISHOP:
        boardString += (board[i]->getColor() == Color::WHITE) ? "B" : "b";
        break;
      case PieceType::KNIGHT:
        boardString += (board[i]->getColor() == Color::WHITE) ? "N" : "n";
        break;
      case PieceType::PAWN:
        boardString += (board[i]->getColor() == Color::WHITE) ? "P" : "p";
        break;
      case PieceType::NONE:
        boardString += "-";
        break;
      }
      boardString += " ";
    }
    return boardString;
  }
};
