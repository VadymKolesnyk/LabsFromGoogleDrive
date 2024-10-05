using System;

namespace lab5
{
    class Program
    {
        static double F(double x) => x * x - (1 + 5) * x + 5;
        static double G(double x) => x * x * x * x - 14 * x * x * x + 60 * x * x - 70 * x;

        static void Main(string[] args)
        {
            double eps, a, b, l, x1, x2, f1, f2;
            eps = 0.001;
            a = 1;
            b = 4;

            l = b - a;

            x1 = a + 0.382 * l;
            x2 = b - 0.382 * l;

            f1 = F(x1);
            f2 = F(x2);
            Console.WriteLine("F(x) = x * x - (1 + 5) * x + 5");
            Console.WriteLine("Шаг\ta\tb\tx1\tx2\tf1\tf2\tl");
            Console.WriteLine("0\t{0:0.000}\t{1:0.000}\t{2:0.000}\t{3:0.000}\t{4:0.000}\t{5:0.000}\t{6:0.000}", a, b, x1, x2, f1, f2, l);
            for (int i = 1; b - a > eps; i++) 
            {
                if (f1 > f2)
                {
                    a = x1;
                    l = b - a;
                    x1 = x2;
                    f1 = f2;
                    x2 = b - 0.382 * l;
                    f2 = F(x2);
                }
                else
                {
                    b = x2;
                    l = b - a;
                    x2 = x1;
                    f2 = f1;
                    x1 = a + 0.382 * l;
                    f1 = F(x1);
                }
                Console.WriteLine("{0}\t{1:0.000}\t{2:0.000}\t{3:0.000}\t{4:0.000}\t{5:0.000}\t{6:0.000}\t{7:0.000}",i, a, b, x1, x2, f1, f2, l);

            }
            Console.WriteLine("Минимум в x = {0:0.000}", (a + b) / 2);
            Console.WriteLine();
            Console.WriteLine("G(x) = x * x * x * x - 14 * x * x * x + 60 * x * x - 70 * x");

            a = -1;
            b = 2;
            l = b - a;
            eps = 0.001;
            x1 = a + 0.382 * l;
            x2 = b - 0.382 * l;

            f1 = G(x1);
            f2 = G(x2);
            Console.WriteLine("Шаг\ta\tb\tx1\tx2\tg1\tg2\tl");
            Console.WriteLine("0\t{0:0.000}\t{1:0.000}\t{2:0.000}\t{3:0.000}\t{4:0.000}\t{5:0.000}\t{6:0.000}", a, b, x1, x2, f1, f2, l);
            for (int i = 1; b - a > eps; i++)
            {
                if (f1 > f2)
                {
                    a = x1;
                    l = b - a;
                    x1 = x2;
                    f1 = f2;
                    x2 = b - 0.382 * l;
                    f2 = G(x2);
                }
                else
                {
                    b = x2;
                    l = b - a;
                    x2 = x1;
                    f2 = f1;
                    x1 = a + 0.382 * l;
                    f1 = G(x1);
                }
                Console.WriteLine("{0}\t{1:0.000}\t{2:0.000}\t{3:0.000}\t{4:0.000}\t{5:0.000}\t{6:0.000}\t{7:0.000}", i, a, b, x1, x2, f1, f2, l);
            }
            Console.WriteLine("Минимум в x = {0:0.000}", (a + b) / 2);
        }
    }
}
