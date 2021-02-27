#!/usr/bin/env python
# -*- coding: utf-8 -*-

# First-Fit memory allocation algorithm
# first process claims the first available memory with space more than or equal to it’s size
# Python implementation
# Refs: 
# 1. https://www.geeksforgeeks.org/partition-allocation-methods-in-memory-management/
# 2. https://www.geeksforgeeks.org/program-first-fit-algorithm-memory-management/
# 3. https://www.geeksforgeeks.org/first-fit-allocation-in-operating-systems/
# 4. https://www.geeksforgeeks.org/first-fit-algorithm-in-memory-management-using-linked-list/
# 5. https://stackoverflow.com/questions/38086774/does-the-for-in-loop-construct-preserve-order

import sys

# each memory blocks can NOT hold more than one process
def FirstFit(memblocks, processes):
	procnum = len(processes)
	blocknum = len(memblocks)
	# indexes of the allocated memblocks to processes
	alloc = [-1]*procnum
	free = [1]*blocknum

	for p in range(procnum):
		for m in range(blocknum):
			if processes[p] <= memblocks[m] and free[m]:
				alloc[p] = m
				free[m] = 0
				print("{}|".format(p), processes[p]," --> {0}|".format(m),memblocks[m])
				#print((alloc, free))
				break

	unallocprocs = [(i, processes[i]) for i in range(procnum) if alloc[i] == -1]
	pfreeblocks = [(i, memblocks[i]) for i in range(blocknum) if free[i]]
	freeblocks = [memblocks[i] for i in range(blocknum) if free[i]]
	print("Unallocated processes: ", unallocprocs)
	print("Free memory blocks: ", pfreeblocks)
	print("External fragments: ", sum(freeblocks))

	ifragments = [memblocks[alloc[i]] - processes[i] for i in range(procnum) if alloc[i] != -1]
	
	print("Internal fragments: ", sum(ifragments))

	return (unallocprocs, freeblocks)

# each memory blocks CAN hold more than one process
def mFirstFit(memblocks, processes):
	procnum = len(processes)
	blocknum = len(memblocks)
	omems = memblocks.copy()
	# indexes of the allocated memblocks to processes
	alloc = [-1]*procnum
	free = [1]*blocknum

	for p in range(procnum):
		for m in range(blocknum):
			if processes[p] <= memblocks[m]:
				alloc[p] = m
				free[m] = 0
				print("{}|".format(p), processes[p]," --> {0}|".format(m),omems[m])

				# extra space
				memblocks[m] -= processes[p]
				#print((alloc, free))
				break

	unallocprocs = [(i, processes[i]) for i in range(procnum) if alloc[i] == -1]
	pfreeblocks = [(i,memblocks[i]) for i in range(blocknum) if free[i]]
	freeblocks = [memblocks[i] for i in range(blocknum) if free[i]]
	print("Unallocated processes: ", unallocprocs)
	print("Free memory blocks: ", pfreeblocks)
	print("External fragments: ", sum(freeblocks))

	ifragments = [memblocks[a] for a in set(alloc[i] for i in range(procnum) if alloc[i] != -1)]
	print("Internal fragments: ", sum(ifragments))

	return (unallocprocs, freeblocks)

if __name__ == '__main__':
	# test code
	
	memblocks = [100, 500, 500, 200]
	processes = [417, 112, 426, 95, 95] 

	if len(sys.argv)>3 and ":" in sys.argv:
		si = sys.argv.index(":")
		memblocks = list(map(int, sys.argv[1:si]))
		processes = list(map(int, sys.argv[si+1:]))
	print("memory:  ", memblocks)
	print("process: ", processes)
	print("\nOne memory block can NOT hold more than one processes:")
	(unallocprocs, freeblocks)=FirstFit(memblocks, processes)

	print("\nOne memory block CAN hold more than one processes:")
	print("For reference only, do NOT use!")
	(unallocprocs, freeblocks)=mFirstFit(memblocks, processes)