#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Disk scheduling is done by operating systems to schedule I/O requests arriving for the disk. 
# Disk scheduling is also known as I/O scheduling.

# Refs: 
# 1. https://www.geeksforgeeks.org/partition-allocation-methods-in-memory-management/

import sys
import numpy as np
import pandas as pd

# ncyls: number of cylinders of the disk, so the available cylinder numbers are 0 to ncyls-1
# lastcyl: last cylinder the header resided
# curcyl: current cylinder the header resides
# reqs: the queue of I/O request, sequence of cylinder number

def tidyinput(ncyls, curcyl, reqs, lastcyl=0):
	if (len(reqs) > 0 and ncyls > 0 and ncyls > max(reqs) 
		and lastcyl>=0 and lastcyl < ncyls and curcyl>= 0 
		and curcyl < ncyls and min(reqs)>= 0 
		and len(set(reqs)) == len(reqs)):
		return True
	else:
		print("Invalid inputs, input again.")
		return False


def FCFS(ncyls, curcyl, reqs, lastcyl=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		return

	df = pd.DataFrame(columns=['from','to','moved'])

	reqs.insert(0, curcyl)
	nreqs = len(reqs)

	for i in range(nreqs - 1):
		df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]

	print('\nFCFS scheduling:')
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def SSTF(ncyls, curcyl, reqs, lastcyl=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		return

	df = pd.DataFrame(columns=['from','to','moved'])

	reqs.insert(0, curcyl)
	reqs.sort()

	while len(reqs) > 1:
		ci = reqs.index(curcyl)
		nreqs = len(reqs)
		if ci == 0:	
			for i in range(nreqs - 1):
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
			break
		elif ci == nreqs - 1:
			i = ci
			while i > 0:
				df.loc[len(df.index)] = [reqs[i], reqs[i-1], np.abs(reqs[1]-reqs[i-1])]
			break
		else:
			if np.abs(reqs[ci]-reqs[ci-1]) > np.abs(reqs[ci+1]-reqs[ci]):
				df.loc[len(df.index)] = [reqs[ci], reqs[ci+1], np.abs(reqs[ci]-reqs[ci+1])]
				curcyl = reqs[ci+1]
			else:
				df.loc[len(df.index)] = [reqs[ci], reqs[ci-1], np.abs(reqs[ci]-reqs[ci-1])]
				curcyl = reqs[ci-1]
			reqs.pop(ci)


	print('\nSSTF scheduling:')
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def SCAN(ncyls, curcyl, reqs, lastcyl=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		return

	df = pd.DataFrame(columns=['from','to','moved'])

	reqs.insert(0, curcyl)
	reqs.sort()

	toright = True if lastcyl < curcyl else False

	ci = reqs.index(curcyl)
	nreqs = len(reqs)

	if toright:
		if ci == 0:
			i = ci
			while i < nreqs-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
		else:
			if reqs[-1] < ncyls-1:
				reqs.append(ncyls-1)
				nreqs += 1
			i = ci
			while i < nreqs-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
			df.loc[len(df.index)] = [reqs[i], reqs[ci-1], np.abs(reqs[i]-reqs[ci-1])]
			ci -= 1
			i = ci
			while i>0:
				df.loc[len(df.index)] = [reqs[i], reqs[i-1], np.abs(reqs[i]-reqs[i-1])]
				i -= 1
	else: # to left
		if ci == nreqs - 1:
			i = ci
			while i>0:
				df.loc[len(df.index)] = [reqs[i], reqs[i-1], np.abs(reqs[i]-reqs[i-1])]
				i -= 1
		else:
			if reqs[0] > 0:
				reqs.insert(0, 0)
				nreqs += 1
				ci += 1
			i = ci
			while i>0:
				df.loc[len(df.index)] = [reqs[i], reqs[i-1], np.abs(reqs[i]-reqs[i-1])]
				i -= 1
			df.loc[len(df.index)] = [reqs[i], reqs[ci+1], np.abs(reqs[ci+1]-reqs[i])]
			ci += 1
			i = ci
			while i < nreqs -1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1

	print('\nSCAN scheduling:')
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def CSCAN(ncyls, curcyl, reqs, lastcyl=0, dirmatter=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		return

	df = pd.DataFrame(columns=['from','to','moved'])

	reqs.insert(0, curcyl)
	reqs.sort()

	toright = False if dirmatter and lastcyl > curcyl else True

	ci = reqs.index(curcyl)
	nreqs = len(reqs)

	if toright:
		if ci == 0:
			i = ci
			while i < nreqs-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
		else:
			if reqs[-1] < ncyls-1:
				reqs.append(ncyls-1)
				nreqs += 1
			i = ci
			while i < nreqs-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1

			df.loc[len(df.index)] = [reqs[i], 0, np.abs(0 - reqs[i])]

			if reqs[0] > 0:
				df.loc[len(df.index)] = [reqs[i], 0, np.abs(reqs[i])]
				reqs.insert(0, 0)
				ci += 1

			i = 0
			while i<ci-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
	else: # to left
		if ci > 0:
			df.loc[len(df.index)] = [reqs[ci], 0, np.abs(0-reqs[ci])]
			if reqs[0] > 0:				
				reqs.insert(0, 0)
				nreqs += 1
		i = 0
		while i < nreqs-1:
			df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
			i += 1

	print('\nCSCAN scheduling:')
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def LOOK(ncyls, curcyl, reqs, lastcyl=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		return

	df = pd.DataFrame(columns=['from','to','moved'])

	reqs.insert(0, curcyl)
	reqs.sort()

	toright = True if lastcyl < curcyl else False

	ci = reqs.index(curcyl)
	nreqs = len(reqs)

	if toright:
		if ci == 0:
			i = ci
			while i < nreqs-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
		else:
			i = ci
			while i < nreqs-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
			df.loc[len(df.index)] = [reqs[i], reqs[ci-1], np.abs(reqs[i]-reqs[ci-1])]
			ci -= 1
			i = ci
			while i>0:
				df.loc[len(df.index)] = [reqs[i], reqs[i-1], np.abs(reqs[i]-reqs[i-1])]
				i -= 1
	else: # to left
		if ci == nreqs - 1:
			i = ci
			while i>0:
				df.loc[len(df.index)] = [reqs[i], reqs[i-1], np.abs(reqs[i]-reqs[i-1])]
				i -= 1
		else:
			i = ci
			while i>0:
				df.loc[len(df.index)] = [reqs[i], reqs[i-1], np.abs(reqs[i]-reqs[i-1])]
				i -= 1
			df.loc[len(df.index)] = [reqs[i], reqs[ci+1], np.abs(reqs[ci+1]-reqs[i])]
			ci += 1
			i = ci
			while i < nreqs -1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1

	print('\nLOOK scheduling:')
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def CLOOK(ncyls, curcyl, reqs, lastcyl=0, dirmatter=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		return

	df = pd.DataFrame(columns=['from','to','moved'])

	reqs.insert(0, curcyl)
	reqs.sort()

	toright = False if dirmatter and lastcyl > curcyl else True

	ci = reqs.index(curcyl)
	nreqs = len(reqs)

	if toright:
		if ci == 0:
			i = ci
			while i < nreqs-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
		else:
			i = ci
			while i < nreqs-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1

			df.loc[len(df.index)] = [reqs[i], reqs[0], np.abs(reqs[i]-reqs[0])]

			i = 0
			while i<ci-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
	else: # to left
		if ci > 0:
			df.loc[len(df.index)] = [reqs[ci], reqs[0], np.abs(reqs[0]-reqs[ci])]
		i = 0
		while i < nreqs-1:
			df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
			i += 1		

	print('\nCLOOK scheduling:')
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

if __name__ == '__main__':
	# test code
	
	# ncyls = 200
	# lastcyl = 0
	# curcyl = 10
	# reqs = [0, 100,50, 30,103, 20, 99, 188] 

	if len(sys.argv)>5 and ":" in sys.argv:
		si = sys.argv.index(":")
		ncyls,lastcyl,curcyl = list(map(int, sys.argv[1:si]))
		reqs = list(map(int, sys.argv[si+1:]))
	else:
		ncyls = int(input('Enter the total number of cylinders:'))
		curcyl = int(input('Enter the total current cylinder number where the header sits:'))
		reqs = [int(x) for x in input('Enter the sequence of I/O requests, separate by blanks:\n').split()]

	FCFS(ncyls, curcyl, reqs.copy())
	SSTF(ncyls, curcyl, reqs.copy())
	CSCAN(ncyls, curcyl, reqs.copy())
	CLOOK(ncyls, curcyl, reqs.copy())
	lastcyl = int(input('\nSCAN: Enter the last cylinder number where the header located:'))
	SCAN(ncyls, curcyl, reqs.copy(), lastcyl)
	CSCAN(ncyls, curcyl, reqs.copy(), lastcyl, dirmatter=1)
	LOOK(ncyls, curcyl, reqs.copy(), lastcyl)
	CLOOK(ncyls, curcyl, reqs.copy(), lastcyl, dirmatter=1)
	lastcyl = int(input('\nSCAN: Enter the last cylinder number where the header located:'))
	SCAN(ncyls, curcyl, reqs.copy(), lastcyl)
	CSCAN(ncyls, curcyl, reqs.copy(), lastcyl, dirmatter=1)
	LOOK(ncyls, curcyl, reqs.copy(),lastcyl)
	CLOOK(ncyls, curcyl, reqs.copy(), lastcyl, dirmatter=1)

