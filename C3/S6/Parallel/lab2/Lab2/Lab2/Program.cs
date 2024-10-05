using System;

#pragma warning disable CS4014 // Так как этот вызов не ожидается, выполнение существующего метода продолжается до тех пор, пока вызов не будет завершен
namespace Lab2
{
    internal class Program
    {
        private static void Main()
        {
            Generator generator = new Generator();
            generator.StartAsync();
            while (Console.ReadKey().Key != ConsoleKey.Spacebar);
        }
    }
}
