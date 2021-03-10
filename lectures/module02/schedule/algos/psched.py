#!/usr/bin/env python
# -*- coding: utf-8 -*-

# references: 
# 1. https://en.wikipedia.org/wiki/Scheduling_(computing)
# 2. https://pandas.pydata.org/pandas-docs/stable/user_guide/10min.html
# 3. https://stackoverflow.com/questions/49854796/select-the-inverse-index-in-pd-dataframe
# 4. https://stackoverflow.com/questions/15315452/selecting-with-complex-criteria-from-pandas-dataframe
# 5. https://realpython.com/python-exceptions/
# 6. https://www.geeksforgeeks.org/align-columns-to-left-in-pandas-python/
# 7. https://stackoverflow.com/questions/59453091/left-align-the-first-column-and-center-align-the-other-columns-in-a-pandas-table

# install numpy and pandas first
# Open a command prompt as Administrator, cd to the folder contains pip, for example
# cd "c:\Program Files\Python39\Scripts"
# pip.3.9.exe install numpy pandas

import numpy as np
import pandas as pd

debug = False

def getScene():
    # get process scene
    nqs = int(input('Number of processes? '))

    print('\nEnter the information for each process in this order:\nArrivalTime BurstTime Priority \nseparate with blank space:\n')
    arrscene = np.array([[int(x) for x in input('Process ' + str(i) + ': ').split(' ')] for i in range(nqs)])

    # show processes gotten
    clabel = np.array(['Arrival Time', 'Burst Time', 'Priority'])
    rlabel = ['P'+str(i) for i in range(nqs)]
    df = pd.DataFrame(arrscene, rlabel, clabel)

    print('\nHere is the scene entered:\n')
    print(df)
    return  df


def FCFS(df):
    print('\nFirst Come First Serve:')
    # sort processes by arrival time
    sdf = df.sort_values(by=['Arrival Time'], ascending=True)
    if debug:
        print("\nProcesses sorted by arrival time:")
        print(sdf)

    
    nqs = sdf.shape[0]

    sdf['Waiting time'] = 0
    sdf['Remain Time'] = sdf['Burst Time']
    sdf['Arrived'] = False
    sdf['Done'] = False
    sdf['Gantt chart'] = ''
    sdf['Order'] = range(nqs)
    clabel = sdf.columns.tolist()

    #sdf.style.set_properties(**{'text-align': 'center'})
    #sdf.style.set_properties(subset=["Gantt chart"], **{'text-align': 'left'})

    if debug:
        print("\nProcesses sorted by arrival time:")
        print(sdf)

    cpu = 0
    oncpu = 0
    while not all(sdf['Done']):
        if debug:
            print('\nCPU time: {0}'.format(cpu))
        #if not all(sdf['Arrived']):
        # Gantt chart legend: u - unarrived; w - wait; x - run
        # unarrived
        selection = (sdf['Arrival Time'] > cpu) & (sdf['Arrived'] == False)
        try:
            sdf.loc[selection, 'Gantt chart'] += 'u'
        except:
            pass
        # arrived
        sdf.loc[sdf['Arrival Time'] == cpu, 'Arrived'] = True

        # for alignment
        sdf.loc[sdf['Done'] == True, 'Gantt chart'] += '-'

        # move cpu through the waiting queue
        if sdf.iat[oncpu, clabel.index('Arrived')] == True and sdf.iat[oncpu, clabel.index('Done')] == False:
            sdf.iat[oncpu, clabel.index('Gantt chart')] += 'x'
            sdf.iat[oncpu, clabel.index('Remain Time')] -= 1

            if oncpu < nqs:
                selection = (sdf['Order'] > oncpu) & (sdf['Arrived'] == True)
                try:
                    sdf.loc[selection, 'Gantt chart'] += 'w'
                    sdf.loc[selection, 'Waiting time'] += 1
                except:
                    pass

            if sdf.iat[oncpu, clabel.index('Remain Time')] == 0:
                sdf.iat[oncpu, clabel.index('Done')] = True
                oncpu += 1
        if debug:
            print(sdf)

        cpu += 1

    sdf.loc[:,'Turnaround time'] = sdf['Burst Time'] + sdf['Waiting time']
    print('All processes finished:')
    print(sdf.loc[:, ['Arrival Time','Burst Time','Priority','Waiting time', 'Turnaround time', 'Gantt chart']].sort_index())
    print("Total waiting time: ", sdf['Waiting time'].sum())
    print("Average waiting time: ", sdf['Waiting time'].sum()/nqs)
    print("Total turnaround time: ", sdf['Turnaround time'].sum())
    print("Average turnaround time: ", sdf['Turnaround time'].sum()/nqs)


