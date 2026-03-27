import random
import copy

# ─────────────────────────────────────────
# ZONE DATA
# ─────────────────────────────────────────
# Key: zone number (1–8)
# Value: dict with description and capacity in kg

zones = {
    1: {"name": "Heavy Item Floor Storage",           "capacity": 120},
    2: {"name": "Standard Rack Storage",              "capacity": 80},
    3: {"name": "Fragile Item Shelf",                 "capacity": 80},
    4: {"name": "Temperature Controlled Storage",     "capacity": 80},
    5: {"name": "Hazardous Material Storage",         "capacity": 80},
    6: {"name": "Fast-Moving Product Area",           "capacity": 60},
    7: {"name": "Bulk Dry Storage",                   "capacity": 150},
    8: {"name": "Refrigerated Loading Dock",          "capacity": 100},
}

# ─────────────────────────────────────────
# PRODUCT DATA
# ─────────────────────────────────────────
# Index 0 = P1, Index 1 = P2, ..., Index 19 = P20
# Each product has:
#   name, weight, category,
#   fragile, hazardous, temp_controlled, high_demand

products = [
    {"name": "Glass Bottles",     "weight": 20, "category": "Beverage",    "fragile": True,  "hazardous": False, "temp_controlled": False, "high_demand": False},
    {"name": "Frozen Meat",       "weight": 30, "category": "Food",        "fragile": False, "hazardous": False, "temp_controlled": True,  "high_demand": True },
    {"name": "Cleaning Acid",     "weight": 10, "category": "Chemical",    "fragile": False, "hazardous": True,  "temp_controlled": False, "high_demand": False},
    {"name": "Rice Bags",         "weight": 50, "category": "Grocery",     "fragile": False, "hazardous": False, "temp_controlled": False, "high_demand": True },
    {"name": "Ceramic Plates",    "weight": 15, "category": "Kitchenware", "fragile": True,  "hazardous": False, "temp_controlled": False, "high_demand": False},
    {"name": "Ice Cream",         "weight": 25, "category": "Food",        "fragile": False, "hazardous": False, "temp_controlled": True,  "high_demand": True },
    {"name": "Detergent",         "weight": 12, "category": "Chemical",    "fragile": False, "hazardous": True,  "temp_controlled": False, "high_demand": False},
    {"name": "Chips Carton",      "weight":  8, "category": "Snacks",      "fragile": False, "hazardous": False, "temp_controlled": False, "high_demand": True },
    {"name": "Olive Oil Bottles", "weight": 18, "category": "Grocery",     "fragile": True,  "hazardous": False, "temp_controlled": False, "high_demand": False},
    {"name": "Industrial Bleach", "weight": 22, "category": "Chemical",    "fragile": False, "hazardous": True,  "temp_controlled": False, "high_demand": False},
    {"name": "Yogurt Cartons",    "weight": 14, "category": "Food",        "fragile": False, "hazardous": False, "temp_controlled": True,  "high_demand": True },
    {"name": "Flour Bags",        "weight": 45, "category": "Grocery",     "fragile": False, "hazardous": False, "temp_controlled": False, "high_demand": True },
    {"name": "Wine Bottles",      "weight": 16, "category": "Beverage",    "fragile": True,  "hazardous": False, "temp_controlled": False, "high_demand": False},
    {"name": "Paint Cans",        "weight": 28, "category": "Chemical",    "fragile": False, "hazardous": True,  "temp_controlled": False, "high_demand": False},
    {"name": "Biscuit Boxes",     "weight":  6, "category": "Snacks",      "fragile": False, "hazardous": False, "temp_controlled": False, "high_demand": True },
    {"name": "Motor Oil",         "weight": 35, "category": "Chemical",    "fragile": False, "hazardous": True,  "temp_controlled": False, "high_demand": False},
    {"name": "Frozen Fish",       "weight": 20, "category": "Food",        "fragile": False, "hazardous": False, "temp_controlled": True,  "high_demand": True },
    {"name": "Bubble Wrap Rolls", "weight": 10, "category": "Packaging",   "fragile": True,  "hazardous": False, "temp_controlled": False, "high_demand": False},
    {"name": "Wheat Sacks",       "weight": 40, "category": "Grocery",     "fragile": False, "hazardous": False, "temp_controlled": False, "high_demand": True },
    {"name": "Hand Sanitizer",    "weight":  8, "category": "Chemical",    "fragile": True,  "hazardous": False, "temp_controlled": False, "high_demand": False},
]

