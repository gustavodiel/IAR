import numpy as np

from helpers import *

def update_temperature(iteration, max_iterations, initial_temperature, final_temperature):
    return (initial_temperature - final_temperature) / (np.cosh(10 * iteration / max_iterations)) + final_temperature


def random_search(name, expected_right, clauses, num_vars, max_iterations, repetitions):
    total_scores = []

    for r in range(repetitions):

        local_scores = []

        solution = generate_solution(num_vars)
        solution_FO = evaluate_all(clauses, solution)

        for i in range(max_iterations):

            new_solution = generate_solution(num_vars)
            new_score = evaluate_all(clauses, new_solution)

            local_scores.append(expected_right - new_score)

            if new_score > solution_FO:
                solution = new_solution
                solution_FO = new_score

        total_scores.append(local_scores)

    np_scores = np.array(total_scores)

    convergence = pd.DataFrame(
        np_scores.mean(axis=0), np.arange(max_iterations), columns=["clausulas"]
    )

    plot_convergence(convergence, "random_search", name)

    return np_scores.mean(), np_scores.std()


def simmulated_annealing(
    name,
    expected_right,
    clauses,
    num_vars,
    initial_temperature,
    final_temperature,
    SAMax,
    max_iterations,
    repetitions,
):
    total_scores = []

    for r in range(repetitions):
        temperature = initial_temperature

        solution = generate_solution(num_vars)
        solution_FO = evaluate_all(clauses, solution)

        iteration = 0

        local_scores = []

        while iteration < max_iterations:
            for i in range(SAMax):
                new_solution = disturb(solution)
                new_score = evaluate_all(clauses, new_solution)

                delta = solution_FO - new_score

                if delta < 0 or random() < np.exp(-delta / temperature):
                    solution = new_solution
                    solution_FO = new_score

            temperature = update_temperature(
                iteration, max_iterations, initial_temperature, final_temperature
            )

            local_scores.append(expected_right - solution_FO)

            iteration += 1
        total_scores.append(local_scores)

    np_scores = np.array(total_scores)

    convergence = pd.DataFrame(
        np_scores.mean(axis=0), np.arange(max_iterations), columns=["clausulas"]
    )

    plot_convergence(convergence, "simulated_anealing", name)

    return np_scores.mean(), np_scores.std()
