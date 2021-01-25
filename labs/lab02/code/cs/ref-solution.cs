// ref: http://code217.blogspot.com/2014/12/create-child-processes-in-parallel-and.html

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
            // number of processes
            const int CHILDREN_NUM = 4;

            // programs to be loaded
            string[] progs = {
                "C:\\WINDOWS\\system32\\mspaint.exe", 
                "C:\\WINDOWS\\system32\\SnippingTool.exe",
                "C:\\Windows\\system32\\charmap.exe",
                //"C:\\Windows\\system32\\eventvwr.exe",
                "C:\\WINDOWS\\explorer.exe"};
            try
            {

                Console.WriteLine("Parent process started executing...");
                Console.WriteLine("Parent process is starting child processes...");
                Parallel.For(0, CHILDREN_NUM, iIndex =>
                {
                    Console.WriteLine("Child process {0} started", iIndex);
                    NewProcess(iIndex, progs[iIndex]);
                });
                Console.WriteLine("All child processes completed.Waiting for user to press the enter key !!!");
                Console.Read();
                /*
                Console.WriteLine("Parent process to continue execution.");
                for (int iIndex = 0; iIndex < 10000; iIndex++)
                {
                    Console.WriteLine(iIndex.ToString());
                }
                */
                Console.WriteLine("Parent process completed execution.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
            Console.Read();
        }

        private static void NewProcess(int iIndex, string progname)
        {
            Process oRunIndex = new Process();
            oRunIndex.StartInfo.FileName = progname;
            oRunIndex.StartInfo.WorkingDirectory = @"c:\";
            oRunIndex.StartInfo.CreateNoWindow = true;
            //oRunIndex.StartInfo.Arguments = string.Format("{0}", iIndex);
            oRunIndex.StartInfo.Arguments = null;

            oRunIndex.Start();
            oRunIndex.WaitForExit();
        }
    }

}