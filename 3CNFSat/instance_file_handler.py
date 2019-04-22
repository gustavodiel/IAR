from os import listdir
from os.path import isfile, join, splitext

def fetch_instances():
    INSTANCES_FOLDER = 'instances/'
    return [{'path': INSTANCES_FOLDER + f, 'name': splitext(f)[0]} for f in listdir(INSTANCES_FOLDER) if isfile(join(INSTANCES_FOLDER, f))]

def read_instance(filename):
    with open(filename, 'r') as file:
        all_lines = file.readlines()
    return all_lines
