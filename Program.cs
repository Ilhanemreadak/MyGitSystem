using System;
using System.IO;
using System.IO.Compression;
using System.Reflection.Metadata;
using System.Security.Cryptography;
using System.Text;

if (args.Length < 1)
{
    Console.WriteLine("Please provide a command.");
    return;
}

// You can use print statements as follows for debugging, they'll be visible when running tests.
Console.Error.WriteLine("Logs from your program will appear here!");

string command = args[0];

if (command == "init")
{
    // Uncomment this block to pass the first stage
    //
    Directory.CreateDirectory(".git");
    Directory.CreateDirectory(".git/objects");
    Directory.CreateDirectory(".git/refs");
    File.WriteAllText(".git/HEAD", "ref: refs/heads/main\n");
    Console.WriteLine("Initialized git directory");
}
else if (command == "list_args")
{
    foreach (var arg in args)
    {
        Console.WriteLine(arg);
    }
}
else if (command == "cat-file") // Check if the command is cat-file
{
    switch (args[1]) // Check the flag
    {
        case "-p": // Check if the flag is -p
            {
                var hash = args[2]; // Get the hash of the object
                var filePath = Path.Combine(".git", "objects", hash.Substring(0, 2), hash.Substring(2)); // Path to the object file

                using FileStream fs = File.OpenRead(filePath); // Open the object file
                using ZLibStream zLibStream = new(fs, CompressionMode.Decompress); // Decompress the object file
                using var content = new StreamReader(zLibStream); // Read the content of the object

                Console.Write((content.ReadToEnd()).Split('\0')[1]); // Print the content of the object
                break;
            }
    }
}

else if (command == "hash-object") // Check if the command is hash-object
{
    switch (args[1])
    {
        case "-w": // Check if the flag is -w
            {
                // blob <size>\0<content> - Create a blob object
                var path = args[2]; // Content of the object
                byte[] content = File.ReadAllBytes(path); // Read the content of the object

                var blobBytes = new List<byte>();
                var size = content.Length;
                string blob = $"blob {size}\0"; // Blob object
                blobBytes.AddRange(Encoding.UTF8.GetBytes(blob)); // Convert the object to bytes
                blobBytes.AddRange(content); // Add the content of the object

                HashAlgorithm sha1 = SHA1.Create(); // Create a SHA1 hash

                byte[] hash = sha1.ComputeHash(blobBytes.ToArray()); // Compute the hash of the object
                var hashString = BitConverter.ToString(hash).Replace("-", "").ToLower(); // Convert the hash to a string

                using MemoryStream output = new MemoryStream();
                using (ZLibStream zLibStream = new(output, CompressionLevel.Optimal))
                {
                    zLibStream.Write(blobBytes.ToArray(), 0, blobBytes.ToArray().Length); // Write the object to the compressed file
                }

                var objectDir = Path.Combine(".git", "objects", hashString.Substring(0, 2)); // Path to the object directory
                var objectPath = Path.Combine(objectDir, hashString.Substring(2)); // Path to the object file

                Directory.CreateDirectory(objectDir); // Create object directory

                File.WriteAllBytes(objectPath, output.ToArray()); // Write the object to the file

                Console.Write(hashString); // Print the hash of the object
                break;
            }
    }
}

else
{
    throw new ArgumentException($"Unknown command {command}");
}