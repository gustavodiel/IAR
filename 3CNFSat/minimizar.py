from random import randint, random, choice, seed
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from datetime import datetime

from instance_file_handler import fetch_instances, read_instance
from helpers import *
from solvers import *


## Initial config
seed(datetime.now())
sns.set_style("darkgrid")

###### Options ######

MAX_ITERATIONS = 25000

NUM_REPETITIONS = 1

START_TEMPERATURE = 10
FINAL_TEMPERATURE = 0.00001

SA_MAX = 1

#####################


def process_instance(path, name):
    print("Processing {}".format(name))

    lines = read_instance(path)

    clauses = []
    for line in lines:
        if line.startswith("p"):
            _, _, n_vars, expected_right = line.split()
            n_vars = int(n_vars)
            expected_right = int(expected_right)

        elif line.startswith("%"):
            break

        elif not line.startswith("c"):
            v1, v2, v3, _ = line.split()
            clauses.append([to_tuple(v1), to_tuple(v2), to_tuple(v3)])

    mean, std = random_search(
        name, expected_right, clauses, n_vars, MAX_ITERATIONS, NUM_REPETITIONS
    )
    print("RS: Media: {}\nDesvio padrao: {}".format(mean, std))

    mean, std = simmulated_annealing(
        name,
        expected_right,
        clauses,
        n_vars,
        START_TEMPERATURE,
        FINAL_TEMPERATURE,
        SA_MAX,
        MAX_ITERATIONS,
        NUM_REPETITIONS,
    )
    print("SA: Media: {}.\nDesvio padrao: {}".format(mean, std))


for instance in fetch_instances():
    path = instance["path"]
    name = instance["name"]
    process_instance(path, name)


# filename = "{}.cnf".format(instance)
# with open(filename, 'r') as file:
#     all_lines = file.readlines()
