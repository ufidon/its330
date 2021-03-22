#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Best-Fit memory allocation algorithm
#  allocates the process to a partition 
# which is the greatest sufficient partition among the free available partitions.
# Python implementation
# Refs: 
# 1. https://www.geeksforgeeks.org/partition-allocation-methods-in-memory-management/
# 2. https://www.geeksforgeeks.org/worst-fit-allocation-in-operating-systems/
# 3. https://www.geeksforgeeks.org/program-worst-fit-algorithm-memory-management/
# 4. https://stackoverflow.com/questions/38086774/does-the-for-in-loop-construct-preserve-order

import sys

# each memory blocks can NOT hold more than one process
def WorstFit(memblocks, processes):
	procnum = len(processes)
	blocknum = len(memblocks)
	# indexes of the allocated memblocks to processes
	alloc = [-1]*procnum
	free = [1]*blocknum

	for p in range(procnum):
		bigmems = [memblocks[i] for i in range(blocknum) if memblocks[i] >= processes[p] and free[i]]
		try:
			maxmem = max(bigmems)
			
			maxdex = memblocks.index(maxmem)
			while not free[maxdex]:
				maxdex = memblocks.index(maxmem, maxdex+1)

			alloc[p] = maxdex
			free[maxdex] = 0
			print("{0}|".format(p), processes[p]," --> {0}|".format(maxdex),memblocks[maxdex])
			#print((alloc, free))
		except:
			pass

	unallocprocs = [(i, processes[i]) for i in range(procnum) if alloc[i] == -1]
	pfreeblocks = [(i,memblocks[i]) for i in range(blocknum) if free[i]]
	freeblocks = [memblocks[i] for i in range(blocknum) if free[i]]
	print("Unallocated processes: ", unallocprocs)
	print("Free memory blocks: ", pfreeblocks)
	print("External fragments: ", sum(freeblocks))

	ifragments = [memblocks[alloc[i]] - processes[i] for i in range(procnum) if alloc[i] != -1]
	print("Internal fragments: ", sum(ifragments))

	return (unallocprocs, freeblocks)

# each memory blocks CAN hold more than one process
def mWorstFit(memblocks, processes):
	procnum = len(processes)
	blocknum = len(memblocks)
	omems = memblocks.copy()
	# indexes of the allocated memblocks to processes
	alloc = [-1]*procnum
	free = [1]*blocknum

	for p in range(procnum):
		bigmems = [memblocks[i] for i in range(blocknum) if memblocks[i] >= processes[p] ]
		try:
			maxmem = max(bigmems)

			maxdex = memblocks.index(maxmem)

			alloc[p] = maxdex
			free[maxdex] = 0
			print("{0}|".format(p), processes[p]," --> {0}|".format(maxdex),omems[maxdex])

			# extra space
			memblocks[maxdex] -= processes[p]
			#print((alloc, free))
		except:
			pass

	unallocprocs = [(i,processes[i]) for i in range(procnum) if alloc[i] == -1]
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
	
	#memblocks = [100, 500, 500, 200]
	#processes = [417, 112, 300, 95, 95] 

	if len(sys.argv)>3 and ":" in sys.argv:
		si = sys.argv.index(":")
		memblocks = list(map(int, sys.argv[1:si]))
		processes = list(map(int, sys.argv[si+1:]))
	else:
		memblocks = [int(x) for x in input('Enter memory blocks, separate by blanks:\n').split()]
		processes = [int(x) for x in input('Enter processes, separate by blanks:\n').split()]
    
	print("memory:  ", memblocks)
	print("process: ", processes)
	print("\nOne memory block can NOT hold more than one processes:")
	(unallocprocs, freeblocks)=WorstFit(memblocks, processes)

	print("\nOne memory block CAN hold more than one processes:")
	print("For reference only, do NOT use!")
	(unallocprocs, freeblocks)=mWorstFit(memblocks, processes)