from enum import Enum, auto
from dataclasses import dataclass, field
from typing import Optional
import copy

"""
Game State
==================================================================
"""
 
"""
─────────────────────────────────────────────
 1. ENUMS
─────────────────────────────────────────────
"""
 
class CellType(Enum):
    EMPTY    = '.'   # Neutral; capturable
    OBSTACLE = 'X'   # Impassable; permanent
    FORTRESS = 'F'   # High-value; defense=2 at start
    MINEFIELD= 'M'   # Traversable; triggers chance event
    OWNED    = 'O'   # Owned by an agent (owner tracked separately)
 
 
class AgentID(Enum):
    A = 'A'   # Expert
    B = 'B'   # Intermediate
    C = 'C'   # Novice
 
"""
─────────────────────────────────────────────
 2. CELL - Cell on board
─────────────────────────────────────────────
"""
 
@dataclass
class Cell:
    cell_type          : CellType          = CellType.EMPTY   # cell type (determines passability and special effects)
    owner              : Optional[AgentID] = None             # the agent who owns it
    defense            : int               = 1                # successful hits needed to capture (1 for regular, 2 for fortress)
    is_fortress        : bool              = False            # True if this cell grants +3/round (set on init for Fortress; kept if captured)
    temp_fortress_rounds: int              = 0                # countdown for Supply Drop temporary fortresses (0 = permanent/normal, >0 means it's a temporary Supply Drop fortress)
 
    # Agents can move to any cell accept obstacle
    def is_passable(self) -> bool:
        return self.cell_type != CellType.OBSTACLE
 
    def is_owned_by(self, agent: AgentID) -> bool:
        return self.owner == agent
 
    # Points this cell yields per round to its owner
    def score_value(self) -> int:
        if self.owner is None:
            return 0
        return 3 if self.is_fortress else 1
 
    # Revert this cell to a neutral empty state
    def reset_to_empty(self):
        self.cell_type  = CellType.EMPTY
        self.owner      = None
        self.defense    = 1
        self.is_fortress= False
        # Note: temp_fortress_rounds left as-is; game engine handles expiry
 
	# Printing string for debugging
    def __repr__(self):
        if self.owner:
            return f"Cell({self.owner.value},def={self.defense},{'F' if self.is_fortress else 'O'})"
        return f"Cell({self.cell_type.value})"
 
"""
─────────────────────────────────────────────
 3. UNIT - a single agent unit on the board
─────────────────────────────────────────────
"""
 
@dataclass
class Unit:
    # One unit belonging to an agent
    unit_id       : int			 # unique id within the agent (0 or 1; bonus unit gets id 2)
    owner         : AgentID		 # the agent this unit belongs to
    row           : int			 # current row position on the board
    col           : int			 # current column position on the board
    disabled_turns: int  = 0     # counts down each turn; unit skips action while >0
    is_bonus      : bool = False # True if this is the temporary Reinforcement bonus unit
    bonus_turns   : int  = 0     # counts down; unit removed when reaches 0
 
    def position(self) -> tuple[int, int]:
        return (self.row, self.col)
 
    def can_act(self) -> bool:
        return self.disabled_turns == 0
 
	# Called once per turn to reduce disabled countdown
    def tick_disabled(self):
        if self.disabled_turns > 0:
            self.disabled_turns -= 1
 
	# Called once per turn for bonus units
	# Returns True if the unit should be removed (lifetime expired/DEAD)
    def tick_bonus(self) -> bool:
        if self.is_bonus:
            self.bonus_turns -= 1
            return self.bonus_turns <= 0
        return False
 
    def __repr__(self):
        status = "disabled" if self.disabled_turns > 0 else "active"
        return f"Unit({self.owner.value}{self.unit_id}@({self.row},{self.col})[{status}])"
    
"""
─────────────────────────────────────────────
 4. AGENT STATE - per-agent tracking
─────────────────────────────────────────────
"""
 
