#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Optimal Page Replacement Algorithm (OPT) Page Replacement algorithm
# page will be replaced which would not be used for 
# the longest duration of time in the future.
# Python implementation
# 1. If referred page is already present, increment hit count.
# 2. If not present, find if a page that is never referenced in future. 
# 	 If such a page exists, replace this page with new page. 
# 	 If no such page exists, find a page that is referenced farthest in future. 
# 	 Replace this page with new page.
# Refs: 
# 1. https://www.geeksforgeeks.org/optimal-page-replacement-algorithm/
# 2. https://stackoverflow.com/questions/38086774/does-the-for-in-loop-construct-preserve-order
# 3. https://realpython.com/null-in-python/
import sys

def predict(loaded, unref):
	furthest = 0
	# there is at least one page in loaded is NOT in unref
	for p in loaded:
		if p not in unref:
			furthest = loaded.index(p)
			return furthest
	# all pages in loaded are also in unref
	indexes = [unref.index(p) for p in loaded]
	furthest = loaded.index(unref[max(indexes)])

	return furthest

def OPT(pagenum, processes):
	hits = 0
	misses = 0
	pages = [' ']*pagenum
	i = 0
	opt = []
	unref = processes.copy()
	furthest = 0

	print("Number of pages: ",pagenum)
	print("Processes: ",processes)

	for p in processes: 
		unref.pop(0)
		# If p is not present in Pages 
		if p not in pages:
			# increment Page faults
			misses +=1
			# Check if pages are used up
			if(len(opt) == pagenum): 
				# replacement happens
				furthest = predict(pages, unref)
				pages[furthest] = p
				opt.pop(furthest)
				opt.append(furthest)
			else: 
				pages[i] = p
				opt.append(i)
			print('☐',p,(pages, opt, misses, hits))

		# If page is already there 
		else:
			hits += 1
			opt.pop(0)
			opt.append(pages.index(p))
			print('☑',p,(pages, opt, misses, hits))
		i += 1
		

	return (misses,hits)

if __name__ == '__main__':
	# test code 
	pagenum = 4
	#processes = [ 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2] 
	processes = ['h', 'a', 'b', 'c', 'a', 'd', 'a', 'e', 'c', 'd', 'a', 'd', 'c']

	# usage: pOPT.py pagenum processes
	if len(sys.argv) > 1:
		pagenum = int(sys.argv[1])
		processes = sys.argv[2:]

	misses = 0
	hits = 0
	(misses,hits)=OPT(pagenum, processes)