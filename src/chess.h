#include <algorithm>
#include <array>
#include <iostream>
#include <map>
#include <vector>

#include "board.h"

class Chess {
private:
  Board board = Board();
  Color turn;

  std::array<int, 8> upMap = {8, 16, 24, 32, 40, 48, 56, 64};
  std::array<int, 8> downMap = {-8, -16, -24, -32, -40, -48, -56, -64};
  std::array<int, 8> leftMap = {-1, -2, -3, -4, -5, -6, -7, -8};
  std::array<int, 8> rightMap = {1, 2, 3, 4, 5, 6, 7, 8};

  std::array<int, 8> upLeftMap = {-9, -18, -27, -36, -45, -54, -63, -72};
  std::array<int, 8> upRightMap = {-7, -14, -21, -28, -35, -42, -49, -56};
  std::array<int, 8> downLeftMap = {7, 14, 21, 28, 35, 42, 49, 56};
  std::array<int, 8> downRightMap = {9, 18, 27, 36, 45, 54, 63, 72};

  std::array<int, 8> knightMap = {-17, -15, -10, -6, 6, 10, 15, 17};

  std::array<int, 8> pawnMap = {8};

  std::array<int, 8> kingMap = {-9, -8, -7, -1, 1, 7, 8, 9};

public:
  Chess() : turn(Color::WHITE) {}

  ~Chess() {}

  Board getBoard() { return board; }

  std::string boardString() { return board.boardString(); }

  Color getTurn() { return turn; }

