#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Disk scheduling is done by operating systems to schedule I/O requests arriving for the disk. 
# Disk scheduling is also known as I/O scheduling.

# Refs: 
# 1. https://www.geeksforgeeks.org/partition-allocation-methods-in-memory-management/
# 2. https://misc.flogisoft.com/bash/tip_colors_and_formatting

import sys
import numpy as np
import pandas as pd

class colornformat:
   FPURPLE = '\033[95m'
   FCYAN = '\033[96m'
   FDARKCYAN = '\033[36m'
   FBLUE = '\033[94m'
   FGREEN = '\033[92m'
   FYELLOW = '\033[93m'
   FRED = '\033[91m'
   FWHITE = '\033[97m'
   FBLACK = '\033[30m'
   FMAGENTA = '\033[35m'

   BLIGHTMAGENTA = '\033[105m'
   BCYAN = '\033[46m'
   BLIGHTCYAN = '\033[106m'
   BBLUE = '\033[44m'
   BGREEN = '\033[42m'
   BYELLOW = '\033[43m'
   BRED = '\033[41m'
   BWHITE = '\033[107m'
   BBLACK = '\033[40m'
   BMAGENTA = '\033[45m'

   BOLD = '\033[1m'
   UNDERLINE = '\033[4m'
   STRIKEOUT = '\033[9m'
   DIM = '\033[2m'
   BLINK = '\033[5m'
   INVERT = '\033[7m'
   HIDDEN = '\033[8m'

   RBOLD = '\033[21m'
   RUNDERLINE = '\033[24m'
   RSTRIKEOUT = '\033[29m'
   RDIM = '\033[22m'
   RBLINK = '\033[25m'
   RINVERT = '\033[27m'
   RHIDDEN = '\033[28m'

   END = '\033[0m'

# ncyls: number of cylinders of the disk, so the available cylinder numbers are 0 to ncyls-1
# lastcyl: last cylinder the header resided
# curcyl: current cylinder the header resides
# reqs: the queue of I/O request, sequence of cylinder number

def tidyinput(ncyls, curcyl, reqs, lastcyl=0):
	lreqs = reqs.copy()
	if (len(lreqs) > 0 and ncyls > 0 and ncyls > max(lreqs) 
		and lastcyl>=0 and lastcyl < ncyls and curcyl>= 0 
		and curcyl < ncyls and min(lreqs)>= 0 
		and len(set(lreqs)) == len(lreqs)):
		return True
	else:
		print('tidyinput.lreqs: ', reqs)
		print("Invalid inputs, input again.")
		return False

def cfprint(ncyls, curcyl, reqs, lastcyl, sorted = False):
	slcyls = str(ncyls-1)
	scurcyl = str(curcyl)
	slastcyl = str(lastcyl)
	sreqs = ' '.join([str(r) for r in reqs])

	cfstr = colornformat.DIM + '0' + colornformat.RDIM + ' ' +\
			colornformat.STRIKEOUT + slastcyl + ' ' + colornformat.RSTRIKEOUT + \
			colornformat.BLINK + scurcyl + ' ' + colornformat.RBLINK + \
			sreqs + ' ' + \
			colornformat.DIM + slcyls + \
			colornformat.END
	if sorted:
		reqs.insert(0, lastcyl)
		reqs.insert(0, curcyl)
		reqs.sort()

		strmid=''
		for r in reqs:
			if r == lastcyl:
				strmid += colornformat.STRIKEOUT + str(r) + colornformat.RSTRIKEOUT + ' '
			elif r == curcyl:
				strmid += colornformat.BLINK + str(r) + ' ' + colornformat.RBLINK
			else:
				strmid += str(r) + ' '
		
		cfstr = colornformat.DIM + '0' + ' ' + colornformat.RDIM + \
				strmid + \
				colornformat.DIM + slcyls + \
				colornformat.END
	print(cfstr)

def FCFS(ncyls, curcyl, reqs, lastcyl=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		exit(1)

	df = pd.DataFrame(columns=['from','to','moved'])

	oreqs = reqs.copy()
	reqs.insert(0, curcyl)
	nreqs = len(reqs)

	for i in range(nreqs - 1):
		df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]

	print('\nFCFS scheduling:')
	cfprint(ncyls, curcyl, oreqs, lastcyl)
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def SSTF(ncyls, curcyl, reqs, lastcyl=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		exit(1)

	df = pd.DataFrame(columns=['from','to','moved'])

	oreqs = reqs.copy()
	ocurcyl = curcyl
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
	cfprint(ncyls, ocurcyl, oreqs, lastcyl, sorted=True)
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def SCAN(ncyls, curcyl, reqs, lastcyl=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		exit(1)

	df = pd.DataFrame(columns=['from','to','moved'])

	oreqs = reqs.copy()
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
	cfprint(ncyls, curcyl, oreqs, lastcyl, sorted=True)
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def CSCAN(ncyls, curcyl, reqs, lastcyl=0, dirmatter=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		exit(1)

	df = pd.DataFrame(columns=['from','to','moved'])

	oreqs = reqs.copy()
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
				reqs.insert(0, 0)
				ci += 1

			i = 0
			while i<ci-1:
				df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
				i += 1
	else: # to left
		if ci > 0:
			df.loc[len(df.index)] = [reqs[ci], 0, np.abs(0-reqs[ci])]
			# cannot delete current request since CSCAN does NOT serve requests while moving left
			# del reqs[ci]
			if reqs[0] > 0:				
				reqs.insert(0, 0)
				nreqs += 1
				ci += 1 # not needed, for clarification only
		i = 0
		while i < nreqs-1:
			df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
			i += 1

	print('\nCSCAN scheduling:')
	if dirmatter:
		print("Initial direction matters\n")
	else:
		print("Initial direction does NOT matter\n")	
	cfprint(ncyls, curcyl, oreqs, lastcyl, sorted=True)
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def LOOK(ncyls, curcyl, reqs, lastcyl=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		exit(1)

	df = pd.DataFrame(columns=['from','to','moved'])

	oreqs = reqs.copy()
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
	cfprint(ncyls, curcyl, oreqs, lastcyl, sorted=True)
	print(df)
	total = df['moved'].sum()
	print("Total movements: ", total)

def CLOOK(ncyls, curcyl, reqs, lastcyl=0, dirmatter=0):
	if not tidyinput(ncyls, lastcyl, reqs, curcyl):
		exit(1)

	df = pd.DataFrame(columns=['from','to','moved'])

	oreqs = reqs.copy()
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
			# cannot delete current request since clook does NOT server while moving left
			# del reqs[ci]
			# nreqs -= 1
		i = 0
		while i < nreqs-1:
			df.loc[len(df.index)] = [reqs[i], reqs[i+1], np.abs(reqs[i+1]-reqs[i])]
			i += 1		

	print('\nCLOOK scheduling:')
	if dirmatter:
		print("Initial direction matters\n")
	else:
		print("Initial direction does NOT matter\n")
	cfprint(ncyls, curcyl, oreqs, lastcyl, sorted=True)
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
		curcyl = int(input('Enter the current cylinder number where the header sits:'))
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

