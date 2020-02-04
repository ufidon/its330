// Refs:
// https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process?view=netframework-4.8
// https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process.getcurrentprocess?view=netframework-4.8
// https://docs.microsoft.com/en-us/dotnet/api/system.threading.tasks.parallel.for?view=netframework-4.8
using System;
using System.Diagnostics;
using System.ComponentModel;
using System.Threading.Tasks;

namespace MyProcessSample
{
    class MyProcess
    {
        // Opens the Internet Explorer application.
        void OpenApplication(string myFavoritesPath)
        {
            // Start Internet Explorer. Defaults to the home page.
            Console.WriteLine("1. Start Internet Explorer. Defaults to the home page.");
             Process child1 = Process.Start("IExplore.exe");
            //child1.WaitForExit();


            // Display the contents of the favorites folder in the browser.
            /*
            Console.WriteLine("2. open favorite folder with file explorer.");
            Process child2 = Process.Start(myFavoritesPath);
            child2.WaitForExit();
            */
        }

        // Opens urls and .html documents using Internet Explorer.
        void OpenWithArguments()
        {
            // url's are not considered documents. They can only be opened
            // by passing them as arguments.
            Console.WriteLine("3. Start Internet Explorer. open an url.");
            Process child3 = Process.Start("IExplore.exe", "www.northwindtraders.com");
            //child3.WaitForExit();

            // Start a Web page using a browser associated with .html and .asp files.
            Console.WriteLine("4. Start Internet Explorer. open a htm web page.");
            Process child4 = Process.Start("IExplore.exe", "C:\\myPath\\myFile.htm");
            //child4.WaitForExit();

            Console.WriteLine("5. Start Internet Explorer. open an asp page.");
            Process child5 = Process.Start("IExplore.exe", "C:\\myPath\\myFile.asp");
            //child5.WaitForExit();
        }

        // Uses the ProcessStartInfo class to start new processes,
        // both in a minimized mode.
        void OpenWithStartInfo()
        {
            ProcessStartInfo startInfo = new ProcessStartInfo("IExplore.exe");
            startInfo.WindowStyle = ProcessWindowStyle.Maximized;

            Console.WriteLine("6. Start Internet Explorer. maximized.");
            //Process child6 = Process.Start(startInfo);
            //child6.WaitForExit();

            startInfo.Arguments = "www.northwindtraders.com";

            Console.WriteLine("7. Start Internet Explorer. open a website.");
            //Process child7 = Process.Start(startInfo);
            //child7.WaitForExit();
        }

        static void Main()
        {
            Console.WriteLine("0. Parent process begins. creates childrens...");
            Process parent = Process.GetCurrentProcess();
            // Get the path that stores favorite links.
            string myFavoritesPath =
                Environment.GetFolderPath(Environment.SpecialFolder.Favorites);

            MyProcess myProcess = new MyProcess();

            Parallel.For(0, 3, i=>
                {
                    myProcess.OpenApplication(myFavoritesPath);
                    myProcess.OpenWithArguments();
                    myProcess.OpenWithStartInfo();
                }
            );

            Console.WriteLine("Press ENTER to terminate the parent");
            Console.ReadKey();
            Console.WriteLine("X. Parent process terminated");
            //parent.WaitForExit();


        }
    }
}