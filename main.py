import chess;

board = chess.Board();


def minmax(depth):
    if depth == 0:
        print(board);
        return # analysis

    legal_moves = board.legal_moves;

    # Go down a path of being a legal move
    for move in legal_moves:
        # Do, then undo, a legal move
        board.push(move);
        minmax(depth - 1);
        board.pop();

minmax(2);