from enum import Enum, auto
from dataclasses import dataclass, field
from typing import Optional
import copy
import random

"""
1. Game State
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
 
"""
─────────────────────────────────────────────
 6. GAME STATE - ties everything together
─────────────────────────────────────────────
"""
 
@dataclass
class GameState:
    board        : Board				# the grid
    agents       : dict            		# dict mapping AgentID -> AgentState
    round_number : int  = 1				# the round we're in
    max_rounds   : int  = 30			# max game rounds
    current_turn : AgentID = AgentID.A	# whose turn it is 
    move_number  : int  = 0				# global move counter (increments each individual unit action)
    fog_active   : bool = False			# True during a Fog of War event turn (visibility radius halved for that turn)
    turn_order   : list = field(default_factory=lambda: [AgentID.A, AgentID.B, AgentID.C])	# fixed order agents take turns in
 
    def get_agent(self, agent_id: AgentID) -> AgentState:
        return self.agents[agent_id]
 
    def active_agents(self) -> list[AgentID]:
        """Agents still in the game (not eliminated)"""
        return [aid for aid in self.turn_order if not self.agents[aid].is_eliminated]
 
    def is_terminal(self) -> bool:
        """Check if the game should end"""
        active = self.active_agents()
 
        # Only one agent left
        if len(active) <= 1:
            return True
 
        # Max rounds reached
        if self.round_number > self.max_rounds:
            return True
 
        # Any agent controls >60% of non-obstacle cells
        total = self.board.total_non_obstacle_cells()
        threshold = total * 0.6
        for aid in active:
            if self.board.count_owned(aid) > threshold:
                return True
 
        return False
 
    def winner(self) -> Optional[AgentID]:
        """Determine winner at game end. None if game not over"""
        if not self.is_terminal():
            return None
        # Highest score wins
        active = self.active_agents()
        if not active:
            return None
        return max(active, key=lambda aid: self.agents[aid].score)
 
    def score_round(self):
        """
        Award points to each agent for cells they own this round.
        Call once per round after all agents have taken their turns.
        """
        for aid in self.active_agents():
            agent = self.agents[aid]
            for row in self.board.grid:
                for cell in row:
                    if cell.owner == aid:
                        agent.add_score(cell.score_value())
 
    def deep_copy(self) -> 'GameState':
        """
        Create a full deep copy of the game state.
        Used by Expectiminimax to explore branches without mutating the real state.
        """
        return copy.deepcopy(self)
 
    def get_observable_cells(self, agent_id: AgentID, radius: int) -> set[tuple[int, int]]:
        """
        Return the set of (row, col) positions visible to the given agent.
        radius=-1 means full board visibility (Expert agent).
        During Fog of War, radius is halved (handled by caller).
        """
        if radius < 0:
            # Full board visibility
            return {
                (r, c)
                for r in range(self.board.rows)
                for c in range(self.board.cols)
            }
 
        visible = set()
        agent = self.agents[agent_id]
        for unit in agent.units:
            for r in range(self.board.rows):
                for c in range(self.board.cols):
                    # Manhattan distance visibility
                    if abs(r - unit.row) + abs(c - unit.col) <= radius:
                        visible.add((r, c))
        return visible
 
    def __repr__(self):
        lines = [f"=== Round {self.round_number}/{self.max_rounds} | Turn: {self.current_turn.value} ==="]
        lines.append(repr(self.board))
        for aid, agent in self.agents.items():
            lines.append(repr(agent))
        return "\n".join(lines)
 

# ─────────────────────────────────────────────
# 7. FACTORY - builds a fresh GameState from parsed board data
# ─────────────────────────────────────────────
 
def build_initial_state(
    rows: int,
    cols: int,
    max_rounds: int,
    grid_chars: list[list[str]],
    start_positions: dict[AgentID, tuple[int, int]]
) -> GameState:
    """
    Build a fresh GameState from the parsed board.txt data.
 
    Arguments:
        rows, cols     : board dimensions
        max_rounds     : R from board.txt
        grid_chars     : 2D list of chars ('.', 'X', 'F', 'M')
        start_positions: {AgentID: (row, col)} for each agent
        
    Returns:
        A fully initialised GameState ready to play.
    """
    board = Board(rows, cols)
 
    # Fill in the grid
    char_to_type = {
        '.': (CellType.EMPTY,     1, False),
        'X': (CellType.OBSTACLE,  0, False),
        'F': (CellType.FORTRESS,  2, True),
        'M': (CellType.MINEFIELD, 1, False),
    }
    for r, row in enumerate(grid_chars):
        for c, ch in enumerate(row):
            cell_type, defense, is_fortress = char_to_type.get(ch, (CellType.EMPTY, 1, False))
            board.set_cell_type(r, c, cell_type, defense, is_fortress)
 
    # Agent configurations - structurally encoded here (not if-else in search)
    AGENT_CONFIGS = {
        AgentID.A: {"label": "Expert",       "start_energy": 20},
        AgentID.B: {"label": "Intermediate", "start_energy": 20},
        AgentID.C: {"label": "Novice",       "start_energy": 20},
    }
 
    agents = {}
    for aid, config in AGENT_CONFIGS.items():
        agent = AgentState(agent_id=aid, energy=config["start_energy"])
 
        # Place 2 starting units
        row, col = start_positions[aid]
        for uid in range(2):
            # Second unit goes to an adjacent cell if possible, else same cell
            if uid == 0:
                ur, uc = row, col
            else:
                # Find first passable adjacent cell for unit 1
                adj = board.passable_adjacent(row, col)
                ur, uc = adj[0] if adj else (row, col)
 
            unit = Unit(unit_id=uid, owner=aid, row=ur, col=uc)
            agent.units.append(unit)
 
            # Agent starts by owning their starting cell
            cell = board.get_cell(ur, uc)
            if cell.cell_type not in (CellType.OBSTACLE,):
                cell.owner = aid
                cell.cell_type = CellType.OWNED if cell.cell_type == CellType.EMPTY else cell.cell_type
 
        agents[aid] = agent
 
    state = GameState(
        board=board,
        agents=agents,
        max_rounds=max_rounds,
        current_turn=AgentID.A,
    )
    return state


"""
2. Game Rules - Actions, Movement, Attack Resolution, Energy
================================================================= 
"""

"""
─────────────────────────────────────────────
 1. ACTION TYPES
