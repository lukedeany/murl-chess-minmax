#include "Board.hpp"
#include "Position.hpp"
#include "Piece.hpp"
#include <iostream>

int main()
{
    Chessboard<8,8> board{};

    for (int i {0}; i < 8; i++)
    {
        board.setPieceAtPosition( Position {i, 2}, WhitePawn );
        board.setPieceAtPosition( Position {i, 7}, BlackPawn );
    }

    std::cout << board.getPieceAtPosition(Position{1,2}) << std::endl;

    return 0;
}