def SJF(df, preemptive=False):
    if preemptive:
        print('\nPreemptive Shortest Remaining Time First:')
    else:
        print('\nNon-preemptive Shortest Remaining Time First:')

    # sort processes by arrival time then burst time
    sdf = df.sort_values(by=['Arrival Time','Burst Time'], ascending=[True,True])

    if debug:
        print("\nProcesses sorted by arrival time then burst time:")
        print(sdf)

    
    nqs = sdf.shape[0]

    sdf['Waiting time'] = 0
    sdf['Remain Time'] = sdf['Burst Time']
    sdf['Arrived'] = False
    sdf['Done'] = False
    sdf['Gantt chart'] = ''
    sdf['Order'] = range(nqs)
    clabel = sdf.columns.tolist()

    #sdf.style.set_properties(**{'text-align': 'center'})
    #sdf.style.set_properties(subset=["Gantt chart"], **{'text-align': 'left'})

    if debug:
        print("\nProcesses sorted by arrival time then remain time:")
        print(sdf)

    cpu = 0
    oncpu = 0
    cpufree = True
    while not all(sdf['Done']):
        if debug:
            print('\nCPU time: {0}'.format(cpu))
        #if not all(sdf['Arrived']):
        # Gantt chart legend: u - unarrived; w - wait; x - run
        # unarrived
        selection = (sdf['Arrival Time'] > cpu) & (sdf['Arrived'] == False)
        try:
            sdf.loc[selection, 'Gantt chart'] += 'u'
        except:
            pass
        # arrived
        sdf.loc[sdf['Arrival Time'] == cpu, 'Arrived'] = True
        # find the shortest remaining time again
        if any(sdf['Arrival Time'] == cpu):
            if preemptive or (not preemptive and cpufree):
                sdf.sort_values(by=['Arrived', 'Remain Time'], ascending = [False, True], inplace=True)
                sdf['Order'] = range(nqs)


        # for alignment
        sdf.loc[sdf['Done'] == True, 'Gantt chart'] += '-'

        # move cpu through the waiting queue
        if sdf.iat[oncpu, clabel.index('Arrived')] == True and sdf.iat[oncpu, clabel.index('Done')] == False:
            sdf.iat[oncpu, clabel.index('Gantt chart')] += 'x'
            sdf.iat[oncpu, clabel.index('Remain Time')] -= 1
            cpufree = False

            if oncpu < nqs:
                selection = (sdf['Order'] > oncpu) & (sdf['Arrived'] == True)
                try:
                    sdf.loc[selection, 'Gantt chart'] += 'w'
                    sdf.loc[selection, 'Waiting time'] += 1
                except:
                    pass

            if sdf.iat[oncpu, clabel.index('Remain Time')] == 0:
                sdf.iat[oncpu, clabel.index('Done')] = True
                cpufree = True

                oncpu += 1
        if debug:
            print(sdf)

        cpu += 1

    sdf.loc[:,'Turnaround time'] = sdf['Burst Time'] + sdf['Waiting time']
    print('All processes finished:')
    print(sdf.loc[:, ['Arrival Time','Burst Time','Priority','Waiting time', 'Turnaround time', 'Gantt chart']].sort_index())
    print("Total waiting time: ", sdf['Waiting time'].sum())
    print("Average waiting time: ", sdf['Waiting time'].sum()/nqs)
    print("Total turnaround time: ", sdf['Turnaround time'].sum())
    print("Average turnaround time: ", sdf['Turnaround time'].sum()/nqs)


