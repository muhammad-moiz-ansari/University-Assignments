import random
import copy

move_directions = [
    (-1, -1), (-1, 0), (-1, 1), # Top-left, Top, Top-right
    (0, -1),           (0, 1),  # Left, Right
    (1, -1),  (1, 0),  (1, 1)   # Bottom-left, Bottom, Bottom-right
]

pieces = ['k', 'K', 'Q']

def initialize_board(n = 8):
    # Initialize the chess board with the specified dimensions
    board = [[0 for i in range(n)] for i in range(n)]
    
    i = 0
    positions = []
    while i < 3:
        pos = (random.randint(0, n-1), random.randint(0, n-1))
        if pos not in positions:
            positions.append(pos)
            i += 1
    
    # Placing pieces on board
    board[positions[0][0]][positions[0][1]] = 'k'  # Human's King (White)
    board[positions[1][0]][positions[1][1]] = 'K'  # AI's King (Black)
    board[positions[2][0]][positions[2][1]] = 'Q'  # AI's Queen (Black)

    return board

def print_board(board):
    print("  0 1 2 3 4 5 6 7")
    i = 0
    for row in board:
        print(f"{i} " + ' '.join('.' if cell == 0 else str(cell) for cell in row))
        i += 1
    print()

def evaluate_board(board):
    """Evaluate the current board position and return a score."""
    # Assign positive scores for winning positions and negative for losing
    if is_checkmate(board, 'Black'):
        return -100  # Human wins
    elif is_checkmate(board, 'White'):
        return 100  # AI wins
    
    # Heuristic evaluation: favor positions where the opponent's king has fewer moves
    black_king_moves = len(generate_legal_moves(board, 'Black'))
    return 50 - black_king_moves  # Favor positions with fewer escape options for Black

def generate_legal_moves(board, player):
    """Generate all possible legal moves for the given player."""
    # Identify valid moves for the King and Queen based on chess rules
    if player == 'White':
        return generate_king_moves(board, 'k')
    elif player == 'Black':
        king_moves = generate_king_moves(board, 'K')
        queen_moves = generate_queen_moves(board, 'Q')
        return king_moves + queen_moves

def find_piece(board, piece):
    for r in range(len(board)):
        for c in range(len(board[r])):
            if board[r][c] == piece:
                return (r, c)
    return None

def generate_king_moves(board, king):
    # Possible moves for king
    pos = find_piece(board, king)
    if not pos:
        return []  # King not found, should not happen in a valid game
    r1, c1 = pos

    moves = []
    if king == 'k':
        enemy = ['K', 'Q']  # Enemy pieces for White King
    else:
        enemy = ['k', 'q']  # Enemy pieces for Black King
    # just making it generalized for future use

    for direction in move_directions:
        r2 = r1 + direction[0]
        c2 = c1 + direction[1]
        if 0 <= r2 < len(board) and 0 <= c2 < len(board):
            if board[r2][c2] == 0 or board[r2][c2] in enemy:      # If cell is empty or has an enemy piece
                moves.append((r1, c1, r2, c2))
    return moves

def generate_queen_moves(board, queen):
    # Possible moves for queen (combination of rook and bishop)
    pos = find_piece(board, queen)
    if not pos:
        return []  # Queen not found (Queen captured)
    r1, c1 = pos

    moves = []
    if queen == 'Q':
        enemy = ['k', 'q']  # Enemy pieces for Black Queen
    else:
        enemy = ['K', 'Q']  # Enemy pieces for Black King
    # just making it generalized for future use

    for dr in [-1, 0, 1]:
        for dc in [-1, 0, 1]:
            if dr == 0 and dc == 0:
                continue
            r2, c2 = r1 + dr, c1 + dc
            while 0 <= r2 < len(board) and 0 <= c2 < len(board):
                if board[r2][c2] == 0:  # If cell is empty
                    moves.append((r1, c1, r2, c2))
                elif board[r2][c2] in enemy:  # If cell has an enemy piece
                    moves.append((r1, c1, r2, c2))
                    break  # Stop if we hit an enemy piece
                else:
                    break  # Stop if we hit another piece
                r2 += dr
                c2 += dc
    
    return moves

