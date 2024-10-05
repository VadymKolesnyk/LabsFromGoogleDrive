using System;
using System.IO;

namespace Archiver
{
    class Program
    {
        static void Main(string[] args)
        { 
            Arcive.Do(1000);
            Unarchive.Do(1000);
        }
    }
}