─────────────────────────────────────────────
"""
 
class ActionType(Enum):
    MOVE    = "Move"
    ATTACK  = "Attack"
    FORTIFY = "Fortify"
    WAIT    = "Wait"
 
 
@dataclass
class Action:
    """One action by one unit"""
    action_type : ActionType			# what the unit is doing
    unit_id     : int					# the unit (0, 1, or 2 for bonus unit)
    agent_id    : AgentID				# the agent this action belongs to
    target_row  : Optional[int] = None	# destination row (Move/Attack/Fortify) or None (Wait)
    target_col  : Optional[int] = None	# destination column (Move/Attack/Fortify) or None (Wait)
 
    def __repr__(self):
        loc = f"({self.target_row},{self.target_col})" if self.target_row is not None else ""
        return f"{self.action_type.value}{loc} by {self.agent_id.value}[unit{self.unit_id}]"
 
"""
─────────────────────────────────────────────
 2. DIE PROBABILITY TABLE
    9-sided die with UNEVEN probabilities
    Each entry: (die_face, probability, outcome_tag)
─────────────────────────────────────────────
"""
 
DIE_OUTCOMES = [
    # face  prob    outcome tag
    (1,     0.10,   "fail_energy"),     # fail + attacker loses 1 extra energy
    (2,     0.10,   "fail_energy"),
    (3,     0.15,   "fail"),            # fail, no extra penalty
    (4,     0.08,   "partial"),         # cell -> neutral, no advance
    (5,     0.08,   "partial"),
    (6,     0.12,   "partial_advance"), # cell -> neutral + attacker advances onto it
    (7,     0.13,   "full"),            # defense -1; capture if 0
    (8,     0.13,   "full"),
    (9,     0.11,   "critical"),        # defense -1; capture if 0; +2 bonus score
]
 
# Collapsed by outcome tag for easy probability lookup (used by search)
OUTCOME_PROBS: dict[str, float] = {}
for _, prob, tag in DIE_OUTCOMES:
    OUTCOME_PROBS[tag] = OUTCOME_PROBS.get(tag, 0.0) + prob
 
# Verify they sum to 1.0
"""assert: Crashes the program if the condition is False, with the given error message."""
assert abs(sum(OUTCOME_PROBS.values()) - 1.0) < 1e-9, "Die probabilities must sum to 1.0"
 
"""
─────────────────────────────────────────────
 3. MINEFIELD EVENT TABLE
