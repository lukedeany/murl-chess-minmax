import chess;

board = chess.Board();


# get legal moves to begin loop
legal_moves = board.legal_moves;
for move in legal_moves:
    board.push(move);

    print (board);

    board.pop();


print(board.outcome());