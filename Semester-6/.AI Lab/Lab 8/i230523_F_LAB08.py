# Checking if current assignment satisfies capacity constraint or not
def is_valid(assignment, city_capacity):
    city_counts = {'A': 0, 'B': 0, 'C': 0}
    
    for city in assignment.values():
        city_counts[city] += 1
        if city_counts[city] > city_capacity[city]:
            return False
            
    return True

# Backtracking
def backtrack(assignment, packages, allowed_cities, city_capacity):
    # If all packages are assigned, it means a solution is found
    if len(assignment) == len(packages):
        return assignment
        
    # Finding unassigned package
    unassigned_package = None
    for package in packages:
        if package not in assignment:
            unassigned_package = package
            break
            
    # Assigning allowed cities to selected package
    for city in allowed_cities[unassigned_package]:
        assignment[unassigned_package] = city
        
        # Check if assignment is valid
        if is_valid(assignment, city_capacity):
            result = backtrack(assignment, packages, allowed_cities, city_capacity)
            if result is not None:
                return result
                
        # Backtrack
        del assignment[unassigned_package]
        
    return None

# ----------- MAIN -----------
def main():
    # Inputs
    packages = [1, 2, 3, 4]
    city_capacity = {'A': 2, 'B': 3, 'C': 1}
    allowed_cities = { 1: ['A', 'B'], 2: ['B', 'C'], 3: ['A', 'C'], 4: ['A'] }

    # Using backtracking
    assignment = {}
    solution = backtrack(assignment, packages, allowed_cities, city_capacity)

    print('\nFINAL RESULTS:')
    if solution:
        final_output = {'A': [], 'B': [], 'C': []}
        for package, city in solution.items():
            final_output[city].append(package)
            
        for city in final_output:
            final_output[city].reverse()

        print(final_output)
    else:
        print("No valid solution found! :(")

main()