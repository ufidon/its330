#!/usr/bin/env python
# references: https://en.wikipedia.org/wiki/Banker%27s_algorithm

# install numpy first
# Open a command prompt as Administrator, cd to the folder contains pip, for example
# cd "c:\Program Files\Python39\Scripts"
# pip.3.9.exe install numpy

import numpy as np

n_processes = int(input('Number of processes? '))
n_resources = int(input('Number of resource types? '))

current_available = [int(x) for x in input('Current available resources? ').split(' ')]

currently_allocated = np.array([[int(x) for x in input('Currently allocated for process ' + str(i + 1) + '? ').split(' ')] for i in range(n_processes)])
max_demand = np.array([[int(x) for x in input('Maximum demand from process ' + str(i + 1) + '? ').split(' ')] for i in range(n_processes)])

total_available = current_available + np.sum(currently_allocated, axis=0)

print("\n\nScenario overview:\n-------------------------\n")
print("Total available:\n", total_available)
print("Current available:\n", current_available)
print("Current allocated:\n", currently_allocated)
print("Maximum expected:\n", max_demand)
print("-------------------------\n\n")

running = np.ones(n_processes)  # An array with n_processes 1's to indicate if process is yet to run

while np.count_nonzero(running) > 0:
    at_least_one_allocated = False
    for p in range(n_processes):
        if running[p]:
            if all(i >= 0 for i in current_available - (max_demand[p] - currently_allocated[p])):
                at_least_one_allocated = True
                print('Process ' + str(p+1) + ' received resources:\n', max_demand[p] - currently_allocated[p])
                print('Process ' + str(p+1) + ' is running')
                running[p] = 0
                print('Process ' + str(p+1) + ' is complete')
                print('Process ' + str(p+1) + ' returned all its resourses:\n', currently_allocated[p])
                current_available += currently_allocated[p]
                print("Current available:\n", current_available)
                print("-------------------------\n")
    if not at_least_one_allocated:
        print('Unsafe')
        exit()
                
print('Safe')