def apply_move(board, move):
    """Apply a given move to the board and return the new board state."""
    # Modify the board according to the move and return the updated state
    new_board = copy.deepcopy(board)
    r1, c1, r2, c2 = move
    piece = new_board[r1][c1]
    new_board[r1][c1] = 0       # Move from old pos
    new_board[r2][c2] = piece   # Move to this new pos
    return new_board

def is_checkmate(board, player):
    """Check if the given player is in checkmate."""
    # Determine if the opposing King has no legal moves and is in check
    if player == 'White':
        king = 'k'
    else:
        king = 'K'

    in_check = is_in_check(board, player)
    if not in_check:
        return False  # King is safe
    else:
        moves = generate_legal_moves(board, player)
        for move in moves:
            new_board = apply_move(board, move)
            if not is_in_check(new_board, player):  # If any move can get out of check
                return False             # King can escape
    return True

def is_in_check(board, player):
    if player == 'White':
        king = 'k'
        opponent = 'Black'
    else:
        king = 'K'
        opponent = 'White'
    moves = generate_legal_moves(board, opponent)

    for move in moves:
        r2, c2 = move[2], move[3]
        if board[r2][c2] == king:
            return True
    return False


def alpha_beta_pruning(board, depth, alpha, beta, is_maximizing):
    """Implement Alpha-Beta Pruning to evaluate board positions efficiently."""
    # Check for terminal states (checkmate/draw)
    # Recursively evaluate all possible moves
    # Apply Alpha-Beta Pruning to cut off unnecessary branches

    if depth == 0 or is_checkmate(board, 'White') or is_checkmate(board, 'Black'):
        return evaluate_board(board)
    
    if is_maximizing:
        max_val = float('-inf')
        moves = generate_legal_moves(board, 'Black')
        for move in moves:
            new_board = apply_move(board, move)
            val = alpha_beta_pruning(new_board, depth - 1, alpha, beta, False)
            max_val = max(max_val, val)
            alpha = max(alpha, val)
            if beta <= alpha:
                break
        return max_val
    else:
        min_val = float('inf')
        moves = generate_legal_moves(board, 'White')
        for move in moves:
            new_board = apply_move(board, move)
            val = alpha_beta_pruning(new_board, depth - 1, alpha, beta, True)
            min_val = min(min_val, val)
            beta = min(beta, val)
            if beta <= alpha:
                break
        return min_val

def find_best_move(board, depth):
    """Determine the best move for the AI using Alpha-Beta Pruning."""
    # Iterate through all possible moves
    # Use Alpha-Beta Pruning to find the optimal move
    # Return the best move found

    best_val = float('-inf')
    best_move = None

    moves = generate_legal_moves(board, 'Black')
    for move in moves:
        new_board = apply_move(board, move)
        val = alpha_beta_pruning(new_board, depth, float('-inf'), float('inf'), False)
        if val > best_val:
            best_val = val
            best_move = move
    return best_move

def play_chess_endgame():
    """Main function to simulate the chess endgame scenario."""
    # Initialize the board with King & Queen vs. King
    board = initialize_board()
    print("Initial Board:")
    print_board(board)

    # Alternate moves between AI and opponent
    while True:
        w_moves = generate_legal_moves(board, 'White')  # Human starts first
        if not w_moves:
            print("No legal moves for White. Black (AI) wins!")
            break
        for i in range(len(w_moves)):
            print(i + 1, ". ", w_moves[i][2], w_moves[i][3])
        move_index = int(input("Enter the move number for White: ")) - 1
        if 0 <= move_index < len(w_moves):
            board = apply_move(board, w_moves[move_index])
            print("Board after White's move:")
            print_board(board)

        # Determine the best move using Alpha-Beta Pruning
        # Continue until checkmate is achieved
        b_move = find_best_move(board, 3)  # AI calculates best move with depth 3
        if b_move:
            board = apply_move(board, b_move)
            print("Board after Black's move:")
            print_board(board)
        else:
            print("No legal moves for Black. White (Human) wins!")


if __name__ == "__main__":
    play_chess_endgame()