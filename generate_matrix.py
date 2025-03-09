import csv
import random
import sys

def generate_matrix(n, min_val=0, max_val=100):
    """Generates an n x n matrix filled with random integers."""
    return [[random.randint(min_val, max_val) for _ in range(n)] for _ in range(n)]

def write_matrix_to_csv(matrix, filename):
    """Writes a matrix to a CSV file."""
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(matrix)

def main():
    if len(sys.argv) != 3:
        print("Usage: python script.py <matrix_size> <output_filename>")
        sys.exit(1)
    
    n = int(sys.argv[1])
    filename = sys.argv[2]
    
    matrix = generate_matrix(n)
    write_matrix_to_csv(matrix, filename)
    print(f"Matrix written to {filename}")

if __name__ == "__main__":
    main()
