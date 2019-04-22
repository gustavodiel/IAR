from random import randint, random, choice
import numpy as np

def to_tuple(n_str):
    n = int(n_str)
    return (abs(n)-1, n >= 0)

def disturb(solution):
    return [1 - var if random() < 0.01 else var for var in solution]

def evaluate(clause, solution):
    return any([solution[position] == value for position, value in clause])

def evaluate_all(clauses, solution):
    return np.sum([evaluate(clause, solution) for clause in clauses])

def generate_solution(n_vars):
    return [choice([True, False]) for _ in range(n_vars)]