# ─────────────────────────────────────────
# QUICK REFERENCE SETS (for fitness checks)
# ─────────────────────────────────────────
# These sets store product INDICES (0-based) for fast lookup

fragile_products     = {i for i, p in enumerate(products) if p["fragile"]}
hazardous_products   = {i for i, p in enumerate(products) if p["hazardous"]}
temp_ctrl_products   = {i for i, p in enumerate(products) if p["temp_controlled"]}
high_demand_products = {i for i, p in enumerate(products) if p["high_demand"]}
heavy_products       = {i for i, p in enumerate(products) if p["weight"] > 40}

# Only Frozen Meat (1), Ice Cream (5), Yogurt Cartons (10), Frozen Fish (16) are eligible for Z8
z8_eligible_products = {1, 5, 10, 16}

# Food and Chemical product indices (for incompatibility check)
food_products     = {i for i, p in enumerate(products) if p["category"] == "Food"}
chemical_products = {i for i, p in enumerate(products) if p["category"] == "Chemical"}

# ─────────────────────────────────────────
# FUNCTION DEFINITIONS
# ─────────────────────────────────────────

def calculate_fitness(chromo):
    fitness = 0
    num_zones = 8

    # 5.1
    # Weights assigned to each zone (0-indexed)
    weights = [0 for i in range(num_zones + 1)]  # +1 to make it 1-indexed for easier mapping
    for i in range(len(chromo)):
        weights[chromo[i]] += products[i]
    
    for i in range(len(weights)):
        diff = weights[i] - zones[i]["capacity"]
        if diff > 0:
            fitness += diff * 2
    
    # 5.2
    for i in range(len(chromo)):
        if zones[chromo[i]] != 3 and products[i] in fragile_products:
            fitness += 8
    
    # 5.3
    for i in range(len(chromo)):
        if zones[chromo[i]] != 5 and products[i] in hazardous_products:
            fitness += 10

    # 5.4
    for i in range(len(chromo)):
        if (zones[chromo[i]] == 8 and i in z8_eligible_products) or (zones[chromo[i]] == 4 and products[i] in temp_ctrl_products) or (zones[chromo[i]] == 4 and i in z8_eligible_products):
            pass
        else:
            fitness += 9

    # 5.5
    for i in range(len(chromo)):
        if zones[chromo[i]] != 6 and products[i] in high_demand_products:
            fitness += 5

    # 5.6
    for i in range(len(chromo)):
        if zones[chromo[i]] != 1 and products[i] in heavy_products:
            fitness += 4

    # 5.7
    #fitness += 3

    # 5.8
    #fitness += 15

    # 5.9
    for i in range(len(chromo)):
        if zones[chromo[i]] != 8 and i in z8_eligible_products:
            fitness += 12


    return fitness

def calc_population_fitness(population):
    fitnesses = []
    for chromo in population:
        fit_val = calculate_fitness(chromo)
        fitnesses.append(fit_val)
    return fitnesses

def initialize_population(pop_size):

    pass

def selection(population, fitnesses):

    pass

def crossover(parent1, parent2):
    
    pass

def mutation(chromosome, mutation_rate):

    pass


if __name__ == "__main__":
    # Initialization
    initial_count = 20
    population = initialize_population(initial_count)
    print("Initial Population: ")
    for i in range(min(len(population), 5)):
        print(population[i])

    hardcoded_chromo = [2, 2, 2, 2, 2, 3, 3, 3, 2, 2,  8,  3,  4,  1,  7,  5,  2,  1,  6,  8]
    #                   P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15 P16 P17 P18 P19 P20

    calculate_fitness(hardcoded_chromo)

    pass