─────────────────────────────────────────────
"""
 
MINEFIELD_OUTCOMES = [
    # outcome_tag         probability
    ("safe",              0.40),   # no effect
    ("energy_drain",      0.30),   # agent loses 3 energy
    ("unit_disabled",     0.20),   # this unit can't act for 2 turns
    ("detonation",        0.10),   # cell -> obstacle; agent loses 5 energy
]
MINEFIELD_PROBS: dict[str, float] = {tag: p for tag, p in MINEFIELD_OUTCOMES}
 
"""
─────────────────────────────────────────────
 4. ACTION GENERATOR - what moves are legal
─────────────────────────────────────────────
"""

def get_legal_actions(state: GameState, agent_id: AgentID) -> list[list[Action]]:
    """
    Returns a list of action COMBINATIONS for the agent this turn.
    Each element is a list of Actions (one per active unit).
    """
    agent = state.get_agent(agent_id)
 
    # Collect per-unit action lists
    per_unit_actions: list[list[Action]] = []
    for unit in agent.units:
        unit_actions = _get_unit_actions(state, agent, unit)
        per_unit_actions.append(unit_actions)
 
    # Cross product: combine one action per unit
    combos = _cross_product(per_unit_actions)
    return combos
 
 
def _get_unit_actions(state: GameState, agent: AgentState, unit: Unit) -> list[Action]:
    """Legal actions for a single unit."""
    actions = []
    aid = agent.agent_id
 
    # Always legal: Wait
    actions.append(Action(ActionType.WAIT, unit.unit_id, aid))
 
    # No energy or disabled -> only Wait
    if agent.energy <= 0 or not unit.can_act():
        return actions
 
    board = state.board
    r, c = unit.row, unit.col
 
    for nr, nc in board.adjacent_cells(r, c):
        cell = board.get_cell(nr, nc)
 
        # MOVE: to any passable cell
        if cell.is_passable():
            actions.append(Action(ActionType.MOVE, unit.unit_id, aid, nr, nc))
 
        # ATTACK: opponent-owned adjacent cell (without moving)
        if cell.owner is not None and cell.owner != aid:
            actions.append(Action(ActionType.ATTACK, unit.unit_id, aid, nr, nc))
 
        # FORTIFY: own adjacent cell (defense < 3)
        if cell.owner == aid and cell.defense < 3:
            actions.append(Action(ActionType.FORTIFY, unit.unit_id, aid, nr, nc))
 
    return actions
 
 
def _cross_product(per_unit: list[list[Action]]) -> list[list[Action]]:
    """Cartesian product of per-unit action lists."""
    if not per_unit:
        return [[]]
    result = [[]]
    for unit_actions in per_unit:
        result = [combo + [act] for combo in result for act in unit_actions]
    return result
 

"""
─────────────────────────────────────────────
 5. ACTION EXECUTOR - apply actions to state
