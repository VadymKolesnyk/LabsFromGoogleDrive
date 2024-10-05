using System;

namespace lab2
{
    class Program
    {
        static int count = 0;
        static void Main(string[] args)
        {
            FuncAnalyzer funcAnalyzer = new FuncAnalyzer
            {
                Function = x => x * x - (1 + 4) * x + 4,
                Accuracy = 0.0001M,
                StatrtStep = 0.0001M,
                RadiusSearch = 100
            };
            funcAnalyzer.TGCalculated += (senser, e) => count++;
            decimal startPoint = 4M;
            Console.WriteLine("F(x) = x * x - (1 + 4) * x + 4");
            Console.WriteLine("Початкова точка: {0:0.0000}",startPoint);

            Console.WriteLine("Розмiр кроку\ta\t\tb\t\tКОЦФ (ДСК)\tКОЦФ (МЗП)\tЗагальна КОЦФ\tТочка мiнiмуму");
            for (decimal h = 10M; h >= 0.0001M; h *= 0.1M) 
            {
                count = 0;
                funcAnalyzer.StatrtStep = h;
                var (a, b) = funcAnalyzer.Localizate(startPoint);
                var DSK = count;
                var res = funcAnalyzer.SearchMinimum(a,b);
                var zagal = count;
                Console.WriteLine("{0:0.0000}\t\t{1,7:0.0000}\t\t{2,7:0.0000}\t\t{3}\t\t{4}\t\t{5}\t\t{6,7:0.0000}", h, a, b, DSK, zagal - DSK, zagal, res);
            }

            startPoint = 0M;
            Console.WriteLine("\n\nF(x) = |-3 * x * x + 4 * x - 1| - 4");
            Console.WriteLine("Початкова точка: {0:0.0000}", startPoint);
            funcAnalyzer.Function = x => Math.Abs(-3 * x * x + 4 * x - 1) - 4;
            Console.WriteLine("Розмiр кроку\ta\t\tb\t\tКОЦФ (ДСК)\tКОЦФ (МЗП)\tЗагальна КОЦФ\tТочка мiнiмуму");
            for (decimal h = 1M; h >= 0.0001M; h *= 0.1M)
            {
                count = 0;
                funcAnalyzer.StatrtStep = h;
                var (a, b) = funcAnalyzer.Localizate(startPoint);
                var DSK = count;
                var res = funcAnalyzer.SearchMinimum(a, b);
                var zagal = count;
                Console.WriteLine("{0:0.0000}\t\t{1,-8: 0.0000;-0.0000}\t{2,7:0.0000}\t\t{3}\t\t{4}\t\t{5}\t\t{6,7:0.0000}", h, a, b, DSK, zagal - DSK, zagal, res);
            }


        }
    }
}
