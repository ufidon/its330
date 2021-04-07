/** hmac-sha256
* Ref:
* 1. https://docs.microsoft.com/en-us/dotnet/api/system.security.cryptography.hmacsha256?view=netframework-4.8
* How to compile & run?
* On Windows:
* Compile: csc hmacsha256.cs
* Run:
* 1. No data file provided: .\hmacsha256
* 2. Provide a data file: .\hmacsha256 <datafile name>
* On Ubuntu:
* Compile: mcs hmacsha256.cs
* Run:
* 1. No data file provided: ./hmacsha256.exe
* 2. Provide a data file: ./hmacsha256.exe <datafile name>
*/

using System;
using System.IO;
using System.Security.Cryptography;

public class HMACSHA256Gen
{
    static void showinhex(byte[] x, int len)
    {
        for (int i = 0; i < len; i++)
        {
            if(i%10 == 0)
            {
                Console.WriteLine();
            }
            Console.Write("{0:X2} ", x[i]);
        }
        Console.WriteLine("\n");
    }

    public static void Main(string[] Fileargs)
    {
        string dataFile;
        string hashFile;
        //If no file names are specified, create them.
        if (Fileargs.Length < 1)
        {
            dataFile = @"data.txt";
            hashFile = dataFile+".sha";

            if (!File.Exists(dataFile))
            {
                Console.WriteLine("1. No data file provided, one will be generated for you.\n");
                // Create a file to write to.
                using (StreamWriter sw = File.CreateText(dataFile))
                {
                    string content = "2. Here is a message to sign";
                    sw.WriteLine(content);
                    Console.WriteLine("2. The content in the generated data file {0} is:\n\n{1}\n", dataFile, content);
                }
                Console.WriteLine("2. The hash file for the data file {0} is {1}\n", dataFile, hashFile);
            }
        }
        else
        {
            dataFile = Fileargs[0];
            Console.WriteLine("1. The file to be digested: {0}", dataFile);
            hashFile = dataFile+".sha";
            Console.WriteLine("2. File {0} saves the HMACSHA256 hash of file {1}", hashFile, dataFile);
        }
        try
        {
            // Create a random key using a random number generator. This would be the
            //  secret key shared by sender and receiver.
            byte[] secretkey = new Byte[64];
            //RNGCryptoServiceProvider is an implementation of a random number generator.
            using (RNGCryptoServiceProvider rng = new RNGCryptoServiceProvider())
            {
                // The array is now filled with cryptographically strong random bytes.
                rng.GetBytes(secretkey);
                Console.WriteLine("3. The key for the HMAC-SHA256:");
                showinhex(secretkey, secretkey.Length);

                // Use the secret key to sign the message file.
                Console.WriteLine("4. Hashing file {0} with HMAC-SHA256...", dataFile);
                HashFile(secretkey, dataFile, hashFile);

                Console.WriteLine("5. The HMAC-SHA256 hash of {0} is saved in {1} together with its origninal content.\n\n", dataFile, hashFile);
                // Verify the signed file

                Console.WriteLine("6. Verifying the HMAC-SHA256 hash in {0} against {1}...", hashFile, dataFile);
                VerifyFile(secretkey, hashFile);
            }
        }
        catch (IOException e)
        {
            Console.WriteLine("2. Error: File not found", e);
        }
    }  //end main
    // Computes a keyed hash for a source file and creates a target file with the keyed hash
    // prepended to the contents of the source file. 
    public static void HashFile(byte[] key, String sourceFile, String destFile)
    {
        // Initialize the keyed hash object.
        using (HMACSHA256 hmac = new HMACSHA256(key))
        {
            using (FileStream inStream = new FileStream(sourceFile, FileMode.Open))
            {
                using (FileStream outStream = new FileStream(destFile, FileMode.Create))
                {
                    // Compute the hash of the input file.
                    byte[] hashValue = hmac.ComputeHash(inStream);

                    Console.WriteLine("5. The HMAC-SHA256 hash of file {0}:", sourceFile);
                    showinhex(hashValue, hashValue.Length);

                    // Reset inStream to the beginning of the file.
                    inStream.Position = 0;
                    // Write the computed hash value to the output file.
                    outStream.Write(hashValue, 0, hashValue.Length);
                    // Copy the contents of the sourceFile to the destFile.
                    int bytesRead;
                    // read 1K at a time
                    byte[] buffer = new byte[1024];
                    do
                    {
                        // Read from the wrapping CryptoStream.
                        bytesRead = inStream.Read(buffer, 0, 1024);
                        outStream.Write(buffer, 0, bytesRead);
                    } while (bytesRead > 0);
                }
            }
        }
        return;
    } // end HashFile

    // Compares the key in the source file with a new key created for the data portion of the file. If the keys 
    // compare the data has not been tampered with.
    public static bool VerifyFile(byte[] key, String sourceFile)
    {
        bool err = false;
        // Initialize the keyed hash object. 
        using (HMACSHA256 hmac = new HMACSHA256(key))
        {
            // Create an array to hold the keyed hash value read from the file.
            byte[] storedHash = new byte[hmac.HashSize / 8];
            // Create a FileStream for the source file.
            using (FileStream inStream = new FileStream(sourceFile, FileMode.Open))
            {
                // Read in the storedHash.
                inStream.Read(storedHash, 0, storedHash.Length);
                Console.WriteLine("6. The stored HMAC-SHA256 hash is:");
                showinhex(storedHash, storedHash.Length);
                // Compute the hash of the remaining contents of the file.
                // The stream is properly positioned at the beginning of the content, 
                // immediately after the stored hash value.
                byte[] computedHash = hmac.ComputeHash(inStream);
                Console.WriteLine("6. The computed HMAC-SHA256 hash is:");
                showinhex(computedHash, computedHash.Length);
                // compare the computed hash with the stored value

                for (int i = 0; i < storedHash.Length; i++)
                {
                    if (computedHash[i] != storedHash[i])
                    {
                        err = true;
                    }
                }
            }
        }
        if (err)
        {
            Console.WriteLine("6. Hash values differ! Hashed file has been tampered with!");
            return false;
        }
        else
        {
            Console.WriteLine("6. Hash values agree -- no tampering occurred.");
            return true;
        }
    } //end VerifyFile
} //end class
