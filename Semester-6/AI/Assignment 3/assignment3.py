from enum import Enum, auto
from dataclasses import dataclass, field
from typing import Optional
import copy, random, math, time, os, sys, threading
import dearpygui.dearpygui as dpg

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
 
        # All remaining agents have 0 energy
        if all(self.get_agent(aid).energy == 0 for aid in active):
            return True

        return False
 
    def winner(self) -> Optional[AgentID]:
        """Determine winner based on highest score."""
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
        Create a fast deep copy of the game state.
        Used by Expectiminimax to explore branches without mutating the real state.
        """
        new_board = Board(self.board.rows, self.board.cols)
        for r in range(self.board.rows):
            for c in range(self.board.cols):
                cell = self.board.grid[r][c]
                new_board.grid[r][c] = Cell(cell.cell_type, cell.owner, cell.defense, cell.is_fortress, cell.temp_fortress_rounds)
        
        new_agents = {}
        for aid, agent in self.agents.items():
            new_units = [Unit(u.unit_id, u.owner, u.row, u.col, u.disabled_turns, u.is_bonus, u.bonus_turns) for u in agent.units]
            new_agent = AgentState(agent.agent_id, agent.energy, agent.score, new_units, agent.is_eliminated)
            if hasattr(agent, '_bonus_awarded'):
                new_agent._bonus_awarded = agent._bonus_awarded
            new_agents[aid] = new_agent
            
        new_state = GameState(
            board=new_board,
            agents=new_agents,
            round_number=self.round_number,
            max_rounds=self.max_rounds,
            current_turn=self.current_turn,
            move_number=self.move_number,
            fog_active=self.fog_active,
            turn_order=list(self.turn_order)
        )
        return new_state
 
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
    
    # LIMIT to top 10 actions to prevent combinatorial explosion in Expectiminimax
    # Since actions are pre-sorted by priority, the first combinations are generally the best.
    if len(combos) > 10:
        combos = combos[:10]
        
    return combos
 
 
def _get_unit_actions(state: GameState, agent: AgentState, unit: Unit) -> list[Action]:
    """Legal actions for a single unit."""
    actions = []
    aid = agent.agent_id

    # Always legal: Wait
    wait_act = Action(ActionType.WAIT, unit.unit_id, aid)

    # No energy or disabled -> only Wait
    if agent.energy <= 0 or not unit.can_act():
        return [wait_act]

    board = state.board
    r, c = unit.row, unit.col

    attacks = []
    moves_unowned = []
    fortifies = []
    moves_owned = []

    for nr, nc in board.adjacent_cells(r, c):
        cell = board.get_cell(nr, nc)

        # ATTACK: opponent-owned adjacent cell (without moving)
        if cell.owner is not None and cell.owner != aid:
            attacks.append(Action(ActionType.ATTACK, unit.unit_id, aid, nr, nc))

        # MOVE: to any passable cell
        if cell.is_passable():
            if cell.owner != aid:
                moves_unowned.append(Action(ActionType.MOVE, unit.unit_id, aid, nr, nc))
            else:
                moves_owned.append(Action(ActionType.MOVE, unit.unit_id, aid, nr, nc))

        # FORTIFY: own adjacent cell (defense < 3)
        if cell.owner == aid and cell.defense < 3:
            fortifies.append(Action(ActionType.FORTIFY, unit.unit_id, aid, nr, nc))

    # Priority sort: Attacks > Moves to unowned > Fortifies > Moves to owned > Wait
    actions = attacks + moves_unowned + fortifies + moves_owned + [wait_act]
    
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
    log: list[str] = field(default_factory=list)  
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
 
 
"""
─────────────────────────────────────────────
 6. INDIVIDUAL ACTION IMPLEMENTATIONS
─────────────────────────────────────────────
"""
 
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
 

"""
─────────────────────────────────────────────
 7. COMBAT RESOLUTION
─────────────────────────────────────────────
"""
 
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
 

"""
─────────────────────────────────────────────
 8. MINEFIELD RESOLUTION
─────────────────────────────────────────────
"""
 
def _resolve_minefield(state: GameState, agent: AgentState, unit: Unit,
                        tr: int, tc: int, outcome: str, result: ActionResult):
    """Apply minefield event outcome."""
    board = state.board
    cell  = board.get_cell(tr, tc)
 
    if outcome == "safe":
        result.add(f"  Minefield at ({tr},{tc}): Safe passage.")
 
    elif outcome == "energy_drain":
        lost = min(3, agent.energy)
        agent.energy -= lost
        result.add(f"  Minefield at ({tr},{tc}): Energy drain - {agent.agent_id.value} loses {lost} energy -> {agent.energy}.")
 
    elif outcome == "unit_disabled":
        unit.disabled_turns = 2
        result.add(f"  Minefield at ({tr},{tc}): {agent.agent_id.value}[unit{unit.unit_id}] disabled for 2 turns.")
 
    elif outcome == "detonation":
        lost = min(5, agent.energy)
        agent.energy -= lost
        cell.cell_type = CellType.OBSTACLE
        cell.owner     = None
        result.add(f"  Minefield at ({tr},{tc}): DETONATION - becomes Obstacle; {agent.agent_id.value} loses {lost} energy -> {agent.energy}.")
 
 
"""
─────────────────────────────────────────────
 9. DIE ROLLERS
─────────────────────────────────────────────
"""
 
def _roll_die() -> str:
    """Roll the 9-sided die; return the outcome tag."""
    r = random.random()
    cumulative = 0.0
    for _, prob, tag in DIE_OUTCOMES:
        cumulative += prob
        if r < cumulative:
            return tag
    return DIE_OUTCOMES[-1][2]  # fallback
 
 
def _roll_minefield() -> str:
    """Roll the minefield 4-sided event."""
    r = random.random()
    cumulative = 0.0
    for tag, prob in MINEFIELD_OUTCOMES:
        cumulative += prob
        if r < cumulative:
            return tag
    return MINEFIELD_OUTCOMES[-1][0]
 
 
"""
─────────────────────────────────────────────
 10. TURN TICK - housekeeping after each agent's turn
