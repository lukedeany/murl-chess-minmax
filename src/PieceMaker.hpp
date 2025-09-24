#include "Piece.hpp"
#include <memory>

// what a joke
// used to create pieces with independent pointers!
// used to decouple a bit from board, may be implemented into board later
// if I want it to be closer.
class PieceMaker
{
    public:
        template <ConcretePiece Piece>
        std::unique_ptr<Piece> createPiece()
        {
            // Create a unique_ptr to our special piece!
            std::unique_ptr<Piece> pointer { std::make_unique<Piece>(current_id) };
            
            // Create a new id!
            current_id++;

            return pointer;
        }

    private:
        // Be a counter for all IDs in the current program
        int current_id {0};
};
