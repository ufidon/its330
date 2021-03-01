#!/usr/bin/env python
# -*- coding: utf-8 -*-

# First In First Out (FIFO) Page Replacement algorithm
# the operating system keeps track of all pages in the memory in a queue, 
# the oldest page is in the front of the queue. 
# When a page needs to be replaced page in the front of the queue 
# is selected for removal.
# Python implementation
# Refs: 
# 1. https://www.geeksforgeeks.org/page-replacement-algorithms-in-operating-systems/
# 2. https://stackoverflow.com/questions/38086774/does-the-for-in-loop-construct-preserve-order
import sys

def FIFO(pagenum, processes):
	hits = 0
	misses = 0
	pages = [' ']*pagenum
	i = 0
	fifo = []

	for p in processes: 
		# If p is not present in Pages 
		if p not in pages:
			# increment Page faults
			misses +=1
			# Check if pages are used up
			if(len(fifo) == pagenum): 
				pages[fifo[0]] = p
				fifo.pop(0)
				fifo.append(pages.index(p))
			else: 
				pages[i] = p
				fifo.append(i)
			print('☐',p,(pages, fifo, misses, hits))

		# If page is already there 
		else:
			hits += 1		
			print('☑',p,(pages, fifo, misses, hits))
		i += 1

	return (misses,hits)

if __name__ == '__main__':
	# test code 
	pagenum = 4
	#processes = [ 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2] 
	processes = ['h', 'a', 'b', 'c', 'a', 'd', 'a', 'e', 'c', 'd', 'a', 'd', 'c']

	# usage: pFIFO.py pagenum processes
	if len(sys.argv) > 1:
		pagenum = int(sys.argv[1])
		processes = sys.argv[2:]

	misses = 0
	hits = 0
	(misses,hits)=FIFO(pagenum, processes)