#include "Board.hpp"
#include "Position.hpp"
#include "Piece.hpp"
#include "PieceMaker.hpp"
#include <iostream>

int main()
{
    Chessboard<8,8> board{};

    PieceMaker factory;

    for (int i {1}; i < 9; i++)
    {
        std::unique_ptr<Pawn<8,8>> black_piece { factory.createPiece<Pawn<8,8>>(PieceColor::PieceColorBlack) };
        std::unique_ptr<Pawn<8,8>> white_piece { factory.createPiece<Pawn<8,8>>(PieceColor::PieceColorWhite) };

        board.registerPiece( std::move(white_piece), Position {i, 2});
        board.registerPiece( std::move(black_piece), Position {i, 7});
    }

    for (int i {1}; i < 9; i++)
    {
        // holders for our pieces
        std::unique_ptr<Piece<8,8>> black_piece;
        std::unique_ptr<Piece<8,8>> white_piece;

        // Set piece to the correct thing based on this switch
        switch (i) {
            case 1:
                black_piece = factory.createPiece<Rook<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<Rook<8,8>>(PieceColor::PieceColorWhite);
                break;
            case 2:
                black_piece = factory.createPiece<Knight<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<Knight<8,8>>(PieceColor::PieceColorWhite);
                break;
            case 3:
                black_piece = factory.createPiece<Bishop<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<Bishop<8,8>>(PieceColor::PieceColorWhite);
                break;
            case 4:
                black_piece = factory.createPiece<Queen<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<Queen<8,8>>(PieceColor::PieceColorWhite);
                break;
            case 5:
                black_piece = factory.createPiece<King<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<King<8,8>>(PieceColor::PieceColorWhite);
                break;
            case 6:
                black_piece = factory.createPiece<Bishop<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<Bishop<8,8>>(PieceColor::PieceColorWhite);
                break;
            case 7:
                black_piece = factory.createPiece<Knight<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<Knight<8,8>>(PieceColor::PieceColorWhite);
                break;
            case 8:
                black_piece = factory.createPiece<Rook<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<Rook<8,8>>(PieceColor::PieceColorWhite);
                break;
            default:
                black_piece = factory.createPiece<Pawn<8,8>>(PieceColor::PieceColorBlack);
                white_piece = factory.createPiece<Pawn<8,8>>(PieceColor::PieceColorWhite);
                break;
        }

        // Take in our pieces, and register the correct one after moving our value so we move ownership
        board.registerPiece(std::move(white_piece), Position {i, 1});
        board.registerPiece(std::move(black_piece), Position {i, 8});
    }

    // Now for every other piece!
    // maybe add a file format to read in?
    
    
    std::cout << board.getPieceAtPosition(Position{3,2}) << std::endl;
    std::cout << board.canColorMoveToPosition(Position {1,3}, PieceColor::PieceColorWhite ) << std::endl;

    return 0;
}

