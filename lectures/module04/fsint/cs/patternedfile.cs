/** Ref: https://docs.microsoft.com/en-us/dotnet/standard/io/how-to-enumerate-directories-and-files
* The following example uses 
* the Directory.EnumerateFiles(String, String, SearchOption) method 
* to recursively enumerate all file names in a directory and subdirectories 
* that match a certain pattern. 
* It then reads each line of each file and displays the lines 
* that contain a specified string, with their filenames and paths.
* How to compile & run?
* On Windows:
* Compile: csc patternedfile.cs 
* Run: .\patternedfile <path or folder or directory name> <target string>
* 1. create several text files contain any contents
* 2. .\patternedfile.exe . THIS
* 3. Try several times: change the path name and target string above then run
* 
* On Ubuntu:
* Compile: mcs patternedfile.cs 
* Run: ./patternedfile <path or folder or directory name> <target string>
* 1. create several text files contain any contents
* 2. ./patternedfile.exe . THIS
* 3. Try several times: change the path name and target string above then run
*/

using System;
using System.IO;
using System.Linq;

class Program
{
    static void Main(string[] args)
    {
        try
        {
			string docPath = ".\\";
            if(args.Length == 1)
			{
				docPath = args[0];
			}
				

			string strTarget = "TEST";
            if(args.Length == 2)
			{
				strTarget = args[1];
			}
		


            var files = from file in Directory.EnumerateFiles(docPath, "*.txt", SearchOption.AllDirectories)
                        from line in File.ReadLines(file)
                        where line.Contains("TEST")
                        select new
                        {
                            File = file,
                            Line = line
                        };

            foreach (var f in files)
            {
                Console.WriteLine($"{f.File}\t{f.Line}");
            }
            Console.WriteLine($"{files.Count().ToString()} files found.");
        }
        catch (UnauthorizedAccessException uAEx)
        {
            Console.WriteLine(uAEx.Message);
        }
        catch (PathTooLongException pathEx)
        {
            Console.WriteLine(pathEx.Message);
        }
    }
}