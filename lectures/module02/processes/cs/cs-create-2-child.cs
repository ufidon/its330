// ref: http://code217.blogspot.com/2014/12/create-child-processes-in-parallel-and.html
// ref: https://docs.microsoft.com/en-us/dotnet/api/system.threading.tasks.parallel.for?view=netframework-4.8

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ProcessWait
{
    class Program
    {
        static void Main(string[] args)
        {
            const int CHILDREN_NUM = 2;
            string [] programs  = new string[CHILDREN_NUM] { "C:\\WINDOWS\\system32\\mspaint.exe", "C:\\WINDOWS\\system32\\notepad.exe"};

            try
            {

                Console.WriteLine("Parent process started executing...");
                Console.WriteLine("Parent process is creating child processes...");

                Parallel.For(0, CHILDREN_NUM, iIndex =>
                {
                    Console.WriteLine("Child process {0} started", iIndex);
                    NewProcess(iIndex, programs[iIndex]);
                });

                Console.WriteLine("All child processes completed. Waiting for user to press the enter key !!!");
                Console.Read();

                Console.WriteLine("Parent process completed execution.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.Read();
        }

        private static void NewProcess(int iIndex, string program)
        {
            Process oRunIndex = new Process();
            oRunIndex.StartInfo.FileName = program;
            oRunIndex.StartInfo.WorkingDirectory = @"c:\";
            oRunIndex.StartInfo.CreateNoWindow = false;
            oRunIndex.StartInfo.Arguments = string.Format("{0}", iIndex);

            oRunIndex.Start();
            oRunIndex.WaitForExit();
        }
    }

}