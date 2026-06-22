import random
import copy

def calc_fitness(chromo, max_range):
  # Calculate the fitness value for the chromosome
  # The fitness is the sum of the distances between each pair of antennas 
  # We want to maximize the fitness value
  fitness = 0
  arr = [[0 for i in range(max_range)] for j in range(max_range)]
  
  for set in chromo:
    X, Y = set
    col = X - 1
    row = Y - 1
    # Center
    if arr[row][col] == 0:
      arr[row][col] = 1
      fitness += 1

    # Up, Down, Left, Right
    if row-1 >= 0 and arr[row-1][col] == 0:
      arr[row-1][col] = 1
      fitness += 1
    if row+1 < max_range and arr[row+1][col] == 0:
      arr[row+1][col] = 1
      fitness += 1
    if col-1 >= 0 and arr[row][col-1] == 0:
      arr[row][col-1] = 1
      fitness += 1
    if col+1 < max_range and arr[row][col+1] == 0:
      arr[row][col+1] = 1
      fitness += 1

  return fitness

def selection(pop, fitness):
  # Use any selection criteria and justify why you use that
  # The chromosomes with higher fitness have a higher probability of being selected
  combined = []
  for i in range(len(pop)):
    combined.append((pop[i], fitness[i]))

  # Ascending sort so top is worst 2
  combined.sort(key=lambda x: x[1])
  chromo1 = combined[0][0]
  chromo2 = combined[1][0]

  return chromo1, chromo2

def crossover(chromo1, chromo2):
  # Perform crossover on the selected chromosomes to create a new offspring
  offspring1 = chromo1[:3] + chromo2[3:]
  offspring2 = chromo2[:3] + chromo1[3:]
  return offspring1, offspring2

def mutation(chromo):
  # Mutate a chromosome return mut_chromo
  mut_chromo = []

  for set in chromo:
    X, Y = set
    col = X - 1
    row = Y - 1
    if row-1>=0:
      new_row = row - 1
    else:
      new_row = row
    mut_chromo.append((col + 1, new_row + 1))
  return mut_chromo

# Main function
def main():
  # Create a random initial population of 20 chromosomes
  max_range = 6
  population = [[(random.randint(1, max_range), random.randint(1, max_range)) for i in range(5)] for j in range(20)]
  print("Initial Population:")
  for pop in population:
    print(pop)

  gen_num = 1500
  
  # MAIN LOOP
  for i in range(gen_num):
    fitness = [calc_fitness(chromo, max_range) for chromo in population]
    chromo1, chromo2 = selection(population, fitness)
    offspring1, offspring2 = crossover(chromo1, chromo2)
    offspring1 = mutation(offspring1)
    population.remove(chromo1)
    population.remove(chromo2)
    population.append(offspring1)
    population.append(offspring2)

  final_fitness = [calc_fitness(chromo, max_range) for chromo in population]
  max_fit = max(final_fitness)
  best_idx = final_fitness.index(max_fit)
  best_chromosome = population[best_idx]

  print('\n--- FINAL RESULTS ---')
  print('Highest Fitness value:', max_fit)
  print('Best Chromosome:', best_chromosome)
main()