─────────────────────────────────────────────
"""
 
def tick_units(state: GameState, agent_id: AgentID):
    """
    Call after an agent completes their turn.
    - Decrements disabled_turns on each unit
    - Removes bonus units whose lifetime expired
    """
    agent = state.get_agent(agent_id)
    to_remove = []
    for unit in agent.units:
        unit.tick_disabled()
        if unit.is_bonus and unit.tick_bonus():
            to_remove.append(unit)
    for u in to_remove:
        agent.units.remove(u)
 
 
def award_elimination_bonus(state: GameState, attacker_id: AgentID, result: ActionResult):
    """
    If any opponent was just eliminated, award +5 to the attacker.
    Call after execute_actions to detect newly eliminated agents.
    """
    for aid in AgentID:
        if aid == attacker_id:
            continue
        agent = state.get_agent(aid)
        if agent.is_eliminated and not getattr(agent, '_bonus_awarded', False):
            state.get_agent(attacker_id).add_score(5)
            agent._bonus_awarded = True
            result.add(f"  Elimination bonus: +5 to {attacker_id.value}!")
 


"""
3. Chance Nodes - Environmental Events
============================================
Handles the 4 environmental events drawn at the start of each round
(before Agent A moves), each with probability 0.25:
"""

# ─────────────────────────────────────────────
# 1. ENVIRONMENTAL EVENT TABLE (configurable)
# ─────────────────────────────────────────────
 
ENV_EVENTS = [
    # event tag            probability
    ("supply_drop",        0.25),
    ("earthquake",         0.25),
    ("reinforcement",      0.25),
    ("fog_of_war",         0.25),
]
 
ENV_EVENT_PROBS: dict[str, float] = {tag: p for tag, p in ENV_EVENTS}
 
# Verify sum
assert abs(sum(ENV_EVENT_PROBS.values()) - 1.0) < 1e-9, "Env event probs must sum to 1.0"
 
 
# ─────────────────────────────────────────────
# 2. EVENT RESULT - log of what happened
# ─────────────────────────────────────────────
 
@dataclass
class EventResult:
    event_tag : str
    log       : list[str]
 
    def __repr__(self):
        return f"[{self.event_tag}] " + " | ".join(self.log)
 
 
# ─────────────────────────────────────────────
# 3. ENVIRONMENTAL EVENT DISPATCHER
# ─────────────────────────────────────────────
 
def draw_environmental_event(forced: Optional[str] = None) -> str:
    """
    Draw one environmental event at random (uniform 0.25 each).
    Pass forced= to override (used by search to enumerate branches).
    """
    if forced:
        return forced
    r = random.random()
    cumulative = 0.0
    for tag, prob in ENV_EVENTS:
        cumulative += prob
        if r < cumulative:
            return tag
    return ENV_EVENTS[-1][0]
 
 
def apply_environmental_event(state: GameState,
                               event_tag: str) -> EventResult:
    """
    Apply the given environmental event to the state IN PLACE.
    Returns an EventResult describing what happened.
    """
    result = EventResult(event_tag=event_tag, log=[])
 
    if event_tag == "supply_drop":
        _apply_supply_drop(state, result)
 
    elif event_tag == "earthquake":
        _apply_earthquake(state, result)
 
    elif event_tag == "reinforcement":
        _apply_reinforcement(state, result)
 
    elif event_tag == "fog_of_war":
        _apply_fog_of_war(state, result)
 
    return result 


# ─────────────────────────────────────────────
# 4. INDIVIDUAL EVENT IMPLEMENTATIONS
# ─────────────────────────────────────────────
 
def _apply_supply_drop(state: GameState, result: EventResult):
    """
    Supply Drop: a random empty cell becomes a Fortress for 3 rounds.
    After 3 rounds it reverts to Empty.
    """
    board = state.board
    candidates = [
        (r, c)
        for r in range(board.rows)
        for c in range(board.cols)
        if board.get_cell(r, c).cell_type == CellType.EMPTY
        and board.get_cell(r, c).owner is None
    ]
 
    if not candidates:
        result.log.append("Supply Drop: no empty cells available - skipped.")
        return
 
    r, c = random.choice(candidates)
    cell = board.get_cell(r, c)
    cell.cell_type           = CellType.FORTRESS
    cell.is_fortress         = True
    cell.defense             = 2
    cell.temp_fortress_rounds = 3
 
    result.log.append(f"Supply Drop: ({r},{c}) becomes a temp Fortress for 3 rounds.")
 
 
def _apply_earthquake(state: GameState, result: EventResult):
    """
    Earthquake: one randomly selected owned cell loses 1 defense.
    If defense reaches 0 the cell reverts to Empty (no capture - just abandoned).
    """
    board = state.board
    owned_cells = [
        (r, c)
        for r in range(board.rows)
        for c in range(board.cols)
        if board.get_cell(r, c).owner is not None
    ]
 
    if not owned_cells:
        result.log.append("Earthquake: no owned cells - skipped.")
        return
 
    r, c = random.choice(owned_cells)
    cell = board.get_cell(r, c)
    old_owner = cell.owner
    cell.defense -= 1
 
    if cell.defense <= 0:
        cell.reset_to_empty()
        result.log.append(
            f"Earthquake: ({r},{c}) owned by {old_owner.value} lost its last defense - reverts to Empty."
        )
    else:
        result.log.append(
            f"Earthquake: ({r},{c}) owned by {old_owner.value} - defense reduced to {cell.defense}."
        )
 
 
def _apply_reinforcement(state: GameState, result: EventResult):
    """
    Reinforcement: the agent with the lowest current score gets a bonus unit
    placed on an empty adjacent cell for 2 turns.
 
    Placement priority:
        1. Adjacent empty cell to any existing unit
        2. Nearest owned cell (if no empty adjacent)
    """
    board  = state.board
    active = [aid for aid in AgentID if not state.get_agent(aid).is_eliminated]
 
    if not active:
        result.log.append("Reinforcement: no active agents - skipped.")
        return
 
    # Find agent with lowest score
    weakest_id = min(active, key=lambda aid: state.get_agent(aid).score)
    agent      = state.get_agent(weakest_id)
 
    # Find placement cell
    placement  = _find_reinforcement_placement(state, agent)
 
    if placement is None:
        result.log.append(
            f"Reinforcement: {weakest_id.value} is weakest but no valid placement found - skipped."
        )
        return
 
    pr, pc = placement
    new_unit_id = max((u.unit_id for u in agent.units), default=-1) + 1
    bonus_unit  = Unit(
        unit_id     = new_unit_id,
        owner       = weakest_id,
        row         = pr,
        col         = pc,
        is_bonus    = True,
        bonus_turns = 2,
    )
    agent.units.append(bonus_unit)
 
    result.log.append(
        f"Reinforcement: {weakest_id.value} (score={agent.score}) gets bonus unit {new_unit_id} "
        f"at ({pr},{pc}) for 2 turns."
    )
 
 
def _find_reinforcement_placement(state: GameState,
                                   agent: AgentState) -> Optional[tuple[int, int]]:
    """Find best placement for the bonus unit."""
    board = state.board
 
    # 1. Look for empty adjacent cell near any existing unit
    for unit in agent.units:
        for nr, nc in board.adjacent_cells(unit.row, unit.col):
            cell = board.get_cell(nr, nc)
            if cell.cell_type == CellType.EMPTY and cell.owner is None:
                return (nr, nc)
 
    # 2. Fall back to nearest owned cell
    for r in range(board.rows):
        for c in range(board.cols):
            cell = board.get_cell(r, c)
            if cell.owner == agent.agent_id:
                return (r, c)
 
    return None
 
 
def _apply_fog_of_war(state: GameState, result: EventResult):
    """
    Fog of War: each agent's observable range is halved (rounded down) for THIS TURN only.
    """
    state.fog_active = True
    result.log.append(
        "Fog of War: all agents' observable range halved for this turn."
    )
 
 
# ─────────────────────────────────────────────
# 5. ROUND HOUSEKEEPING
# ─────────────────────────────────────────────
 
def tick_temp_fortresses(state: GameState) -> list[str]:
    """
    Decrement countdown on all temporary Supply Drop fortresses.
    Reverts any that have expired back to Empty.
    Called once per round (after all agents move).
    Returns a log of what expired.
    """
    log = []
    board = state.board
    for r in range(board.rows):
        for c in range(board.cols):
            cell = board.get_cell(r, c)
            if cell.temp_fortress_rounds > 0:
                cell.temp_fortress_rounds -= 1
                if cell.temp_fortress_rounds == 0:
                    old_owner = cell.owner
                    cell.reset_to_empty()
                    log.append(
                        f"Supply Drop expired: ({r},{c}) reverts to Empty "
                        f"(was owned by {old_owner.value if old_owner else 'nobody'})."
                    )
    return log
 
 
def tick_bonus_units(state: GameState) -> list[str]:
    """
    Decrement countdown on all bonus units across all agents.
    Removes expired bonus units.
    Called once per round.
    Returns a log of removals.
    """
    log = []
    for aid in AgentID:
        agent = state.get_agent(aid)
        to_remove = []
        for unit in agent.units:
            if unit.is_bonus:
                unit.bonus_turns -= 1
                if unit.bonus_turns <= 0:
                    to_remove.append(unit)
        for u in to_remove:
            agent.units.remove(u)
            log.append(f"Bonus unit {u.unit_id} of {aid.value} expired and removed.")
    return log
 
 
def clear_fog(state: GameState):
    """Reset fog flag at the end of the turn it was applied."""
    state.fog_active = False
 
 
def get_effective_radius(agent_id: AgentID, state: GameState) -> int:
    """
    Return the effective observable radius for an agent,
    accounting for Fog of War halving.
 
    Radius conventions:
        -1  -> full board (Expert, no fog)
        ≥0  -> Manhattan distance radius
    """
    BASE_RADIUS = {
        AgentID.A: -1,   # full board
        AgentID.B:  5,
        AgentID.C:  3,
    }
    radius = BASE_RADIUS[agent_id]
 
    if state.fog_active:
        if radius < 0:
            # Full board halved -> treat as large finite radius
            radius = max(0, (max(state.board.rows, state.board.cols)) // 2)
        else:
            radius = radius // 2  # rounded down per rules
 
    return radius
 
 
def score_all_agents(state: GameState) -> list[str]:
    """
    Award per-round points to every active agent for cells they own.
    Call once per round.
    Returns a log of points awarded.
    """
    log = []
    for aid in AgentID:
        agent = state.get_agent(aid)
        if agent.is_eliminated:
            continue
        earned = 0
        for row in state.board.grid:
            for cell in row:
                if cell.owner == aid:
                    earned += cell.score_value()
        agent.add_score(earned)
        log.append(f"  {aid.value} earns {earned} pts this round -> total {agent.score}.")
    return log
 


"""
Step 4: Expectiminimax with Alpha-Beta Pruning
===============================================
Core AI search for all three agents.
"""

# ─────────────────────────────────────────────
# 1. AGENT CONFIGURATION (structural asymmetry)
#    Everything flows through these config objects.
# ─────────────────────────────────────────────
 
@dataclass
class AgentConfig:
    """
    Structural definition of an agent's cognitive capability.
    The search engine reads ONLY these fields - never agent ID directly.
    """
    agent_id         : AgentID
    max_depth        : int
    obs_radius       : int          # -1 = full board
    chance_branches  : list[str]    # the outcome tags to evaluate at chance nodes
    eval_factors     : int          # 1=greedy, 3=intermediate, 5=full
    use_transposition: bool
 
 
# Top-2 most probable chance branches for Novice (by probability)
_sorted_outcomes = sorted(OUTCOME_PROBS.items(), key=lambda x: -x[1])
NOVICE_BRANCHES  = [tag for tag, _ in _sorted_outcomes[:2]]   # ["full", "fail_energy"]
ALL_BRANCHES     = list(OUTCOME_PROBS.keys())                  # all 6 collapsed tags
 
AGENT_CONFIGS: dict[AgentID, AgentConfig] = {
    AgentID.A: AgentConfig(
        agent_id          = AgentID.A,
        max_depth         = 3,
        obs_radius        = -1,
        chance_branches   = ALL_BRANCHES,
        eval_factors      = 5,
        use_transposition = True,
    ),
    AgentID.B: AgentConfig(
        agent_id          = AgentID.B,
        max_depth         = 2,
        obs_radius        = 5,
        chance_branches   = ALL_BRANCHES,
        eval_factors      = 3,
        use_transposition = False,
    ),
    AgentID.C: AgentConfig(
        agent_id          = AgentID.C,
        max_depth         = 1,
        obs_radius        = 3,
        chance_branches   = NOVICE_BRANCHES,
        eval_factors      = 1,
        use_transposition = False,
    ),
}
 
 
# ─────────────────────────────────────────────
# 2. NODE STATISTICS (per move reporting)
# ─────────────────────────────────────────────
 
@dataclass
class SearchStats:
    """Tracks node counts for per-move reporting (Section 6.2)."""
    nodes_explored : int = 0
    nodes_pruned   : int = 0
    start_time     : float = field(default_factory=time.time)
 
    def pruning_pct(self) -> float:
        total = self.nodes_explored + self.nodes_pruned
        return (self.nodes_pruned / total * 100) if total > 0 else 0.0
 
    def elapsed_ms(self) -> float:
        return (time.time() - self.start_time) * 1000
 
 
# ─────────────────────────────────────────────
# 3. EVALUATION FUNCTIONS
#    Each agent uses a different subset of factors.
#    eval_factors controls which factors are active.
# ─────────────────────────────────────────────
 
def evaluate(state: GameState, agent_id: AgentID, eval_factors: int) -> float:
    """
    Estimate board utility for agent_id.
 
    eval_factors:
        1 -> greedy: score differential only          (Novice)
        3 -> score diff + territory + positional      (Intermediate)
        5 -> all 5 factors                            (Expert)
 
    All factors return values in a normalised range so weights are comparable.
    """
    agent    = state.get_agent(agent_id)
    board    = state.board
    opponents = [aid for aid in AgentID if aid != agent_id
                 and not state.get_agent(aid).is_eliminated]
 
    # ── Factor 1: Score differential (all agents) ──────────────────────────
    # Directly measures winning margin. Primary signal for all agents.
    my_score  = agent.score
    opp_scores = [state.get_agent(o).score for o in opponents]
    avg_opp_score = (sum(opp_scores) / len(opp_scores)) if opp_scores else 0
    f1_score_diff = my_score - avg_opp_score
 
    if eval_factors == 1:
        my_cells = board.count_owned(agent_id)
        opp_cells = sum(board.count_owned(o) for o in opponents)
        return float(f1_score_diff + 0.5 * (my_cells - opp_cells))
 
    # ── Factor 2: Territory control ────────────────────────────────────────
    # Owning more cells = more points per round = compounding advantage.
    # Fortress cells weighted 3x (they yield +3/round vs +1).
    my_cells = 0
    my_fortress = 0
    for r in range(board.rows):
        for c in range(board.cols):
            cell = board.get_cell(r, c)
            if cell.owner == agent_id:
                my_cells += 1
                if cell.is_fortress:
                    my_fortress += 1
 
    opp_cells = sum(board.count_owned(o) for o in opponents)
    f2_territory = (my_cells + 3 * my_fortress) - opp_cells
 
    # ── Factor 3: Positional advantage ────────────────────────────────────
    # Units close to Fortresses can capture them quickly.
    # We reward low average Manhattan distance from units to nearest fortress.
    fortress_cells = [
        (r, c) for r in range(board.rows) for c in range(board.cols)
        if board.get_cell(r, c).is_fortress and board.get_cell(r, c).owner != agent_id
    ]
 
    f3_position = 0.0
    if fortress_cells and agent.units:
        total_dist = 0
        for unit in agent.units:
            min_dist = min(
                abs(unit.row - fr) + abs(unit.col - fc)
                for fr, fc in fortress_cells
            )
            total_dist += min_dist
        avg_dist = total_dist / len(agent.units)
        # Closer = better -> negate distance, normalise by board size
        max_dist = board.rows + board.cols
        f3_position = (max_dist - avg_dist) / max_dist * 10
 
    if eval_factors == 3:
        return float(f1_score_diff * 1.0 +
                     f2_territory  * 2.0 +
                     f3_position   * 1.5)
 
    # ── Factor 4: Threat assessment ────────────────────────────────────────
    # Opponent units adjacent to owned cells threaten captures next turn.
    # Penalty for each such threat - defensive awareness.
    threat_count = 0
    for r in range(board.rows):
        for c in range(board.cols):
            cell = board.get_cell(r, c)
            if cell.owner == agent_id:
                for nr, nc in board.adjacent_cells(r, c):
                    # Check if any opponent unit is sitting there
                    for opp in opponents:
                        for u in state.get_agent(opp).units:
                            if u.row == nr and u.col == nc:
                                threat_count += 1
 
    f4_threat = -threat_count  # negative: more threats = worse
 
    # ── Factor 5: Energy advantage ─────────────────────────────────────────
    # Energy = future action budget. Running low = forced to Wait.
    opp_energies = [state.get_agent(o).energy for o in opponents]
    avg_opp_energy = (sum(opp_energies) / len(opp_energies)) if opp_energies else 0
    f5_energy = agent.energy - avg_opp_energy
 
    # Full weighted combination
    return float(
        f1_score_diff * 1.0 +
        f2_territory  * 2.0 +
        f3_position   * 1.5 +
        f4_threat     * 1.0 +
        f5_energy     * 0.5
    )
 


# ─────────────────────────────────────────────
# 4. TRANSPOSITION TABLE
# ─────────────────────────────────────────────
 
class TranspositionTable:
    """
    Simple hash-map for Expert agent.
    Stores (value, depth) so shallower cached results aren't used for deeper searches.
    """
    def __init__(self):
        self._table: dict[int, tuple[float, int]] = {}
 
    def _hash(self, state: GameState, agent_id: AgentID, depth: int) -> int:
        """
        Lightweight state hash. Uses board ownership layout + agent energies/scores.
        """
        board = state.board
        key_parts = []
        for r in range(board.rows):
            for c in range(board.cols):
                cell = board.get_cell(r, c)
                key_parts.append(
                    (cell.owner.value if cell.owner else '_',
                     cell.defense,
                     cell.cell_type.value)
                )
        for aid in AgentID:
            ag = state.get_agent(aid)
            key_parts.append((ag.energy, ag.score, ag.is_eliminated))
        key_parts.append((agent_id.value, depth))
        return hash(tuple(key_parts))
 
    def get(self, state: GameState, agent_id: AgentID,
            depth: int) -> Optional[float]:
        h = self._hash(state, agent_id, depth)
        entry = self._table.get(h)
        if entry and entry[1] >= depth:
            return entry[0]
        return None
 
    def put(self, state: GameState, agent_id: AgentID,
            depth: int, value: float):
        h = self._hash(state, agent_id, depth)
        self._table[h] = (value, depth)
 
    def clear(self):
        self._table.clear()
 
    def __len__(self):
        return len(self._table)
 
 
# One global transposition table for the Expert agent
_expert_tt = TranspositionTable()
 
 
# ─────────────────────────────────────────────
# 5. EXPECTIMINIMAX WITH ALPHA-BETA
# ─────────────────────────────────────────────
 
def expectiminimax(
    state      : GameState,      # current game state (will be deep-copied for each branch)
    agent_id   : AgentID,        # the agent whose turn this is
    root_agent : AgentID,        # the agent we're computing utility FOR
    depth      : int,            # remaining depth
    alpha      : float,          # alpha bound
    beta       : float,          # beta bound
    config     : AgentConfig,    # root agent's config (controls depth limit etc.)
    stats      : SearchStats,    # mutable stats object to track nodes explored/pruned
    is_max     : bool = True,    # True if this is a MAX node (root_agent's turn)
) -> float:
    """
    Expectiminimax search.
    Returns:
        Expected utility value from root_agent's perspective.
    """
    stats.nodes_explored += 1
 
    # ── Terminal / cutoff ──────────────────────────────────────────────────
    if state.is_terminal() or depth == 0:
        return evaluate(state, root_agent, config.eval_factors)
 
    # ── Transposition table lookup (Expert only) ───────────────────────────
    if config.use_transposition:
        cached = _expert_tt.get(state, root_agent, depth)
        if cached is not None:
            return cached
 
    # ── MAX node (root agent's turn) ───────────────────────────────────────
    if is_max:
        best_val = -math.inf
        actions_list = get_legal_actions(state, root_agent)
 
        for actions in actions_list:
            # After agent acts, go to CHANCE node before opponents move
            chance_val = _chance_node(
                state, root_agent, actions,
                next_agent_id=_next_agent(state, root_agent),
                root_agent=root_agent,
                depth=depth - 1,
                alpha=alpha, beta=beta,
                config=config, stats=stats,
            )
            if chance_val > best_val:
                best_val = chance_val
            alpha = max(alpha, best_val)
            if beta <= alpha:
                stats.nodes_pruned += len(actions_list)  # approximate remaining
                break
 
        if config.use_transposition:
            _expert_tt.put(state, root_agent, depth, best_val)
        return best_val
 
    # ── MIN node (opponent's turn) ─────────────────────────────────────────
    else:
        worst_val = math.inf
        actions_list = get_legal_actions(state, agent_id)
 
        for actions in actions_list:
            next_agent = _next_agent(state, agent_id)
            # Determine if next node is MAX or MIN
            next_is_max = (next_agent == root_agent)
 
            child_val = _chance_node(
                state, agent_id, actions,
                next_agent_id=next_agent,
                root_agent=root_agent,
                depth=depth - 1,
                alpha=alpha, beta=beta,
                config=config, stats=stats,
                next_is_max=next_is_max,
            )
            if child_val < worst_val:
                worst_val = child_val
            beta = min(beta, worst_val)
            if beta <= alpha:
                stats.nodes_pruned += len(actions_list)
                break
 
        if config.use_transposition:
            _expert_tt.put(state, root_agent, depth, worst_val)
        return worst_val
 
 
def _chance_node(
    state        : GameState,
    acting_agent : AgentID,
    actions      : list[Action],
    next_agent_id: AgentID,
    root_agent   : AgentID,
    depth        : int,
    alpha        : float,
    beta         : float,
    config       : AgentConfig,
    stats        : SearchStats,
    next_is_max  : bool = False,
) -> float:
    """
    Chance node: enumerate die outcome branches and return the probability-weighted average of child values.
    NO pruning here - all branches must be evaluated.
 
    Only evaluates branches in config.chance_branches (Novice gets top-2).
    Probabilities of excluded branches are redistributed proportionally so they still sum to 1.0.
    """
    stats.nodes_explored += 1
 
    # Filter to this agent's allowed branches
    allowed = config.chance_branches
    raw_probs = {tag: OUTCOME_PROBS[tag] for tag in allowed if tag in OUTCOME_PROBS}
    total_prob = sum(raw_probs.values())
 
    expected_val = 0.0
 
    for outcome_tag, raw_prob in raw_probs.items():
        # Normalise probability among allowed branches
        prob = raw_prob / total_prob
 
        # Apply actions with this forced die outcome
        child_state = state.deep_copy()
        execute_actions(child_state, acting_agent, actions, die_outcome=outcome_tag)
        tick_units(child_state, acting_agent)
 
        # Recurse into next agent's node
        child_val = expectiminimax(
            state      = child_state,
            agent_id   = next_agent_id,
            root_agent = root_agent,
            depth      = depth,
            alpha      = alpha,
            beta       = beta,
            config     = config,
            stats      = stats,
            is_max     = next_is_max,
        )
        expected_val += prob * child_val
 
    return expected_val
 
 
def _next_agent(state: GameState, current: AgentID) -> AgentID:
    """Return the next active agent after current in turn order."""
    order  = state.turn_order
    active = state.active_agents()
    idx    = order.index(current)
    # Cycle through turn order, skipping eliminated agents
    for i in range(1, len(order) + 1):
        candidate = order[(idx + i) % len(order)]
        if candidate in active or candidate == current:
            return candidate
    return current
 


# ─────────────────────────────────────────────
# 6. PUBLIC INTERFACE: choose_best_action
# ─────────────────────────────────────────────
 
@dataclass
class MoveReport:
    """Per-move node report (Section 6.2 of assignment)."""
    move_number     : int
    agent_id        : AgentID
    action_label    : str
    nodes_explored  : int
    nodes_pruned    : int
    pruning_pct     : float
    chosen_value    : float
    elapsed_ms      : float
 
    def to_string(self) -> str:
        return (
            f"Move {self.move_number} | Agent {self.agent_id.value} "
            f"({AGENT_CONFIGS[self.agent_id].agent_id.value}) | "
            f"Action: {self.action_label}\n"
            f"  Expectiminimax nodes explored : {self.nodes_explored:,}\n"
            f"  Nodes pruned (Alpha-Beta)     : {self.nodes_pruned:,} "
            f"({self.pruning_pct:.1f}%)\n"
            f"  Chosen action value (utility) : {self.chosen_value:.4f}\n"
            f"  Time elapsed                  : {self.elapsed_ms:.1f} ms"
        )
 
 
def choose_best_action(
    state       : GameState,
    agent_id    : AgentID,
    move_number : int,
) -> tuple[list[Action], MoveReport]:
    """
    Entry point: run Expectiminimax for the given agent and return
    the best action combo plus a MoveReport for logging.
 
    Args:
        state       : current game state (NOT mutated)
        agent_id    : which agent is deciding
        move_number : global move counter for the report
 
    Returns:
        (best_actions, report)
    """
    config = AGENT_CONFIGS[agent_id]
    stats  = SearchStats()
 
    # Clear transposition table each top-level decision for Expert
    if config.use_transposition:
        _expert_tt.clear()
 
    actions_list = get_legal_actions(state, agent_id)
 
    best_val     = -math.inf
    best_actions = actions_list[0] if actions_list else []
    alpha        = -math.inf
    beta         = math.inf

    for actions in actions_list:
        # Each top-level action goes through a chance node first
        chance_val = _chance_node(
            state        = state,
            acting_agent = agent_id,
            actions      = actions,
            next_agent_id= _next_agent(state, agent_id),
            root_agent   = agent_id,
            depth        = config.max_depth - 1,
            alpha        = alpha,
            beta         = beta,
            config       = config,
            stats        = stats,
            next_is_max  = False,   # after our move it's opponents' turn (MIN)
        )
        if chance_val > best_val:
            best_val     = chance_val
            best_actions = actions
        
        alpha = max(alpha, best_val)
        if beta <= alpha:
            stats.nodes_pruned += len(actions_list) - actions_list.index(actions) - 1
            break

    action_label = _actions_label(best_actions)
 
    report = MoveReport(
        move_number   = move_number,
        agent_id      = agent_id,
        action_label  = action_label,
        nodes_explored= stats.nodes_explored,
        nodes_pruned  = stats.nodes_pruned,
        pruning_pct   = stats.pruning_pct(),
        chosen_value  = best_val,
        elapsed_ms    = stats.elapsed_ms(),
    )
 
    return best_actions, report
 
 
def _actions_label(actions: list[Action]) -> str:
    """Human-readable label for a list of actions."""
    parts = []
    for a in actions:
        if a.action_type == ActionType.WAIT:
            parts.append("Wait")
        else:
            parts.append(f"{a.action_type.value}({a.target_row},{a.target_col})")
    return " + ".join(parts)
 
 
# ─────────────────────────────────────────────
# 7. GAME SUMMARY TABLE
# ─────────────────────────────────────────────
 
def print_summary_table(reports: list[MoveReport]):
    """Print end-of-game summary table (Section 6.2)."""
    print("\n" + "="*65)
    print("GAME SUMMARY - Search Statistics")
    print("="*65)
    print(f"{'Agent':<12} {'Moves':>6} {'Nodes':>10} {'Pruned':>10} {'Efficiency':>12}")
    print("-"*65)
 
    for aid in AgentID:
        agent_reports = [r for r in reports if r.agent_id == aid]
        if not agent_reports:
            continue
        total_nodes  = sum(r.nodes_explored for r in agent_reports)
        total_pruned = sum(r.nodes_pruned   for r in agent_reports)
        total        = total_nodes + total_pruned
        eff          = (total_pruned / total * 100) if total > 0 else 0.0
        label        = f"{aid.value} ({['Expert','Intermediate','Novice'][list(AgentID).index(aid)]})"
        print(f"{label:<12} {len(agent_reports):>6} {total_nodes:>10,} {total_pruned:>10,} {eff:>11.1f}%")
 
    print("="*65)



"""
5. I/O + Game Loop
========================
"""
 
 
# ─────────────────────────────────────────────
# 1. BOARD.TXT PARSER
# ─────────────────────────────────────────────
 
def parse_board(filepath: str) -> tuple[int, int, int, list[list[str]], dict]:
    """
    Expected format:
        N M R
        <N lines of M characters>
        A_row A_col
        B_row B_col
        C_row C_col
 
    Returns:
        (rows, cols, max_rounds, grid_chars, start_positions)
        start_positions: {AgentID: (row, col)}
    """
    if not os.path.exists(filepath):
        raise FileNotFoundError(f"board.txt not found at: {filepath}")
 
    with open(filepath, 'r') as f:
        lines = [l.rstrip('\n') for l in f.readlines()]
 
    # Filter blank lines
    lines = [l for l in lines if l.strip()]
 
    if len(lines) < 5:
        raise ValueError(
            f"board.txt too short - expected at least 5 lines, got {len(lines)}"
        )
 
    # Line 1: N M R
    try:
        parts = lines[0].split()
        rows, cols, max_rounds = int(parts[0]), int(parts[1]), int(parts[2])
    except (IndexError, ValueError):
        raise ValueError(f"Line 1 must be 'N M R' (integers), got: '{lines[0]}'")
 
    # Lines 2..N+1: the grid
    valid_chars = set('.XFM')
    grid_chars = []
    for i in range(1, rows + 1):
        if i >= len(lines):
            raise ValueError(f"Expected {rows} grid rows, ran out at row {i}.")
        row_str = lines[i]
        if len(row_str) != cols:
            raise ValueError(
                f"Grid row {i} has {len(row_str)} chars, expected {cols}: '{row_str}'"
            )
        invalid = set(row_str) - valid_chars
        if invalid:
            raise ValueError(
                f"Grid row {i} contains invalid characters {invalid}: '{row_str}'"
            )
        grid_chars.append(list(row_str))
 
    # Lines N+2, N+3, N+4: agent start positions
    agent_order = [AgentID.A, AgentID.B, AgentID.C]
    start_positions = {}
    for j, aid in enumerate(agent_order):
        line_idx = rows + 1 + j
        if line_idx >= len(lines):
            raise ValueError(f"Missing start position for agent {aid.value}.")
        try:
            r, c = map(int, lines[line_idx].split())
        except ValueError:
            raise ValueError(
                f"Agent {aid.value} start position must be two integers, "
                f"got: '{lines[line_idx]}'"
            )
        if not (0 <= r < rows and 0 <= c < cols):
            raise ValueError(
                f"Agent {aid.value} start ({r},{c}) is out of bounds "
                f"for {rows}x{cols} board."
            )
        if grid_chars[r][c] == 'X':
            raise ValueError(
                f"Agent {aid.value} start ({r},{c}) is on an Obstacle."
            )
        start_positions[aid] = (r, c)
 
    return rows, cols, max_rounds, grid_chars, start_positions
 
 
# ─────────────────────────────────────────────
# 2. RESULTS WRITER
# ─────────────────────────────────────────────
 
class ResultsWriter:
    """
    Writes per-move node reports and the final summary to results.txt.
    """
 
    def __init__(self, filepath: str = "results.txt"):
        self.filepath = filepath
        self._file = open(filepath, 'w', encoding='utf-8')
        self._move_reports: list[MoveReport] = []
 
    def write(self, text: str, to_console: bool = True):
        """Write text to file (and optionally console)."""
        self._file.write(text + '\n')
        self._file.flush()
        if to_console:
            print(text)
 
    def log_move(self, report: MoveReport):
        """Log a per-move node report (spec Section 6.2)."""
        self._move_reports.append(report)
        self.write(report.to_string())
        self.write("")   # blank line separator
 
    def log_event(self, event: EventResult):
        """Log an environmental event."""
        self.write(f"  [ENV] {event}")
 
    def log_action_result(self, result: ActionResult):
        """Log action execution details."""
        for line in result.log:
            self.write(f"  {line}")
 
    def log_round_scores(self, score_log: list[str]):
        """Log end-of-round scoring."""
        self.write("  [SCORE]")
        for line in score_log:
            self.write(f"  {line}")
 
    def write_final_summary(self, state: GameState):
        """Write final scores, winner, and the per-agent summary table."""
        self.write("\n" + "="*65)
        self.write("FINAL RESULTS")
        self.write("="*65)
 
        # Scores
        for aid in AgentID:
            agent = state.get_agent(aid)
            label = ["Expert", "Intermediate", "Novice"][list(AgentID).index(aid)]
            status = "ELIMINATED" if agent.is_eliminated else "active"
            self.write(
                f"  Agent {aid.value} ({label:13s}): "
                f"score={agent.score:5d}  energy={agent.energy:2d}  "
                f"cells={state.board.count_owned(aid):3d}  [{status}]"
            )
 
        winner = state.winner()
        if winner:
            label = ["Expert", "Intermediate", "Novice"][list(AgentID).index(winner)]
            self.write(f"\n  WINNER: Agent {winner.value} ({label})")
        else:
            self.write("\n  RESULT: Draw / no winner determined.")
 
        self.write("="*65)
 
        # Per-agent search summary
        _write_summary_table_to_file(self, self._move_reports)
 
    def close(self):
        self._file.close()
 
 
def _write_summary_table_to_file(writer: ResultsWriter, reports: list[MoveReport]):
    """Write the summary table to both file and console."""
    writer.write("\n" + "="*65)
    writer.write("GAME SUMMARY - Search Statistics")
    writer.write("="*65)
    writer.write(
        f"{'Agent':<20} {'Moves':>6} {'Nodes':>10} {'Pruned':>10} {'Efficiency':>12}"
    )
    writer.write("-"*65)
 
    for aid in AgentID:
        agent_reports = [r for r in reports if r.agent_id == aid]
        if not agent_reports:
            continue
        total_nodes  = sum(r.nodes_explored for r in agent_reports)
        total_pruned = sum(r.nodes_pruned   for r in agent_reports)
        total        = total_nodes + total_pruned
        eff          = (total_pruned / total * 100) if total > 0 else 0.0
        label = f"{aid.value} ({'Expert' if aid==AgentID.A else 'Intermediate' if aid==AgentID.B else 'Novice'})"
        writer.write(
            f"{label:<20} {len(agent_reports):>6} "
            f"{total_nodes:>10,} {total_pruned:>10,} {eff:>11.1f}%"
        )
 
    writer.write("="*65)
 


# ─────────────────────────────────────────────
# 3. GAME LOOP
# ─────────────────────────────────────────────
 
class GameLoop:
    """
    How to run the game:
        loop = GameLoop(state, writer)
        loop.run()           # play to completion
        # or step-by-step:
        loop.step()          # advance one agent action
    """
 
    def __init__(self, state: GameState,    # initial state (from build_initial_state)
                 writer: ResultsWriter,     # ResultsWriter for logging
                 use_search: bool = True):  # if False, agents pick random actions (for fast testing)
        self.state      = state
        self.writer     = writer
        self.use_search = use_search
        self.move_number= 0
        self.done       = False
 
        # Track which agent index within the round we're on
        self._agent_idx = 0
        self._round_started = False
 
        # For GUI: store last move report and event for display
        self.last_report: Optional[MoveReport] = None
        self.last_event : Optional[EventResult] = None
        self.last_action_result: Optional[ActionResult] = None
 
    def run(self) -> GameState:
        """Play the game to completion. Returns final state."""
        while not self.done:
            self.step()
        return self.state
 
    def step(self) -> bool:
        """
        Advance one agent's turn.
        Returns True if the game is still running, False if it ended.
        """
        if self.done:
            return False
 
        state = self.state
 
        # ── Start of new round ────────────────────────────────────────────
        if self._agent_idx == 0 and not self._round_started:
            self._round_started = True
            self.writer.write(
                f"\n{'─'*50}\n"
                f"ROUND {state.round_number} / {state.max_rounds}\n"
                f"{'─'*50}"
            )
 
            # Environmental event (before Agent A moves)
            event_tag = draw_environmental_event()
            event_res = apply_environmental_event(state, event_tag)
            self.last_event = event_res
            self.writer.log_event(event_res)
 
        # ── Current agent's turn ──────────────────────────────────────────
        active_agents = state.active_agents()
        if not active_agents:
            self._end_game()
            return False
 
        # Wrap agent index to active agents
        if self._agent_idx >= len(active_agents):
            self._agent_idx = 0
            self._finish_round()
            return not self.done
 
        agent_id = active_agents[self._agent_idx]
 
        self.writer.write(f"\n  >> {agent_id.value} turn:")
 
        # Choose action
        if self.use_search:
            self.move_number += 1
            actions, report = choose_best_action(state, agent_id, self.move_number)
            self.last_report = report
            self.writer.log_move(report)
        else:
            # Random fallback for fast testing
            actions_list = get_legal_actions(state, agent_id)
            actions = random.choice(actions_list)
            self.move_number += 1
            self.writer.write(
                f"  [RANDOM] {agent_id.value} → {[str(a) for a in actions]}"
            )
 
        # Execute actions
        result = execute_actions(state, agent_id, actions)
        self.last_action_result = result
        self.writer.log_action_result(result)
 
        # Award elimination bonus if any opponent was just eliminated
        award_elimination_bonus(state, agent_id, result)
 
        # Tick unit cooldowns
        tick_units(state, agent_id)
 
        # Clear fog if it was applied this turn
        if state.fog_active:
            clear_fog(state)
 
        # Check for immediate win condition (>60% cells)
        if state.is_terminal():
            self._end_game()
            return False
 
        self._agent_idx += 1
        return True
 
    def _finish_round(self):
        """Called after all agents have moved in a round."""
        state = self.state
 
        # Score all agents
        score_log = score_all_agents(state)
        self.writer.log_round_scores(score_log)
 
        # Tick temp fortresses and bonus units
        expired_fortresses = tick_temp_fortresses(state)
        for msg in expired_fortresses:
            self.writer.write(f"  [EXPIRY] {msg}")
 
        expired_units = tick_bonus_units(state)
        for msg in expired_units:
            self.writer.write(f"  [EXPIRY] {msg}")
 
        # Check elimination: agents with 0 energy and no active units
        for aid in AgentID:
            agent = state.get_agent(aid)
            if not agent.is_eliminated:
                if len(agent.units) == 0:
                    agent.is_eliminated = True
                    self.writer.write(f"  [ELIM] {aid.value} has no units - eliminated!")
 
        # Print board snapshot
        self.writer.write(f"\n  Board after round {state.round_number}:")
        for line in repr(state.board).split('\n'):
            self.writer.write(f"    {line}")
 
        # Advance round counter
        state.round_number += 1
        self._round_started = False
 
        # Check terminal
        if state.is_terminal():
            self._end_game()
 
    def _end_game(self):
        """Finalise the game."""
        self.done = True
        self.writer.write("\n" + "="*50)
        self.writer.write("GAME OVER")
        self.writer.write("="*50)
        self.writer.write_final_summary(self.state)
        self.writer.close()
 
 
# ─────────────────────────────────────────────
# 4. MAIN ENTRY POINT
# ─────────────────────────────────────────────
 
def main(board_path: str = "board.txt",
         results_path: str = "results.txt",
         use_search: bool = True,
         seed: Optional[int] = None):
    """
    parse board.txt → build state → run game loop → write results.txt
    """
    if seed is not None:
        random.seed(seed)
 
    print(f"Loading board from: {board_path}")
    rows, cols, max_rounds, grid_chars, start_positions = parse_board(board_path)
    print(f"Board: {rows}x{cols}, {max_rounds} rounds")
    print(f"Starts: A={start_positions[AgentID.A]}, "
          f"B={start_positions[AgentID.B]}, "
          f"C={start_positions[AgentID.C]}")
 
    state  = build_initial_state(rows, cols, max_rounds, grid_chars, start_positions)
    writer = ResultsWriter(results_path)
 
    writer.write(f"Stochastic Battlefield Game - {rows}x{cols} board, {max_rounds} rounds")
    writer.write(f"Agents: A(Expert,d=7), B(Intermediate,d=5), C(Novice,d=3)")
    writer.write("="*65 + "\n")
 
    loop = GameLoop(state, writer, use_search=use_search)
    final_state = loop.run()
 
    print(f"\nResults written to: {results_path}")
    return final_state
 


"""
Step 6: GUI - Dear PyGui Interface
====================================
"""

# ─────────────────────────────────────────────
# COLOURS
# ─────────────────────────────────────────────

COL_EMPTY     = (40,  40,  40,  255)   # dark grey
COL_OBSTACLE  = (20,  20,  20,  255)   # near-black
COL_FORTRESS  = (180, 140, 0,   255)   # gold
COL_MINEFIELD = (140, 60,  0,   255)   # brown
COL_AGENT_A   = (30,  100, 200, 255)   # blue
COL_AGENT_B   = (200, 60,  60,  255)   # red
COL_AGENT_C   = (60,  180, 60,  255)   # green
COL_TEXT      = (220, 220, 220, 255)
COL_UNIT      = (255, 255, 255, 255)   # white dot for unit

AGENT_COLOURS = {
    AgentID.A: COL_AGENT_A,
    AgentID.B: COL_AGENT_B,
    AgentID.C: COL_AGENT_C,
}
AGENT_LABELS = {
    AgentID.A: "A - Expert",
    AgentID.B: "B - Intermediate",
    AgentID.C: "C - Novice",
}


# ─────────────────────────────────────────────
# GUI CLASS
# ─────────────────────────────────────────────

class BattlefieldGUI:

    CELL_SIZE = 52          # pixels per cell
    LOG_MAX   = 120         # max lines in move log

    def __init__(self, board_path: str = "board.txt",
                 results_path: str = "results.txt"):

        # ── Parse & build state ──────────────────────────────────────────
        rows, cols, max_rounds, grid_chars, starts = parse_board(board_path)
        self.state   = build_initial_state(rows, cols, max_rounds, grid_chars, starts)
        self.writer  = ResultsWriter(results_path)
        self.loop    = GameLoop(self.state, self.writer, use_search=True)

        self.rows    = rows
        self.cols    = cols
        self._running_auto = False
        self._auto_thread  = None
        self._log_lines: list[str] = []

        # DrawList tag references built during setup
        self._cell_tags : list[list[str]] = []   # [r][c] → drawlist rect tag
        self._unit_tags : list[str]       = []   # flat list of unit dot tags
        self._unit_draw_counter: int      = 0    # ensures unique tags across redraws

    # ─────────────────────────────────────────
    # BUILD UI
    # ─────────────────────────────────────────

    def build(self):
        dpg.create_context()
        dpg.create_viewport(title="Stochastic Battlefield", width=1080, height=680)
        dpg.setup_dearpygui()

        with dpg.font_registry():
            pass  # use default font

        board_px_w = self.cols * self.CELL_SIZE + 10
        board_px_h = self.rows * self.CELL_SIZE + 10

        with dpg.window(tag="main", label="Battlefield",
                        width=1080, height=680,
                        no_resize=True, no_move=True,
                        no_title_bar=True):

            with dpg.group(horizontal=True):

                # ── Left: board ──────────────────────────────────────────
                with dpg.child_window(tag="board_panel",
                                      width=board_px_w + 4,
                                      height=board_px_h + 60,
                                      border=False):
                    dpg.add_text("Board", color=COL_TEXT)
                    with dpg.drawlist(width=board_px_w,
                                      height=board_px_h,
                                      tag="board_dl"):
                        self._draw_board_initial()
                    dpg.add_text("", tag="txt_winner_map", color=(255, 215, 0, 255))

                # ── Right: controls + stats + log ────────────────────────
                with dpg.child_window(tag="right_panel",
                                      width=590, height=660,
                                      border=False):

                    # Round info
                    dpg.add_text("Round: 1", tag="txt_round", color=COL_TEXT)
                    dpg.add_separator()

                    # Controls
                    dpg.add_text("Controls", color=COL_TEXT)
                    with dpg.group(horizontal=True):
                        dpg.add_button(label="Next Move",
                                       callback=self._cb_next,
                                       width=110, height=32)
                        dpg.add_button(label="Run",
                                       tag="btn_run",
                                       callback=self._cb_run,
                                       width=60, height=32)
                        dpg.add_button(label="Stop",
                                       callback=self._cb_stop,
                                       width=60, height=32)
                        dpg.add_button(label="End",
                                       callback=self._cb_end,
                                       width=60, height=32)

                    dpg.add_text("Speed (moves/sec):", color=COL_TEXT)
                    dpg.add_slider_float(tag="slider_speed",
                                         default_value=1.0,
                                         min_value=0.2, max_value=5.0,
                                         width=260)
                    dpg.add_separator()

                    # Legend
                    dpg.add_text("Legend", color=COL_TEXT)
                    with dpg.group(horizontal=True):
                        _legend_box(COL_AGENT_A, "Agent A")
                        _legend_box(COL_AGENT_B, "Agent B")
                        _legend_box(COL_AGENT_C, "Agent C")
                        _legend_box(COL_FORTRESS, "Fortress")
                        _legend_box(COL_MINEFIELD, "Mine")
                        _legend_box(COL_OBSTACLE, "Obstacle")
                    dpg.add_separator()

                    # Agent stats
                    dpg.add_text("Agent Stats", color=COL_TEXT)
                    with dpg.table(tag="agent_table",
                                   header_row=True,
                                   borders_innerH=True,
                                   borders_outerH=True,
                                   borders_outerV=True,
                                   width=560):
                        dpg.add_table_column(label="Agent",  width_fixed=True, init_width_or_weight=130)
                        dpg.add_table_column(label="Score",  width_fixed=True, init_width_or_weight=70)
                        dpg.add_table_column(label="Energy", width_fixed=True, init_width_or_weight=70)
                        dpg.add_table_column(label="Cells",  width_fixed=True, init_width_or_weight=60)
                        dpg.add_table_column(label="Units",  width_fixed=True, init_width_or_weight=60)
                        dpg.add_table_column(label="Status", width_fixed=True, init_width_or_weight=100)

                        for aid in AgentID:
                            with dpg.table_row(tag=f"row_{aid.value}"):
                                dpg.add_text(AGENT_LABELS[aid],
                                             color=AGENT_COLOURS[aid],
                                             tag=f"stat_name_{aid.value}")
                                dpg.add_text("0",  tag=f"stat_score_{aid.value}")
                                dpg.add_text("20", tag=f"stat_energy_{aid.value}")
                                dpg.add_text("0",  tag=f"stat_cells_{aid.value}")
                                dpg.add_text("0",  tag=f"stat_units_{aid.value}")
                                dpg.add_text("Active", tag=f"stat_status_{aid.value}")

                    dpg.add_separator()

                    # Last move node stats
                    dpg.add_text("Last Move Stats", color=COL_TEXT)
                    dpg.add_text("-", tag="txt_node_stats", color=(180, 180, 180, 255),
                                 wrap=560)
                    dpg.add_separator()

                    # Move log
                    dpg.add_text("Move Log", color=COL_TEXT)
                    with dpg.child_window(tag="log_win",
                                          width=565, height=200,
                                          border=True):
                        dpg.add_text("Game start.", tag="txt_log",
                                     color=(180, 180, 180, 255),
                                     wrap=550)

        dpg.set_primary_window("main", True)
        self._refresh_stats()

    # ─────────────────────────────────────────
    # INITIAL BOARD DRAW
    # ─────────────────────────────────────────

    def _draw_board_initial(self):
        cs  = self.CELL_SIZE
        board = self.state.board

        self._cell_tags = [[None]*self.cols for _ in range(self.rows)]

        for r in range(self.rows):
            for c in range(self.cols):
                x0, y0 = c*cs + 2, r*cs + 2
                x1, y1 = x0 + cs - 2, y0 + cs - 2
                tag = f"cell_{r}_{c}"
                col = self._cell_colour(r, c)
                dpg.draw_rectangle(pmin=(x0, y0), pmax=(x1, y1),
                                   color=(0,0,0,0), fill=col,
                                   tag=tag, parent="board_dl")
                self._cell_tags[r][c] = tag

        # Draw coordinate labels (col numbers top, row numbers left)
        for c in range(self.cols):
            dpg.draw_text((c*cs + cs//2 - 4, 2),
                          str(c), size=11,
                          color=(120,120,120,200),
                          parent="board_dl")
        for r in range(self.rows):
            dpg.draw_text((2, r*cs + cs//2 - 6),
                          str(r), size=11,
                          color=(120,120,120,200),
                          parent="board_dl")

        self._draw_units()

    def _cell_colour(self, r: int, c: int) -> tuple:
        board = self.state.board
        cell  = board.get_cell(r, c)

        if cell.cell_type == CellType.OBSTACLE:
            return COL_OBSTACLE
        if cell.cell_type == CellType.MINEFIELD and cell.owner is None:
            return COL_MINEFIELD
        if cell.owner is not None:
            base = AGENT_COLOURS[cell.owner]
            if cell.is_fortress:
                # Blend agent colour with gold
                return (
                    (base[0] + COL_FORTRESS[0]) // 2,
                    (base[1] + COL_FORTRESS[1]) // 2,
                    (base[2] + COL_FORTRESS[2]) // 2,
                    255
                )
            return base
        if cell.cell_type == CellType.FORTRESS:
            return COL_FORTRESS

        return COL_EMPTY

    def _draw_units(self):
        """Draw white dots for each unit on the board."""
        # Delete old unit dots
        for tag in self._unit_tags:
            if dpg.does_item_exist(tag):
                dpg.delete_item(tag)
        self._unit_tags.clear()

        cs = self.CELL_SIZE

        for aid in AgentID:
            agent = self.state.get_agent(aid)
            for unit in agent.units:
                r, c = unit.row, unit.col
                cx = c * cs + cs // 2
                cy = r * cs + cs // 2
                tag = f"unit_dot_{self._unit_draw_counter}"
                self._unit_draw_counter += 1
                dpg.draw_circle(center=(cx, cy), radius=8,
                                color=(0,0,0,255),
                                fill=COL_UNIT,
                                tag=tag, parent="board_dl")
                # Agent letter
                ltag = f"unit_lbl_{self._unit_draw_counter}"
                self._unit_draw_counter += 1
                dpg.draw_text((cx - 4, cy - 7),
                              aid.value, size=13,
                              color=AGENT_COLOURS[aid],
                              tag=ltag, parent="board_dl")
                self._unit_tags += [tag, ltag]

    # ─────────────────────────────────────────
    # REFRESH
    # ─────────────────────────────────────────

    def _refresh_board(self):
        """Repaint every cell and redraw units."""
        for r in range(self.rows):
            for c in range(self.cols):
                tag = self._cell_tags[r][c]
                if dpg.does_item_exist(tag):
                    dpg.configure_item(tag, fill=self._cell_colour(r, c))
        self._draw_units()

    def _refresh_stats(self):
        """Update the agent stats table and round label."""
        state = self.state
        display_round = min(state.round_number, state.max_rounds)
        dpg.set_value("txt_round",
                      f"Round: {display_round} / {state.max_rounds}")

        for aid in AgentID:
            agent = state.get_agent(aid)
            cells = state.board.count_owned(aid)
            dpg.set_value(f"stat_score_{aid.value}",  str(agent.score))
            dpg.set_value(f"stat_energy_{aid.value}", str(agent.energy))
            dpg.set_value(f"stat_cells_{aid.value}",  str(cells))
            dpg.set_value(f"stat_units_{aid.value}",  str(len(agent.units)))
            status = "Eliminated" if agent.is_eliminated else "Active"
            dpg.set_value(f"stat_status_{aid.value}", status)

    def _refresh_node_stats(self, report):
        """Show last move search stats."""
        if report is None:
            return
        txt = (
            f"{report.agent_id.value} | {report.action_label}\n"
            f"Nodes: {report.nodes_explored:,}  "
            f"Pruned: {report.nodes_pruned:,} ({report.pruning_pct:.1f}%)  "
            f"Utility: {report.chosen_value:.3f}  "
            f"Time: {report.elapsed_ms:.0f}ms"
        )
        dpg.set_value("txt_node_stats", txt)

    def _add_log(self, text: str):
        """Append a line to the move log panel."""
        self._log_lines.append(text)
        if len(self._log_lines) > self.LOG_MAX:
            self._log_lines = self._log_lines[-self.LOG_MAX:]
        dpg.set_value("txt_log", "\n".join(self._log_lines))

    # ─────────────────────────────────────────
    # STEP LOGIC
    # ─────────────────────────────────────────

    def _do_step(self):
        """Advance one move and refresh UI."""
        if getattr(self, '_game_over_handled', False) or self.loop.done:
            self._add_log("Game over.")
            return

        still_running = self.loop.step()

        # Grab what happened from the loop
        if self.loop.last_event:
            ev = self.loop.last_event
            self._add_log(f"[ENV] {ev.event_tag}: {' '.join(ev.log)}")
            self.loop.last_event = None

        if self.loop.last_action_result:
            for line in self.loop.last_action_result.log:
                self._add_log(line)
            self.loop.last_action_result = None

        if self.loop.last_report:
            self._refresh_node_stats(self.loop.last_report)
            self.loop.last_report = None

        self._refresh_board()
        self._refresh_stats()

        if not still_running or self.loop.done:
            self._ui_game_over()

    def _ui_game_over(self):
        if getattr(self, '_game_over_handled', False):
            return
        self._game_over_handled = True
        self._add_log("=== GAME OVER ===")
        winner = self.state.winner()
        if winner:
            self._add_log(f"Winner: Agent {winner.value}!")
            dpg.set_value("txt_winner_map", f"GAME OVER! Winner: Agent {winner.value} (Score: {self.state.get_agent(winner).score})")
        else:
            dpg.set_value("txt_winner_map", "GAME OVER! Draw / No Winner")
        
        self._add_log("--- GAME SUMMARY ---")
        for aid in AgentID:
            agent_reports = [r for r in self.loop.writer._move_reports if r.agent_id == aid]
            if agent_reports:
                total_nodes = sum(r.nodes_explored for r in agent_reports)
                total_pruned = sum(r.nodes_pruned for r in agent_reports)
                eff = (total_pruned / (total_nodes + total_pruned) * 100) if (total_nodes + total_pruned) > 0 else 0.0
                self._add_log(f"Agent {aid.value}: {total_nodes} nodes, {total_pruned} pruned ({eff:.1f}%)")
        
        self._running_auto = False

    # ─────────────────────────────────────────
    # CALLBACKS
    # ─────────────────────────────────────────

    def _cb_next(self, sender, app_data):
        if not getattr(self, '_game_over_handled', False) and not self.loop.done:
            self._do_step()

    def _cb_run(self, sender, app_data):
        if self._running_auto or self.loop.done or getattr(self, '_game_over_handled', False):
            return
        if hasattr(self, '_auto_thread') and self._auto_thread.is_alive():
            return
        self._running_auto = True
        self._auto_thread  = threading.Thread(target=self._auto_run, daemon=True)
        self._auto_thread.start()

    def _cb_stop(self, sender, app_data):
        self._running_auto = False

    def _cb_end(self, sender, app_data):
        if not getattr(self, '_game_over_handled', False) and not self.loop.done:
            self._running_auto = False
            self._add_log("Game terminated")
            self.loop._end_game()
            self._ui_game_over()

    def _auto_run(self):
        """Background thread: keep stepping at configured speed."""
        while self._running_auto and not self.loop.done and not getattr(self, '_game_over_handled', False):
            speed   = dpg.get_value("slider_speed")
            delay   = 1.0 / max(speed, 0.1)
            self._do_step()
            
            slept = 0.0
            while slept < delay and self._running_auto:
                time.sleep(0.05)
                slept += 0.05
                
        self._running_auto = False

    # ─────────────────────────────────────────
    # LAUNCH
    # ─────────────────────────────────────────

    def run(self):
        self.build()
        dpg.show_viewport()
        while dpg.is_dearpygui_running():
            dpg.render_dearpygui_frame()
        dpg.destroy_context()


# ─────────────────────────────────────────────
# HELPER
# ─────────────────────────────────────────────

def _legend_box(colour: tuple, label: str):
    """Small coloured square + label for the legend."""
    with dpg.group(horizontal=True):
        dpg.add_color_button(default_value=colour,
                             width=14, height=14,
                             no_tooltip=True, no_border=True,
                             enabled=False)
        dpg.add_text(label, color=COL_TEXT)


# ─────────────────────────────────────────────
# ENTRY POINT
# ─────────────────────────────────────────────

if __name__ == "__main__":
    import sys
    board_path   = sys.argv[1] if len(sys.argv) > 1 else "board.txt"
    results_path = sys.argv[2] if len(sys.argv) > 2 else "results.txt"
    random.seed(42)
    gui = BattlefieldGUI(board_path, results_path)
    gui.run()