@dataclass
class AgentState:
    # Everything tracked for one agent across the whole game.
    agent_id     : AgentID		  							# the agent this state belongs to
    energy       : int        = 20						    # shared energy pool for all this agent's units
    score        : int        = 0						    # total score earned so far
    units        : list       = field(default_factory=list) # list of Unit objects currently on the board
    is_eliminated: bool       = False						# True once all units gone or energy at 0 and no units
 
    # Deduct energy. Returns True if successful, False if not enough energy.
    def spend_energy(self, amount: int = 1) -> bool:
        if self.energy >= amount:
            self.energy -= amount
            return True
        return False
 
	# Agent can act only if it has energy > 0 and at least one active unit
    def can_act(self) -> bool:
        if self.is_eliminated:
            return False
        return self.energy > 0 and any(u.can_act() for u in self.units)
 
	# Units that are not disabled
    def active_units(self) -> list:
        return [u for u in self.units if u.can_act()]
 
    def add_score(self, points: int):
        self.score += points
 
	# Cells owned by this agent
    def owned_cells_count(self, board: 'Board') -> int:
        count = 0
        for row in board.grid:
            for cell in row:
                if cell.owner == self.agent_id:
                    count += 1
        return count
 
    def __repr__(self):
        return (f"AgentState({self.agent_id.value} | "
                f"energy={self.energy} | score={self.score} | "
                f"units={len(self.units)} | eliminated={self.is_eliminated})")
 
 
"""
─────────────────────────────────────────────
 5. BOARD - the grid
─────────────────────────────────────────────
"""

class Board:
    # Stores Cell objects in a 2D list.
    def __init__(self, rows: int, cols: int):
        self.rows = rows
        self.cols = cols
        # Initialize every cell as empty
        self.grid: list[list[Cell]] = [
            [Cell() for _ in range(cols)]
            for _ in range(rows)
        ]
 
    def in_bounds(self, row: int, col: int) -> bool:
        return 0 <= row < self.rows and 0 <= col < self.cols
 
    def get_cell(self, row: int, col: int) -> Cell:
        return self.grid[row][col]
 
    def set_cell_type(self, row: int, col: int, cell_type: CellType,
                      defense: int = 1, is_fortress: bool = False):
        cell = self.grid[row][col]
        cell.cell_type   = cell_type
        cell.defense     = defense
        cell.is_fortress = is_fortress
 
	# Returns valid (row, col) neighbours in 4 directions
    def adjacent_cells(self, row: int, col: int) -> list[tuple[int, int]]:
        directions = [(-1,0),(1,0),(0,-1),(0,1)]
        return [
            (row+dr, col+dc)
            for dr, dc in directions
            if self.in_bounds(row+dr, col+dc)
        ]
 
    # Returns adjacent cells an agent can actually move to
    def passable_adjacent(self, row: int, col: int) -> list[tuple[int, int]]:
        lst = []
        for r, c in self.adjacent_cells(row, col):
            if self.grid[r][c].is_passable():
                lst.append((r, c))
        return lst
 
    def count_owned(self, agent_id: AgentID) -> int:
        count = 0
        for row in self.grid:
            for cell in row:
                if cell.owner == agent_id:
                    count += 1
        return count
 
    def total_non_obstacle_cells(self) -> int:
        count = 0
        for row in self.grid:
            for cell in row:
                if cell.cell_type != CellType.OBSTACLE:
                    count += 1
        return count
 
    # List of (row, col, cell) for all cells owned by agent
    def all_owned_cells(self, agent_id: AgentID) -> list[tuple[int, int, Cell]]:
        result = []
        for r, row in enumerate(self.grid):
            for c, cell in enumerate(row):
                if cell.owner == agent_id:
                    result.append((r, c, cell))
        return result
 
    def __repr__(self):
        lines = []
        for row in self.grid:
            line = ""
            for cell in row:
                if cell.owner:
                    line += cell.owner.value
                elif cell.cell_type == CellType.FORTRESS:
                    line += 'F'
                elif cell.cell_type == CellType.OBSTACLE:
                    line += 'X'
                elif cell.cell_type == CellType.MINEFIELD:
                    line += 'M'
                else:
                    line += '.'
            lines.append(line)
        return "\n".join(lines)
 
 