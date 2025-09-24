#include "Board.hpp"
#include "Position.hpp"
#include "Piece.hpp"
#include "PieceMaker.hpp"
#include <iostream>

int main()
{
    Chessboard<8,8> board{};

    PieceMaker factory;

    for (int i {0}; i < 8; i++)
    {
        std::unique_ptr<Pawn<8,8>> black_piece { factory.createPiece<Pawn<8,8>>() };
        std::unique_ptr<Pawn<8,8>> white_piece { factory.createPiece<Pawn<8,8>>() };

        //auto test = white_piece.get();

        

        board.setPieceAtPosition( Position {i, 2}, white_piece.get()->getID());
        board.setPieceAtPosition( Position {i, 7}, black_piece.get()->getID());
    }

    std::cout << board.getPieceAtPosition(Position{3,2}) << std::endl;

    return 0;
}

