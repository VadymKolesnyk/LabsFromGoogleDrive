using System;
using GF256Library;

namespace Test_bench
{
    class Program
    {
        static void Main(string[] args)
        {
            GF256 a; 
            GF256 b;
            bool first = true;  // перевірка (a + b)^2 == a^2 + b^2
            bool second = true; // перевірка a + a == 0
            bool third = true;  // перевірка a * a^-1 == 1

            for (int i = 0; i < 256; i++)
            {
                a = i;
                for (int j = i; j < 256; j++)
                {
                    b = j;
                    if(((a + b)^2) != ((a^2) + (b^2)))
                        first = false;
                }
            }
            for (int i = 0; i < 256; i++)
            {
                a = i;
                if (a + a != 0)
                    second = false;   
            }
            for (int i = 1; i < 256; i++)
            {
                a = i;
                if (a * (a^-1) != 1)
                    third = false;
            }
            Console.WriteLine(first);
            Console.WriteLine(second);
            Console.WriteLine(third);
            a = 0;
            try
            {
                Console.WriteLine(a * (a ^ -1));
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine("Перехвачено исключение InvalidOperationException : " + e.Message);
            }
        }
    }
}
