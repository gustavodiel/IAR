from random import randint, random, choice
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd


def to_tuple(n_str):
    n = int(n_str)
    return (abs(n) - 1, n >= 0)


def disturb(solution):
    return [1 - var if random() < 0.01 else var for var in solution]


def evaluate(clause, solution):
    return any([solution[position] == value for position, value in clause])


def evaluate_all(clauses, solution):
    return np.sum([evaluate(clause, solution) for clause in clauses])


def generate_solution(n_vars):
    return [choice([True, False]) for _ in range(n_vars)]


def plot_convergence(df, name, instance, cenario):
    df.index.name = "Iterações"

    fig, ax = plt.subplots()
    fig.set_size_inches(30, 8.27)
    sns.lineplot(x=df.index, y="clausulas", data=df, lw=0.4, ax=ax, estimator=None)
    sns.despine()
    fig.savefig("resultados/{}_{}_{}_convergence.png".format(instance, name, cenario))

    fig, ax = plt.subplots()
    fig.set_size_inches(30, 8.27)
    sns.lineplot(x=df.index, y="clausulas", data=df.rolling(1000).mean(), ax=ax)
    sns.despine()
    fig.savefig("resultados/{}_{}_{}_convergence_agg.png".format(instance, name, cenario))