  std::map<int, std::vector<int>> getPseudoLegalMoves(Board operateBoard,
                                                      Color operateTurn) {
    std::map<int, std::vector<int>> getLegalMoves;
    // get some popcorn and get comfortable, this is gonna be a long one
    for (int i = 0; i < 64; i++) {
      // Check if there is a piece at the current position
      if (operateBoard.getSquare(i).getType() == PieceType::NONE) {
        continue;
      }
      // Check if the piece at the current position is of the correct color
      if (operateBoard.getSquare(i).getColor() != operateTurn) {
        continue;
      }
      if (operateBoard.getSquare(i).getType() == PieceType::PAWN) {
        // multiply by 1 if white, -1 if black
        int direction = (operateTurn == Color::WHITE) ? 1 : -1;
        // TODO: Check for en passant
        // TODO: Check for promotion
        // Check if the pawn can move forward for white

        if (operateBoard.getSquare(i + pawnMap[0] * direction).getType() ==
            PieceType::NONE) {
          getLegalMoves[i].push_back(i + pawnMap[0] * direction);
          if ((operateTurn == Color::WHITE && i > 7 && i < 16) &&
              (operateBoard.getSquare(i + pawnMap[0] * direction * 2)
                   .getType() == PieceType::NONE)) {
            getLegalMoves[i].push_back(i + (pawnMap[0] * direction * 2));
          } else if ((operateTurn == Color::BLACK && i < 56 && i > 47) &&
                     (operateBoard.getSquare(i + pawnMap[0] * direction * 2)
                          .getType() == PieceType::NONE)) {
            getLegalMoves[i].push_back(i + (pawnMap[0] * direction * 2));
          }
        }
        // Check if the pawn can move diagonally
        if (operateBoard.getSquare((i + (pawnMap[0] * direction)) + 1)
                    .getColor() != operateTurn &&
            operateBoard.getSquare((i + (pawnMap[0] * direction)) + 1)
                    .getType() != PieceType::NONE) {
          getLegalMoves[i].push_back((i + (pawnMap[0] * direction)) + 1);
        }
        if (operateBoard.getSquare((i + (pawnMap[0] * direction)) - 1)
                    .getColor() != operateTurn &&
            operateBoard.getSquare((i + (pawnMap[0] * direction)) - 1)
                    .getType() != PieceType::NONE) {
          getLegalMoves[i].push_back((i + (pawnMap[0] * direction)) - 1);
        }
      }
      // Knight checking logic
      if (operateBoard.getSquare(i).getType() == PieceType::KNIGHT) {
        for (int j = 0; j < 8; j++) {
          if (operateBoard.getSquare(i + knightMap[j]).getColor() !=
              operateTurn) {
            getLegalMoves[i].push_back(i + knightMap[j]);
          }
        }
      }
      // Rook checking logic
      if (operateBoard.getSquare(i).getType() == PieceType::ROOK ||
          operateBoard.getSquare(i).getType() == PieceType::QUEEN) {
        bool up = true;
        bool down = true;
        bool left = true;
        bool right = true;

        for (int j = 0; j < 8; j++) {

          if (i + upMap[j] >= 0 && i + upMap[j] <= 63 && up) {
            // if enemy piece is found, add it to the vector and stop checking
            // in that direction
            if (operateBoard.getSquare(i + upMap[j]).getColor() !=
                    operateTurn &&
                operateBoard.getSquare(i + upMap[j]).getType() !=
                    PieceType::NONE) {
              getLegalMoves[i].push_back(i + upMap[j]);
              up = false;
              // if no enemy piece is found, add it to the vector
            } else if (operateBoard.getSquare(i + upMap[j]).getType() ==
                       PieceType::NONE) {
              getLegalMoves[i].push_back(i + upMap[j]);
            }
            // if the piece is the same color, stop checking in that direction
            else if (operateBoard.getSquare(i + upMap[j]).getColor() ==
                     operateTurn) {
              up = false;
            }
          }
          //

          if (i + downMap[j] >= 0 && i + downMap[j] <= 63 && down) {
            // if enemy piece is found, add it to the vector and stop checking
            // in that direction
            if (operateBoard.getSquare(i + downMap[j]).getColor() !=
                    operateTurn &&
                operateBoard.getSquare(i + downMap[j]).getType() !=
                    PieceType::NONE) {
              getLegalMoves[i].push_back(i + downMap[j]);
              down = false;
              // if no enemy piece is found, add it to the vector
            } else if (operateBoard.getSquare(i + downMap[j]).getType() ==
                       PieceType::NONE) {
              getLegalMoves[i].push_back(i + downMap[j]);
            }
            // if the piece is the same color, stop checking in that direction
            else if (operateBoard.getSquare(i + downMap[j]).getColor() ==
                     operateTurn) {
              down = false;
            }
          }

          //
          if (i + leftMap[j] >= 0 && i + leftMap[j] <= 63 && left) {
            // if enemy piece is found, add it to the vector and stop checking
            // in that direction
            if (operateBoard.getSquare(i + leftMap[j]).getColor() !=
                    operateTurn &&
                operateBoard.getSquare(i + leftMap[j]).getType() !=
                    PieceType::NONE) {
              getLegalMoves[i].push_back(i + leftMap[j]);
              left = false;
              // if no enemy piece is found, add it to the vector
            } else if (operateBoard.getSquare(i + leftMap[j]).getType() ==
                       PieceType::NONE) {
              getLegalMoves[i].push_back(i + leftMap[j]);
            }
            // if the piece is the same color, stop checking in that direction
            else if (operateBoard.getSquare(i + leftMap[j]).getColor() ==
                     operateTurn) {
              left = false;
            }
          }

          //
          if (i + rightMap[j] >= 0 && i + rightMap[j] <= 63 && right) {
            // if enemy piece is found, add it to the vector and stop checking
            // in that direction
            if (operateBoard.getSquare(i + rightMap[j]).getColor() !=
                    operateTurn &&
                operateBoard.getSquare(i + rightMap[j]).getType() !=
                    PieceType::NONE) {
              getLegalMoves[i].push_back(i + rightMap[j]);
              right = false;
              // if no enemy piece is found, add it to the vector
            } else if (operateBoard.getSquare(i + rightMap[j]).getType() ==
                       PieceType::NONE) {
              getLegalMoves[i].push_back(i + rightMap[j]);
            }
            // if the piece is the same color, stop checking in that direction
            else if (operateBoard.getSquare(i + rightMap[j]).getColor() ==
                     operateTurn) {
              right = false;
            }
          }
        }
      }
      // Bishop moves
      if (operateBoard.getSquare(i).getType() == PieceType::BISHOP ||
          operateBoard.getSquare(i).getType() == PieceType::QUEEN) {
        bool upLeft = true;
        bool downLeft = true;
        bool upRight = true;
        bool downRight = true;

        for (int j = 0; j < 8; j++) {

          //
          if (i + upLeftMap[j] >= 0 && i + upLeftMap[j] <= 63 && upLeft) {
            if (operateBoard.getSquare(i + upLeftMap[j]).getColor() !=
                    operateTurn &&
                operateBoard.getSquare(i + upLeftMap[j]).getType() !=
                    PieceType::NONE) {
              getLegalMoves[i].push_back(i + upLeftMap[j]);
              upLeft = false;
            } else if (operateBoard.getSquare(i + upLeftMap[j]).getType() ==
                       PieceType::NONE) {
              getLegalMoves[i].push_back(i + upLeftMap[j]);
            } else if (operateBoard.getSquare(i + upLeftMap[j]).getColor() ==
                       operateTurn) {
              upLeft = false;
            }
          }

          //
          if (i + downLeftMap[j] >= 0 && i + downLeftMap[j] <= 63 && downLeft) {
            if (operateBoard.getSquare(i + downLeftMap[j]).getColor() !=
                    operateTurn &&
                operateBoard.getSquare(i + downLeftMap[j]).getType() !=
                    PieceType::NONE) {
              getLegalMoves[i].push_back(i + downLeftMap[j]);
              downLeft = false;
            } else if (operateBoard.getSquare(i + downLeftMap[j]).getType() ==
                       PieceType::NONE) {
              getLegalMoves[i].push_back(i + downLeftMap[j]);
            } else if (operateBoard.getSquare(i + downLeftMap[j]).getColor() ==
                       operateTurn) {
              downLeft = false;
            }
          }

          //
          if (i + upRightMap[j] >= 0 && i + upRightMap[j] <= 63 && upRight) {
            if (operateBoard.getSquare(i + upRightMap[j]).getColor() !=
                    operateTurn &&
                operateBoard.getSquare(i + upRightMap[j]).getType() !=
                    PieceType::NONE) {
              getLegalMoves[i].push_back(i + upRightMap[j]);
              upRight = false;
            } else if (operateBoard.getSquare(i + upRightMap[j]).getType() ==
                       PieceType::NONE) {
              getLegalMoves[i].push_back(i + upRightMap[j]);
            } else if (operateBoard.getSquare(i + upRightMap[j]).getColor() ==
                       operateTurn) {
              upRight = false;
            }
          }

          //
          if (i + downRightMap[j] >= 0 && i + downRightMap[j] <= 63 &&
              downRight) {
            if (operateBoard.getSquare(i + downRightMap[j]).getColor() !=
                    operateTurn &&
                operateBoard.getSquare(i + downRightMap[j]).getType() !=
                    PieceType::NONE) {
              getLegalMoves[i].push_back(i + downRightMap[j]);
              downRight = false;
            } else if (operateBoard.getSquare(i + downRightMap[j]).getType() ==
                       PieceType::NONE) {
              getLegalMoves[i].push_back(i + downRightMap[j]);
            } else if (operateBoard.getSquare(i + downRightMap[j]).getColor() ==
                       operateTurn) {
              downRight = false;
            }
          }
        }

        // King moves
        if (operateBoard.getSquare(i).getType() == PieceType::KING) {
          for (int j = 0; j < 8; j++) {
            if (i + kingMap[j] >= 0 && i + kingMap[j] <= 63) {
              if (operateBoard.getSquare(i + kingMap[j]).getColor() !=
                  operateTurn) {
                getLegalMoves[i].push_back(i + kingMap[j]);
              }
            }
          }
        }
      }
    }
    printMap(getLegalMoves);
    return getLegalMoves;
  }

  std::map<int, std::vector<int>> getLegalMoves(int kingPos) {
    // this function uses the getPseudoLegalMoves function and removes
    // moves that would put the king in check
    std::map<int, std::vector<int>> getLegalMoves =
        getPseudoLegalMoves(this->board, turn);
    // find king
    // for (int a = 0; a < 64; a++) {
    //   if (board.getSquare(a).getType() == PieceType::KING &&
    //       board.getSquare(a).getColor() == turn) {
    //     kingPos = a;
    //   }
    // }
    // TODO: Check for checks
    // a for loop that goes through all possible moves
    // sets a new board to that position
    // sets the player to the opposite color
    // checks if the king can be captured
    // if it can, remove the move from the map


    return getLegalMoves;
  }

  void printMap(const std::map<int, std::vector<int>> &m) {
    for (const auto &pair : m) {
      std::cout << "Key: " << pair.first << " Values: ";
      for (const auto &val : pair.second) {
        std::cout << val << " ";
      }
      std::cout << std::endl;
    }
  }

  bool canMovePiece(int currentPos, int newPos) {

  }
};
