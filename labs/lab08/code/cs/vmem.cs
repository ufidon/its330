/** Program:
* Process.VirtualMemorySize64 Property
* Gets the amount of the virtual memory, in bytes, allocated for the associated process.
* How to compile & run?

* On Ubuntu:
* Compile: mcs vmem.cs
* Run: ./vmem.exe 
* pay attention to the program output for a while, then close mate-calc started by vmem.exe
* record the program output and explain

* On Windows:
* Goto Line 36, change mate-calc to notepad.exe
* Compile: csc vmem.cs
* Run: .\vmem.exe
* pay attention to the program output for a while, then close notepad.exe started by vmem.exe
* record the program output and explain
*/

using System;
using System.Diagnostics;

namespace ProcessSample
{
    class ProcessMonitorSample
    {
        public static void Main()
        {
            // Define variables to track the peak
            // memory usage of the process.
            long peakPagedMem   = 0,
                 peakWorkingSet = 0,
                 peakVirtualMem = 0;

            // Start the process.
            using (Process myProcess = Process.Start("mate-calc"))
            {
                // Display the process statistics until
                // the user closes the program.
                do
                {
                    if (!myProcess.HasExited)
                    {
                        // Refresh the current process property values.
                        myProcess.Refresh();

                        Console.WriteLine();

                        // Display current process statistics.

                        Console.WriteLine($"{myProcess} -");
                        Console.WriteLine("-------------------------------------");

                        Console.WriteLine($"  Physical memory usage     : {myProcess.WorkingSet64}");
                        Console.WriteLine($"  Base priority             : {myProcess.BasePriority}");
                        Console.WriteLine($"  Priority class            : {myProcess.PriorityClass}");
                        Console.WriteLine($"  User processor time       : {myProcess.UserProcessorTime}");
                        Console.WriteLine($"  Privileged processor time : {myProcess.PrivilegedProcessorTime}");
                        Console.WriteLine($"  Total processor time      : {myProcess.TotalProcessorTime}");
                        Console.WriteLine($"  Paged system memory size  : {myProcess.PagedSystemMemorySize64}");
                        Console.WriteLine($"  Paged memory size         : {myProcess.PagedMemorySize64}");

                        // Update the values for the overall peak memory statistics.
                        peakPagedMem   = myProcess.PeakPagedMemorySize64;
                        peakVirtualMem = myProcess.PeakVirtualMemorySize64;
                        peakWorkingSet = myProcess.PeakWorkingSet64;

                        if (myProcess.Responding)
                        {
                            Console.WriteLine("Status = Running");
                        }
                        else
                        {
                            Console.WriteLine("Status = Not Responding");
                        }
                    }
                }
                while (!myProcess.WaitForExit(1000));

                Console.WriteLine();
                Console.WriteLine($"  Process exit code          : {myProcess.ExitCode}");

                // Display peak memory statistics for the process.
                Console.WriteLine($"  Peak physical memory usage : {peakWorkingSet}");
                Console.WriteLine($"  Peak paged memory usage    : {peakPagedMem}");
                Console.WriteLine($"  Peak virtual memory usage  : {peakVirtualMem}");
            }
        }
    }
}

/**
* Refs:
* 1. https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process.virtualmemorysize64?view=netframework-4.8
*/