# larger number means higher priority
def PP(df, preemptive=False):
    if preemptive:
        print('\nPreemptive Priority-based schedule:')
    else:
        print('\nNon-preemptive Priority-based schedule:')

    # sort processes by arrival time then Priority
    sdf = df.sort_values(by=['Arrival Time','Priority'], ascending=[True,False])

    if debug:
        print("\nProcesses sorted by arrival time then priority:")
        print(sdf)

    
    nqs = sdf.shape[0]

    sdf['Waiting time'] = 0
    sdf['Remain Time'] = sdf['Burst Time']
    sdf['Arrived'] = False
    sdf['Done'] = False
    sdf['Gantt chart'] = ''
    sdf['Order'] = range(nqs)
    clabel = sdf.columns.tolist()

    #sdf.style.set_properties(**{'text-align': 'center'})
    #sdf.style.set_properties(subset=["Gantt chart"], **{'text-align': 'left'})

    if debug:
        print("\nProcesses sorted by arrival time then priority:")
        print(sdf)

    cpu = 0
    oncpu = 0
    cpufree = True
    while not all(sdf['Done']):
        if debug:
            print('\nCPU time: {0}'.format(cpu))
        #if not all(sdf['Arrived']):
        # Gantt chart legend: u - unarrived; w - wait; x - run
        # unarrived
        selection = (sdf['Arrival Time'] > cpu) & (sdf['Arrived'] == False)
        try:
            sdf.loc[selection, 'Gantt chart'] += 'u'
        except:
            pass
        # arrived
        sdf.loc[sdf['Arrival Time'] == cpu, 'Arrived'] = True
        # find the highest priority again
        if any(sdf['Arrival Time'] == cpu):
            if preemptive or (not preemptive and cpufree):
                sdf.sort_values(by=['Arrived', 'Priority'], ascending = [False, False], inplace=True)
                sdf['Order'] = range(nqs)

        # for alignment
        sdf.loc[sdf['Done'] == True, 'Gantt chart'] += '-'

        # move cpu through the waiting queue
        if sdf.iat[oncpu, clabel.index('Arrived')] == True and sdf.iat[oncpu, clabel.index('Done')] == False:
            sdf.iat[oncpu, clabel.index('Gantt chart')] += 'x'
            sdf.iat[oncpu, clabel.index('Remain Time')] -= 1
            cpufree = False

            if oncpu < nqs:
                selection = (sdf['Order'] > oncpu) & (sdf['Arrived'] == True)
                try:
                    sdf.loc[selection, 'Gantt chart'] += 'w'
                    sdf.loc[selection, 'Waiting time'] += 1
                except:
                    pass

            if sdf.iat[oncpu, clabel.index('Remain Time')] == 0:
                sdf.iat[oncpu, clabel.index('Done')] = True
                cpufree = True
                
                # if not preemptive:
                #     sdf.iat[oncpu, clabel.index('sPriority')] = -1 # out of schedule
                #     sdf.sort_values(by=['sPriority', 'Arrived'], ascending = [False, False], inplace=True)
                #     sdf['Order'] = range(nqs)

                oncpu += 1
        if debug:
            print(sdf)

        cpu += 1

    sdf.loc[:,'Turnaround time'] = sdf['Burst Time'] + sdf['Waiting time']
    print('All processes finished:')
    print(sdf.loc[:, ['Arrival Time','Burst Time','Priority','Waiting time', 'Turnaround time', 'Gantt chart']].sort_index())
    print("Total waiting time: ", sdf['Waiting time'].sum())
    print("Average waiting time: ", sdf['Waiting time'].sum()/nqs)
    print("Total turnaround time: ", sdf['Turnaround time'].sum())
    print("Average turnaround time: ", sdf['Turnaround time'].sum()/nqs)