─────────────────────────────────────────────
"""
 
@dataclass
class ActionResult:
    """Holds the outcome of executing a set of actions."""
    log: list[str] = []
    die_outcome: Optional[str] = None     # last combat outcome tag
    minefield_outcome: Optional[str] = None
 
    def add(self, msg: str):
        self.log.append(msg)
 
    def __repr__(self):
        return "\n".join(self.log)
 
 
def execute_actions(state: GameState, 		# GameState to mutate
                    agent_id: AgentID,		# which agent is acting
                    actions: list[Action],	# list of Action objects (one per unit)
                    die_outcome: Optional[str] = None) -> ActionResult:		# if provided, use this combat outcome instead of rolling
                     														# (used by search to enumerate branches deterministically)
 
    """
    Apply a list of actions (one per unit) to the state IN PLACE.
    Returns:
        ActionResult with a log of what happened.
    """
    result = ActionResult()
    agent  = state.get_agent(agent_id)
 
    for action in actions:
        unit = _find_unit(agent, action.unit_id)
        if unit is None:
            result.add(f"[WARN] Unit {action.unit_id} not found for {agent_id.value}")
            continue
 
        if action.action_type == ActionType.WAIT:
            _do_wait(state, agent, unit, result)
 
        elif action.action_type == ActionType.MOVE:
            _do_move(state, agent, unit, action.target_row, action.target_col,
                     die_outcome, result)
 
        elif action.action_type == ActionType.ATTACK:
            _do_attack(state, agent, unit, action.target_row, action.target_col,
                       die_outcome, result)
 
        elif action.action_type == ActionType.FORTIFY:
            _do_fortify(state, agent, unit, action.target_row, action.target_col, result)
 
    return result
 
 
# ─────────────────────────────────────────────
# 6. INDIVIDUAL ACTION IMPLEMENTATIONS
# ─────────────────────────────────────────────
 
def _find_unit(agent: AgentState, unit_id: int) -> Optional[Unit]:
    for u in agent.units:
        if u.unit_id == unit_id:
            return u
    return None
 
 
def _do_wait(state: GameState, agent: AgentState, unit: Unit, result: ActionResult):
    """Wait costs 1 energy, does nothing else."""
    agent.spend_energy(1)
    result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] Waits. Energy now {agent.energy}.")
 
 
def _do_move(state: GameState, agent: AgentState, unit: Unit,
             tr: int, tc: int, die_outcome: Optional[str],
             result: ActionResult):
    """
    Move unit to (tr, tc).
    - Empty/Minefield cell: capture immediately (if empty) or trigger mine event
    - Opponent cell: triggers combat (same as Attack but unit moves if successful)
    """
    board = state.board
    cell  = board.get_cell(tr, tc)
 
    if not agent.spend_energy(1):
        result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] has no energy - Wait forced.")
        return
 
    # Move onto empty cell -> instant capture
    if cell.cell_type == CellType.EMPTY and cell.owner is None:
        unit.row, unit.col = tr, tc
        cell.owner = agent.agent_id
        result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] Moves to ({tr},{tc}) - captured empty cell.")
 
    # Move onto own cell -> just reposition
    elif cell.owner == agent.agent_id:
        unit.row, unit.col = tr, tc
        result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] Moves to own cell ({tr},{tc}).")
 
    # Move onto opponent cell -> combat (attacker advances on partial_advance/capture)
    elif cell.owner is not None and cell.owner != agent.agent_id:
        outcome = die_outcome or _roll_die()
        result.die_outcome = outcome
        _resolve_combat(state, agent, unit, tr, tc, outcome, move_attack=True, result=result)
 
    # Move onto Minefield
    elif cell.cell_type == CellType.MINEFIELD:
        unit.row, unit.col = tr, tc
        mine_outcome = _roll_minefield()
        result.minefield_outcome = mine_outcome
        _resolve_minefield(state, agent, unit, tr, tc, mine_outcome, result)
 
    # Move onto Fortress (unowned)
    elif cell.cell_type == CellType.FORTRESS and cell.owner is None:
        unit.row, unit.col = tr, tc
        cell.owner = agent.agent_id
        result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] Captures unowned Fortress at ({tr},{tc}).")
 
 
def _do_attack(state: GameState, agent: AgentState, unit: Unit,
               tr: int, tc: int, die_outcome: Optional[str],
               result: ActionResult):
    """Attack adjacent opponent cell without moving."""
    board = state.board
    cell  = board.get_cell(tr, tc)
 
    if not agent.spend_energy(1):
        result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] has no energy - Wait forced.")
        return
 
    if cell.owner is None or cell.owner == agent.agent_id:
        result.add(f"[WARN] ({tr},{tc}) is not an opponent cell - Attack invalid.")
        return
 
    outcome = die_outcome or _roll_die()
    result.die_outcome = outcome
    _resolve_combat(state, agent, unit, tr, tc, outcome, move_attack=False, result=result)
 
 
def _do_fortify(state: GameState, agent: AgentState, unit: Unit,
                tr: int, tc: int, result: ActionResult):
    """Increase defense of own adjacent cell by 1 (max 3)."""
    board = state.board
    cell  = board.get_cell(tr, tc)
 
    if not agent.spend_energy(1):
        result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] has no energy - Wait forced.")
        return
 
    if cell.owner != agent.agent_id:
        result.add(f"[WARN] ({tr},{tc}) not owned by {agent.agent_id.value} - Fortify invalid.")
        return
 
    if cell.defense >= 3:
        result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] Fortify at ({tr},{tc}) - already at max defense 3.")
        return
 
    cell.defense += 1
    result.add(f"{agent.agent_id.value}[unit{unit.unit_id}] Fortifies ({tr},{tc}) - defense now {cell.defense}.")
 
 
# ─────────────────────────────────────────────
# 7. COMBAT RESOLUTION
# ─────────────────────────────────────────────
 
def _resolve_combat(state: GameState, agent: AgentState, unit: Unit,
                    tr: int, tc: int, outcome: str,
                    move_attack: bool, result: ActionResult):
    """
    Apply a combat outcome to the target cell.
 
    outcome tags:
        fail_energy     -> attack fails; attacker loses 1 extra energy
        fail            -> attack fails; no extra penalty
        partial         -> cell becomes neutral
        partial_advance -> cell becomes neutral; attacker moves onto it
        full            -> defense -1; capture if 0
        critical        -> defense -1; capture if 0; +2 bonus score
    """
    board     = state.board
    cell      = board.get_cell(tr, tc)
    defender_id = cell.owner
    defender  = state.get_agent(defender_id) if defender_id else None
 
    if outcome in ("fail_energy", "fail"):
        if outcome == "fail_energy":
            agent.spend_energy(1)   # extra energy loss on top of action cost
            result.add(f"  Combat FAIL (energy penalty): {agent.agent_id.value} loses 1 extra energy -> {agent.energy} left.")
        else:
            result.add(f"  Combat FAIL: {agent.agent_id.value} attack on ({tr},{tc}) repelled.")
 
    elif outcome in ("partial", "partial_advance"):
        old_owner = cell.owner
        cell.reset_to_empty()
        result.add(f"  Combat PARTIAL: ({tr},{tc}) becomes neutral (was {old_owner.value if old_owner else '?'}).")
        if outcome == "partial_advance" and move_attack:
            unit.row, unit.col = tr, tc
            result.add(f"  Attacker {agent.agent_id.value}[unit{unit.unit_id}] advances onto ({tr},{tc}).")
 
    elif outcome in ("full", "critical"):
        cell.defense -= 1
        result.add(f"  Combat {'FULL' if outcome=='full' else 'CRITICAL'}: ({tr},{tc}) defense -> {cell.defense}.")
 
        if cell.defense <= 0:
            # Capture
            old_owner = cell.owner
            cell.owner   = agent.agent_id
            cell.defense = 1  # reset defense for new owner (Fortress keeps is_fortress)
            result.add(f"  CAPTURED ({tr},{tc}) from {old_owner.value if old_owner else '?'} by {agent.agent_id.value}!")
 
            if move_attack:
                unit.row, unit.col = tr, tc
 
            if outcome == "critical":
                agent.add_score(2)
                result.add(f"  Critical bonus: +2 score to {agent.agent_id.value} -> {agent.score}.")
 
            # Check if defender is eliminated (no units and no owned cells)
            if defender:
                _check_elimination(state, defender_id, result)
 
 
def _check_elimination(state: GameState, agent_id: AgentID, result: ActionResult):
    """Eliminate agent if they have no units left."""
    agent = state.get_agent(agent_id)
    if len(agent.units) == 0:
        agent.is_eliminated = True
        # Award +5 to whoever eliminated them (last attacker implicit via context)
        result.add(f"  {agent_id.value} has been ELIMINATED!")
 
 




















if __name__ == "__main__":
    # Simulate parsing the example board from the assignment
    grid_chars = [
        list("........"),
        list(".X..F..."),
        list("....X..."),
        list("..M....."),
        list(".......M"),
        list("...X...."),
        list("..F..X.."),
        list("........"),
    ]
    start_positions = {
        AgentID.A: (0, 0),
        AgentID.B: (0, 7),
        AgentID.C: (7, 3),
    }
 
    state = build_initial_state(
        rows=8, cols=8, max_rounds=30,
        grid_chars=grid_chars,
        start_positions=start_positions
    )
 
    print(state)
    print()
    print("--- Cell checks ---")
    print("(0,0):", state.board.get_cell(0,0))
    print("(1,1):", state.board.get_cell(1,1))   # obstacle
    print("(1,4):", state.board.get_cell(1,4))   # fortress
    print("(3,2):", state.board.get_cell(3,2))   # minefield
    print()
    print("--- Agent checks ---")
    for aid in AgentID:
        agent = state.get_agent(aid)
        print(agent)
        for u in agent.units:
            print(" ", u)
    print()
    print("Non-obstacle cells:", state.board.total_non_obstacle_cells())
    print("Terminal?", state.is_terminal())
    print("Observable cells for A (full):", len(state.get_observable_cells(AgentID.A, -1)))
    print("Observable cells for C (r=3):", len(state.get_observable_cells(AgentID.C, 3)))