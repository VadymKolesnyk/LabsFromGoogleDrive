﻿using System;
using System.Linq;

#if DEBUG
#warning DEBUG is defined
#endif
namespace OptimizationMethods
{
    public class FuncAnalyzer
    {
        public FuncAnalyzer()
        {

        }
        private const decimal PHI = 0.381966011M;
        public Func<decimal, decimal> Function { get; set; }
        public decimal StatrtStep { get; set; }
        public decimal Accuracy { get; set; }
        public decimal RadiusSearch { get; set; }
        public event EventHandler TGCalculated;
        private decimal FucntionCalc(decimal x)
        {
            if (Function == null)
            {
                throw new ArgumentNullException("Функция null");
            }
            var res = Function(x);
            TGCalculated?.Invoke(this, new EventArgs());
            return res;
        }
        public decimal SearchMinimum(decimal leftBound, decimal rightBound)
        {
#if DEBUG
            Console.WriteLine("+-----------------------+");
            Console.WriteLine("|Метод золотого перетину|");
            Console.WriteLine("+-----------------------+");
            Console.WriteLine("Iтерацiя\ta\t\tb\t\tx1\t\tx2\t\tf1\t\tf2\t\tl");
#endif
            decimal length = rightBound - leftBound;
            decimal x1 = leftBound + PHI * length;
            decimal x2 = rightBound - PHI * length;
            decimal f1 = FucntionCalc(x1);
            decimal f2 = FucntionCalc(x2);
#if DEBUG
            Console.WriteLine($"0\t\t{leftBound,7:0.0000}\t\t{rightBound,7:0.0000}\t\t{x1,7:0.0000}\t\t{x2,7:0.0000}\t\t{f1,13:0.0000000000}\t{f2,13:0.0000000000}\t{length,7:0.0000}");
#endif
            for (int i = 1; rightBound - leftBound > Accuracy; i++)
            {
                if (f1 > f2)
                {
                    leftBound = x1;
                    length = rightBound - leftBound;
                    x1 = x2;
                    f1 = f2;
                    x2 = rightBound - PHI * length;
                    f2 = FucntionCalc(x2);
                }
                else
                {
                    rightBound = x2;
                    length = rightBound - leftBound;
                    x2 = x1;
                    f2 = f1;
                    x1 = leftBound + PHI * length;
                    f1 = FucntionCalc(x1);
                }
#if DEBUG
                Console.WriteLine($"{i}\t\t{leftBound,7:0.0000}\t\t{rightBound,7:0.0000}\t\t{x1,7:0.0000}\t\t{x2,7:0.0000}\t\t{f1,13:0.0000000000}\t{f2,13:0.0000000000}\t{length,7:0.0000}");
#endif
            }
            return (leftBound + rightBound) / 2;
        }
        public (decimal leftBound, decimal rightBound) Localizate(decimal start)
        {
#if DEBUG
            Console.WriteLine("+-----------------------+");
            Console.WriteLine("|      Метод Свена      |");
            Console.WriteLine("+-----------------------+");
            Console.WriteLine("Iтерацаiя\th\t\tx0\t\tx1\t\tx2\t\tf0\t\tf1\t\tf2");
#endif
            decimal x0 = start;
            decimal h = StatrtStep;
            decimal x1 = x0 - h;
            decimal x2 = x0 + h;
            decimal f0 = FucntionCalc(x0);
            decimal f1 = FucntionCalc(x1);
            decimal f2 = FucntionCalc(x2);
#if DEBUG
            Console.WriteLine($"0\t\t{h,7:0.0000}\t\t{x0,7:0.0000}\t\t{x1,7:0.0000}\t\t{x2,7:0.0000}\t\t{f0,7:0.0000000000}\t{f1,7:0.0000000000}\t{f2,13:0.0000000000}");
#endif
            if (f1 > f0 && f2 > f0)
            {
                return (x1, x2);
            }
            else if (f1 > f0 && f2 > f0)
            {
                throw new ArgumentException("Возле начальной точки находится максимум");
            }

            if (f1 <= f2)
            {
                h = -h;
            }
            else
            {
                x1 = x2;
                f1 = f2;
            }
#if DEBUG
            int i = 1;
#endif
            while ((new decimal[] { x0, x2 }).Select(x => Math.Abs(x - start)).Max() < RadiusSearch)
            {
#if DEBUG
                Console.WriteLine($"{i++}\t\t{h,7:0.0000}\t\t{x0,7:0.0000}\t\t{x1,7:0.0000}\t\t{x2,7:0.0000}\t\t{f0,7:0.0000000000}\t{f1,7:0.0000000000}\t{f2,13:0.0000000000}");
#endif
                h = 2 * h;
                x2 = x1 + h;

                f2 = FucntionCalc(x2);
                if (f2 <= f1)
                {
                    x0 = x1;
#if DEBUG
                    f0 = f1;
#endif
                    x1 = x2;
                    f1 = f2;
                }
                else
                {
                    decimal x3 = x2 - h / 2;
                    decimal f3 = FucntionCalc(x3);
#if DEBUG
                    Console.WriteLine($"{i++}\t\t{h,7:0.0000}\t\t{x0,7:0.0000}\t\t{x1,7:0.0000}\t\t{x2,7:0.0000}\t\t{f0,7:0.0000000000}\t{f1,7:0.0000000000}\t{f2,13:0.0000000000}");
#endif
                    if (f1 > f3)
                    {
                        return x1 < x2 ? (x1, x2) : (x2, x1);
                    }
                    else
                    {
                        return x0 < x3 ? (x0, x3) : (x3, x0);
                    }
                }
            }

            throw new ArgumentException("Начальная точка слишком далеко от минимума");
        }
        public decimal SearchMinimumNearPoin(decimal start)
        {
            var (l, r) = Localizate(start);
            return SearchMinimum(l, r);
        }
    }
}