def RR(df, qu=2):
    # sort processes by arrival time
    print('\nRound Robin schedule with quantum {0}:'.format(qu))
    sdf = df.sort_values(by=['Arrival Time'], ascending=True)

    if debug:
        print("\nProcesses sorted by arrival time:")
        print(sdf)

    
    nqs = sdf.shape[0]

    sdf['Waiting time'] = 0
    sdf['Remain Time'] = sdf['Burst Time']
    sdf['Arrived'] = False
    sdf['Done'] = False
    sdf['Quantum'] = 0
    sdf['Gantt chart'] = ''
    sdf['Order'] = range(nqs)
    clabel = sdf.columns.tolist()

    #sdf.style.set_properties(**{'text-align': 'center'})
    #sdf.style.set_properties(subset=["Gantt chart"], **{'text-align': 'left'})

    if debug:
        print("\nProcesses sorted by arrival time:")
        print(sdf)

    cpu = 0
    oncpu = 0
    while not all(sdf['Done']):
        if debug:
            print('\nCPU time: {0}'.format(cpu))
        #if not all(sdf['Arrived']):
        # Gantt chart legend: u - unarrived; w - wait; x - run
        # unarrived
        selection = (sdf['Arrival Time'] > cpu) & (sdf['Arrived'] == False)
        try:
            sdf.loc[selection, 'Gantt chart'] += 'u'
        except:
            pass
        # arrived
        sdf.loc[sdf['Arrival Time'] == cpu, 'Arrived'] = True


        # for alignment
        sdf.loc[sdf['Done'] == True, 'Gantt chart'] += '-'

        # move cpu through the waiting queue
        if sdf.iat[oncpu, clabel.index('Arrived')] == True and sdf.iat[oncpu, clabel.index('Done')] == False:
            sdf.iat[oncpu, clabel.index('Gantt chart')] += 'x'
            sdf.iat[oncpu, clabel.index('Remain Time')] -= 1
            sdf.iat[oncpu, clabel.index('Quantum')] += 1

            if oncpu < nqs:
                selection = (sdf['Order'] != oncpu) & (sdf['Arrived'] == True) & (sdf['Done'] == False)
                try:
                    sdf.loc[selection, 'Gantt chart'] += 'w'
                    sdf.loc[selection, 'Waiting time'] += 1
                except:
                    pass

            if sdf.iat[oncpu, clabel.index('Remain Time')] == 0:
                sdf.iat[oncpu, clabel.index('Done')] = True
                sdf.iat[oncpu, clabel.index('Quantum')] = 0
                oncpu += 1
            elif sdf.iat[oncpu, clabel.index('Quantum')] % qu == 0 and not sdf.iat[oncpu, clabel.index('Done')]:
                sdf.iat[oncpu, clabel.index('Quantum')] = 0
                oncpu += 1

            oncpu %= nqs
            while sdf.iat[oncpu, clabel.index('Done')] and not all(sdf['Done']):
                oncpu += 1
                oncpu %= nqs
        # advance cpu time
        cpu += 1

        if debug:
            print(sdf)
        

    sdf.loc[:,'Turnaround time'] = sdf['Burst Time'] + sdf['Waiting time']
    print('All processes finished:')
    print(sdf.loc[:, ['Arrival Time','Burst Time','Priority','Waiting time', 'Turnaround time', 'Gantt chart']].sort_index())
    print("Total waiting time: ", sdf['Waiting time'].sum())
    print("Average waiting time: ", sdf['Waiting time'].sum()/nqs)
    print("Total turnaround time: ", sdf['Turnaround time'].sum())
    print("Average turnaround time: ", sdf['Turnaround time'].sum()/nqs)

if __name__ == '__main__':
    # test 
    df = getScene()
    FCFS(df.copy())
    SJF(df.copy())
    SJF(df.copy(), True)
    PP(df.copy())
    PP(df.copy(), True)
    RR(df.copy(), 2)
