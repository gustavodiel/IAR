import numpy as np

from helpers import *

def update_temperature(iteration, max_iterations, initial_temperature, final_temperature):
    return (initial_temperature-final_temperature)/(np.cosh(10*i/max_iterations)) + final_temperature

def random_search(clauses, num_vars, max_iterations, repetitions):
    scores = []

    for r in range(repetitions):

        solution = generate_solution(num_vars)
        solution_FO = evaluate_all(clauses, solution)

        for i in range(max_iterations):

            new_solution = generate_solution(num_vars)
            new_score = evaluate_all(clauses, new_solution)

            if new_score > solution_FO:
                solution = new_solution
                solution_FO = new_score

            scores.append(solution_FO)

    np_scores = np.array(scores)

    return np_scores.mean(), np_scores.std()

def simmulated_annealing(clauses, num_vars, initial_temperature, final_temperature, SAMax, repetitions):
    scores = []

    for r in range(repetitions):
        temeprature = initial_temperature

        solution = generate_solution(num_vars)
        solution_FO = evaluate_all(clauses, solution)

        while temperature > final_temperature:
            for i in range(SAMax):
                new_solution = disturb(solution)
                new_score = evaluate_all(clauses, new_solution)

                delta = solution_FO - new_score

                if delta < 0 or random() < np.exp(-delta / temperature):
                    solution = new_solution
                    solution_FO = new_score

                scores.append(solution_FO)

    np_scores = np.array(scores)

    return np_scores.mean(), np_scores.std()
