using System;
using OptimizationMethods;
namespace lab2
{
    class Program
    {
        static int count = 0;
        static void Main(string[] args)
        {
            decimal phi2 = 4M;
            FuncAnalyzer funcAnalyzer = new FuncAnalyzer
            {
                Function = R2 => Pow(ElectricalFunc(R2) - phi2, 2),
                Accuracy = 0.0001M,
                StatrtStep = 1M,
                RadiusSearch = 10
            };
            funcAnalyzer.TGCalculated += (senser, e) => count++;
            decimal startPoint = 5M;
            Console.WriteLine("F(R2) = (E1 * (R2 + R3 + R4) / (R1 + R2 + R3 + R4) - phi2) ^ 2");
            Console.WriteLine("Початкова точка: {0:0.0000}", startPoint);

            count = 0;
            var (a, b) = funcAnalyzer.Localizate(startPoint);
            var DSK = count;

            var res = funcAnalyzer.SearchMinimum(a, b);
            var zagal = count;
            Console.WriteLine("\nРозмiр кроку\ta\t\tb\t\tКОЦФ (ДСК)\tКОЦФ (МЗП)\tЗагальна КОЦФ\tТочка мiнiмуму");
            Console.WriteLine("{0:0.0000}\t\t{1,7:0.0000}\t\t{2,7:0.0000}\t\t{3}\t\t{4}\t\t{5}\t\t{6,7:0.0000}", 
                                funcAnalyzer.StatrtStep, a, b, DSK, zagal - DSK, zagal, res);
        }
        private static decimal Pow(decimal x, int pow)
        {
            if(pow < 0)
            {
                pow = -pow;
                x = 1 / x;
            }
            decimal result = 1;
            for (int i = 1; i <= pow; i++)
            {
                result *= x;
            }
            return result;
        }
        public static decimal ElectricalFunc(decimal R2)
        {
            decimal R1 = 5, R3 = 5, R4 = 5;
            decimal E1 = 5;
            return E1 * (R2 + R3 + R4) / (R1 + R2 + R3 + R4);
        }
    }
}
