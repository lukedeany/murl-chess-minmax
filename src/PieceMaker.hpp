#pragma once
#include "Piece.hpp"
#include <memory>

// used to create pieces with independent piece objects (done through unique ptrs)!
// used to decouple a bit from board, may be implemented into board later
// if I want it to be coupled.
class PieceMaker
{
    public:
        template <ConcretePiece Piece>
        std::unique_ptr<Piece> createPiece(PieceColor color)
        {
            // Create a unique_ptr to our special piece!
            std::unique_ptr<Piece> pointer { std::make_unique<Piece>(current_id, color) };
            
            // Create a new id!
            current_id++;

            return pointer;
        }

    private:
        // Be a counter for all IDs in the current program
        int current_id {0};
};
