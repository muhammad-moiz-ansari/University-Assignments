import copy

def calculate_board_conflicts(board, n):
    count = 0
    for i in range(n):
        for j in range(n):
            if board[i][j] == 'Q':
                count += calculate_conflicts(board, n, i, j)
    return count

def calculate_conflicts(board, n, row, col):
    count = 0

    # Column conflicts
    col_q = 0
    for r in range(row, n):
        if board[r][col] == 'Q':
            col_q += 1
    count += col_q - 1
        
    # Primary Diagonal
    i = row
    j = col
    d_q = 0
    while i < n and j < n:
        if board[i][j] == 'Q':
            d_q += 1
        i += 1
        j += 1
    count += d_q - 1

    # Secondary Diagonal
    i = row
    j = col
    d_q = 0
    while i < n and j >= 0:
        if board[i][j] == 'Q':
            d_q += 1
        i += 1
        j -= 1
    count += d_q - 1

    return count

def get_neighbors(board, n, row):
    boards = []
    def_row = []
    for i in range(n):
        def_row.append('.')

    for i in range(n):
        tboard = copy.deepcopy(board)
        tboard[row] = copy.deepcopy(def_row)
        tboard[row][i] = 'Q'
        boards.append(tboard)

    return boards
    pass

def hill_climbing_n_queens(board, n, k):
    for i in range(n):
        boards = get_neighbors(board, n, i)
        min_conflicts = calculate_board_conflicts(board, n)
        best_board = board
        for b in boards:
            c = calculate_board_conflicts(b, n)
            if c < min_conflicts:
                min_conflicts = c
                best_board = b
        board = best_board
    
    return board, min_conflicts

def solve_n_queens(n, k, board):
    print("Initial Board:")
    print_board(board)
    init_count = calculate_board_conflicts(board, n)
    print(f"Initial conflict count: {init_count}")
    
    i = 0
    conflicts = init_count
    while conflicts > 0 and i < 1000:
        final_board, conflicts = hill_climbing_n_queens(board, n, k)
        i += 1
    print("\nFinal Board:")
    print_board(final_board)
    print(f"Final Conflicts: {conflicts}")

def print_board(board):
    for r in board:
        print(" ".join(r))
    #print()

# Define board parameters
n = 6 # Board size
k = 6 # Number of queens to place
initial_board = [
    ['.', 'Q', '.', '.', '.', '.'],
    ['.', 'Q', '.', '.', '.', '.'],
    ['.', '.', '.', 'Q', '.', '.'],
    ['.', '.', '.', '.', '.', 'Q'],
    ['.', '.', '.', 'Q', '.', '.'],
    ['.', '.', '.', '.', '.', 'Q']
]

# Start the solver
solve_n_queens(n, k, initial_board)