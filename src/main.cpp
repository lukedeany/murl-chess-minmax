#include "board.hpp"
#include <iostream>

int main()
{
    Chessboard<8,8> board{};

    std::cout << board.getPieceAtPosition(Position{3,3}) << std::endl;

    return 0;
}

