import random

# Initialize population with random allocations
def initialize_population(population_size, user_demands):
    population = []
    for _ in range(population_size):
        # Create random allocations for each user
        chromosome = [ [random.randint(1, max(user_demands[i])) for _ in range(len(user_demands[i]))] for i in range(len(user_demands))]
        population.append(chromosome)
    return population

def evaluate_population(population, user_demands, bandwidth):
    fitness_scores = []
    for chromosome in population:
        total_bandwidth = sum(sum(user) for user in chromosome)
        # Apply a penalty for exceeding bandwidth rather than zeroing out
        penalty = max(0, (total_bandwidth - bandwidth) * 0.5)  # Penalize for excess usage
        fitness = sum(min(chromosome[i][j], user_demands[i][j]) for i in range(len(chromosome)) for j in range(len(user_demands[i])))
        fitness_scores.append(fitness - penalty if total_bandwidth <= bandwidth * 1.5 else 0.1)  # Avoid zeroing fitness
    return fitness_scores

# Selection using a roulette wheel approach
def selection(population, fitness_scores):
    total_fitness = sum(fitness_scores)
    
    # Handle the case where total_fitness is zero
    if total_fitness == 0:
        return random.choices(population, k=len(population))
    
    selection_probs = [fitness / total_fitness for fitness in fitness_scores]
    selected = random.choices(population, weights=selection_probs, k=len(population))
    return selected

# Crossover between two parents to create offspring
def crossover(selected):
    next_generation = []
    for i in range(0, len(selected), 2):
        parent1, parent2 = selected[i], selected[i + 1]
        crossover_point = random.randint(1, len(parent1) - 1)
        offspring1 = parent1[:crossover_point] + parent2[crossover_point:]
        offspring2 = parent2[:crossover_point] + parent1[crossover_point:]
        next_generation.extend([offspring1, offspring2])
    return next_generation

# Mutate by randomly changing the allocation of a single slice for a user
def mutate(population, mutation_rate=0.2):
    for chromosome in population:
        if random.random() < mutation_rate:
            user_index = random.randint(0, len(chromosome) - 1)
            slice_index = random.randint(0, len(chromosome[user_index]) - 1)
            chromosome[user_index][slice_index] = random.randint(1, max(max(user) for user in chromosome))
    return population

# Return the best solution with the highest fitness score
def best_solution(population, user_demands, bandwidth):
    fitness_scores = evaluate_population(population, user_demands, bandwidth)
    best_index = fitness_scores.index(max(fitness_scores))
    return population[best_index], fitness_scores[best_index]

def genetic_algorithm(user_demands, bandwidth, population_size=100, generations=100, elite_size=5):
    population = initialize_population(population_size, user_demands)
    print(population)
    for generation in range(generations):
        fitness_scores = evaluate_population(population, user_demands, bandwidth)
        sorted_population = [chrom for _, chrom in sorted(zip(fitness_scores, population), reverse=True)]
        
        # Preserve top elite_size chromosomes directly
        elite = sorted_population[:elite_size]
        selected = selection(population, fitness_scores)
        
        population = crossover(selected)
        population = mutate(population)
        
        # Add the elites back
        population[:elite_size] = elite
    
    return best_solution(population, user_demands, bandwidth)
# Example usage:
user_demands = [[30, 40, 20], [20, 30, 10], [15, 20, 5]]  # Demand for each slice by multiple users
bandwidth = 80  # Total available bandwidth
best_allocation, best_fitness = genetic_algorithm(user_demands, bandwidth)
print("Best allocation:", best_allocation)
print("Best fitness score:", best_fitness)
