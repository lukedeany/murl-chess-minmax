import chess;
import math

board = chess.Board();

def evaluate(turn: bool):
    white_count = 0;
    black_count = 0;

    for square in chess.SQUARES:
        piece = board.piece_at(square)
        if piece:
            if piece.color == chess.WHITE:
                white_count += piece.piece_type
            else:
                black_count += piece.piece_type;

    return white_count - black_count


def minmax(depth):
    if depth == 0:
        return (evaluate(board.turn), None); #

    legal_moves = board.legal_moves;

    best_move = None;
    best_eval = 0;
    if board.turn == chess.WHITE:
        best_eval = -100;
    else:
        best_eval = 100;

    # Go down a path of being a legal move
    for move in legal_moves:
        # Do, then undo, a legal move
        board.push(move);
        evaluation = minmax(depth - 1);
        board.pop();

        print(best_eval, evaluation[0]);
        if (board.turn == chess.WHITE):
            if (best_eval < evaluation[0]):
                best_eval = evaluation[0];
                best_move = move;
        else:
            if (best_eval > evaluation[0]):
                best_eval = evaluation[0];
                best_move = move;
        
        #print(best_eval, best_move);

    # Now get the best possible move
    return (best_eval, best_move);


result = minmax(3);

print(result[0])
print(result[1])