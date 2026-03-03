
oneWayDirections = {'<', '>', '^', 'v'}
directionVectors = {'<': (-1, 0), '>': (1, 0), '^': (0, 1), 'v': (0, -1)}

# CLASSES

class Robot:
    def __init__(self, id, pr, elimit, start, goal, chpts):
        self.id = id
        self.priority = pr
        self.energy_limit = elimit
        self.start = start
        self.goal = goal
        self.checkpoints = chpts

    def __str__(self):
        return f"Robot {self.id} (Priority: {self.priority}, Energy Limit: {self.energy_limit}, Start: {self.start}, Goal: {self.goal}, Checkpoints: {self.checkpoints})"
    
class Grid:
    def __init__(self, width, height, cells):
        self.width = width
        self.height = height
        self.cells = cells
        self.reservations = set()
    
    # To get correct element in array
    def getCell(self, x, y):
        return self.cells[self.height - 1 - y][x]

    def add_reservation(self, x, y, t):
        self.reservations.add((x, y, t))

    # ======= CHECK FUNCTIONS =======
    def is_within_bounds(self, x, y):
        return 0 <= x < self.width and 0 <= y < self.height

    def is_reserved(self, x, y, t):
        return (x, y, t) in self.reservations
    
    def is_free(self, x, y):
        return self.getCell(x, y) != 'X'
    
    def is_valid(self, nx, ny, t):  # Current position (cx, cy), next position (nx, ny), time step t
        return self.is_within_bounds(nx, ny) and self.is_free(nx, ny) and not self.is_reserved(nx, ny, t)
    
    def is_oneway(self, cx, cy):
        return self.getCell(cx, cy) in oneWayDirections
    
    def get_valid_neighbors(self, cx, cy, t):
        next_t = t + 1

        # If robot standing on onway
        if self.is_oneway(cx, cy):
            dx, dy = directionVectors[self.getCell(cx, cy)]
            nx, ny = cx + dx, cy + dy
            if self.is_valid(nx, ny, next_t):
                return [(nx, ny)]
            else:
                return []

        # Returning only valid neighbors
        neighbors = []
        if self.is_valid(cx - 1, cy, next_t):
            neighbors.append((cx - 1, cy))
        if self.is_valid(cx + 1, cy, next_t):
            neighbors.append((cx + 1, cy))
        if self.is_valid(cx, cy - 1, next_t):
            neighbors.append((cx, cy - 1))
        if self.is_valid(cx, cy + 1, next_t):
            neighbors.append((cx, cy + 1))

        # Add wait action if any neighbor is reserved
        #if (self.is_free(cx, cy) and self.is_within_bounds(cx, cy)) and (self.is_reserved(cx-1, cy, t) or self.is_reserved(cx+1, cy, t) or self.is_reserved(cx, cy-1, t) or self.is_reserved(cx, cy+1, t)):
        if not self.is_reserved(cx, cy, next_t):
            neighbors.append((cx, cy))

        return neighbors
    
class State:
    def __init__(self, x, y, checkpoint_index, time, parent=None):
        self.x = x
        self.y = y
        self.cp_ind = checkpoint_index
        self.t = time
        self.parent = parent

    def getPosition(self):
        return (self.x, self.y)
    
    def __eq__(self, other):
        return (self.x, self.y, self.cp_ind, self.t) == (other.x, other.y, other.cp_ind, other.t)
    
    def __hash__(self):
        return hash((self.x, self.y, self.cp_ind, self.t))
    
def bfs(robot, grid):
    start_state = State(robot.start[0], robot.start[1], 0, 0, None)

    queue = [start_state]
    visited = set()
    visited.add(start_state)

    while queue:
        curr_state = queue.pop(0)

        # Check if goal is reached
        if (curr_state.x, curr_state.y) == robot.goal and curr_state.cp_ind == len(robot.checkpoints):
            return generate_path(curr_state)
        
        # Check energy limit
        if curr_state.t >= robot.energy_limit:
            continue

        
        # Get valid neighbors
        neighbors = grid.get_valid_neighbors(curr_state.x, curr_state.y, curr_state.t)
        for nx, ny in neighbors:
            next_cp_ind = curr_state.cp_ind

            # Checks if checkpoint visited
            if next_cp_ind < len(robot.checkpoints) and (nx, ny) == robot.checkpoints[next_cp_ind]:
                next_cp_ind += 1

            next_state = State(nx, ny, next_cp_ind, curr_state.t + 1, curr_state)

            if next_state not in visited:
                visited.add(next_state)
                queue.append(next_state)
    return None

def generate_path(state):
    path = []
    while state:
        path.append(state)
        state = state.parent
    return path[::-1]

def parse_txt(filepath):
    with open(filepath, 'r') as file:
        lines = file.read().splitlines()

    N, M = lines[0].split()
    N, M = int(N), int(M)

    # GRID
    cells = []
    # loop N times for N rows
    for i in range(1, N + 1):
        cells.append(lines[i])
        
    line_idx = N + 1
    R = int(lines[line_idx])
    line_idx += 1
    
    robots = []
    
    for i in range(R):
        id, pr, elimit = lines[line_idx].split()
        id, pr, elimit = int(id), int(pr), int(elimit)
        line_idx += 1
        
        st1, st2 = lines[line_idx].split()
        start = (int(st1), int(st2))
        line_idx += 1
        
        g1, g2 = lines[line_idx].split()
        goal = (int(g1), int(g2))
        line_idx += 1

        # Checkpoints
        cnum = int(lines[line_idx])
        line_idx += 1
        
        checkpts = []
        for j in range(cnum):
            c1, c2 = lines[line_idx].split()
            cpt = (int(c1), int(c2))
            checkpts.append(cpt)
            line_idx += 1
            
        robot = Robot(id, pr, elimit, start, goal, checkpts)
        robots.append(robot)

    grid = Grid(M, N, cells)
    
    return grid, robots

    
def main():
    grid, robots = parse_txt('input.txt')

    # Sort robots by priority
    robots.sort(key=lambda r: r.priority, reverse=True)

    for robot in robots:
        path = bfs(robot, grid)
        if path is None:
            print(f"Robot {robot.id}: No valid path found.")
        else:
            print(f"Robot {robot.id}: Path found with length {len(path) - 1}.")
            for state in path:
                grid.add_reservation(state.x, state.y, state.t)


if __name__ == "__main__":
    main()