#!/usr/bin/env python3

from random import randint, random, choice, seed
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from datetime import datetime
import multiprocessing
import os

from instance_file_handler import fetch_instances, read_instance
from helpers import *
from solvers import *


## Initial config
seed(datetime.now())
sns.set_style("darkgrid")

###### Options ######

MAX_ITERATIONS = 50000

NUM_REPETITIONS = 5

START_TEMPERATURE = 1
FINAL_TEMPERATURE = 0.00001

SA_MAX = 10

#####################
def start():

    # Clear old results
    for file in os.scandir('resultados'):
        if file != '.gitkeep':
            os.unlink(file.path)

    instances = fetch_instances()

    jobs = []

    for instance in instances:
        path = instance["path"]
        name = instance["name"]

        process = multiprocessing.Process(target=process_instance,args=(path, name))
        jobs.append(process)

    for j in jobs:
        j.start()

    for j in jobs:
        j.join()

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

    # mean, std = random_search(name, expected_right, clauses, n_vars, MAX_ITERATIONS, NUM_REPETITIONS)
    # print("RS: Media: {}\nDesvio padrao: {}".format(mean, std))

    mean, std = simmulated_annealing( name, expected_right, clauses, n_vars, START_TEMPERATURE, FINAL_TEMPERATURE, SA_MAX, MAX_ITERATIONS, NUM_REPETITIONS)

    print("SA: Media: {}.\nDesvio padrao: {}".format(mean, std))


if __name__ == '__main__':
    start()
