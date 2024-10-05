using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Lab4
{
    class Program
    {
        const int Size = 100;
        const int MaxValue = 100;

        static void Main(string[] args)
        {
            Random rand = new Random();
            var generator = Enumerable.Repeat(0, Size).Select(i => rand.Next(MaxValue)); // створюємо генератор випадковий послідовностей.

            var first = generator.ToList();  // заповнюємо 1 колекцію 
            var second = generator.ToList(); // заповнюємо 2 колекцію
            var third = generator.ToList();  // заповнюємо 3 колекцію

            // вивід на екран
            PrintList(first); 
            PrintList(second);
            PrintList(third);

            var taskFirst = Task.Run(() => first.Where(element => element > 0.4 * first.Max()).ToList()); // працюємо в окремому потоці над 1 колекцією 
            var taskSecond = Task.Run(() => second.Where(element => element % 3 == 0).ToList()); // працюємо в окремому потоці над 2 колекцією 
            var taskThird = Task.Run(() => third.Take(third.Count / 2).ToList()); // працюємо в окремому потоці над 3 колекцією
            // усюди як результат повертається оброблена колекція

            // коли всі колекції обробляться ...
            var res = Task.WhenAll(taskFirst, taskSecond, taskThird).ContinueWith((list) => // виконуємо цю функцію
            {
                //збереження результатів
                first = list.Result[0];
                second = list.Result[1];
                third = list.Result[2];

                Console.WriteLine();
                //вивід оброблний колекцій на екран
                PrintList(first);
                PrintList(second);
                PrintList(third);
            }).ContinueWith((t) => first.Distinct().Where(element => second.Contains(element) && third.Contains(element)).OrderBy(x => x).ToList()); // потім цю

            PrintList(res.Result); // вивід результатів
        }

        private static void PrintList(IEnumerable<int> result) // функція друку колекції
        {
            Console.Write("\n( ");
            foreach (var item in result)
                Console.Write($"{item,2} ");
            Console.WriteLine(")");      
        }
    }
}
