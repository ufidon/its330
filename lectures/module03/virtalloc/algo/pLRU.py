#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Least Recently Used (LRU) Page Replacement algorithm
# page will be replaced which is least recently used
# Python implementation
# Refs: 
# 1. https://www.geeksforgeeks.org/program-for-least-recently-used-lru-page-replacement-algorithm/
# 2. https://stackoverflow.com/questions/38086774/does-the-for-in-loop-construct-preserve-order
import sys
import re

def LRU(pagenum, processes):
	hits = 0
	misses = 0
	pages = [' ']*pagenum
	i = 0
	lru = []

	#print("Number of frames: ",pagenum)
	#print("Page references: ",processes, '\n')

	for p in processes: 
		# If p is not present in Pages 
		if p not in pages:
			# increment Page faults
			misses +=1
			# Check if pages are used up
			if(len(lru) == pagenum): 
				pages[lru[0]] = p
				lru.pop(0)
				lru.append(pages.index(p))
			else: 
				pages[i] = p
				lru.append(i)
			print('☐',p,(pages, lru, misses, hits))

		# If page is already there 
		else:
			hits += 1		
			lru.pop(lru.index(pages.index(p)))
			lru.append(pages.index(p))
			print('☑',p,(pages, lru, misses, hits))
		i += 1

	return (misses,hits)

if __name__ == '__main__':
	# test code 
	framenum = 4
	#pagerefs = [ 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2] 
	#pagerefs = ['h', 'a', 'b', 'c', 'a', 'd', 'a', 'e', 'c', 'd', 'a', 'd', 'c']

	refasletter = False
	# usage: pFIFO.py framenum pagerefs
	if len(sys.argv) > 1:
		framenum = int(sys.argv[1])
		pagerefs = sys.argv[2:]
	else:
		framenum = int(input('Enter the number of frames: '))
		pagerefs = [int(x) for x in input('Enter the page reference sequences, separate by spaces:\n').split()]
		refasletter = True if re.search(r'[y|Y]', input('Represent page refs as letters(Yes|No): ')) else False
		if refasletter:
			lpagerefs = [chr(x+ord('a')) for x in pagerefs]
			print('Pageref as letters:\n',list(zip(pagerefs,lpagerefs)))
			pagerefs = lpagerefs

	misses = 0
	hits = 0
	print('\nAlgorithm started...\n')
	(misses,hits)=LRU(framenum, pagerefs)