using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Program
    {
        static double p = 1;
        static double q = 4;
        [STAThread]
        static void Main(string[] args)
        {
            var x = 10;
            var levels = new Dictionary<double, Color>
            {
                { x + 0, Color.Blue },
                { x + 2, Color.Green },
                { x + 4, Color. Yellow},
                { x + 6, Color.Orange},
                { x + 8, Color.Red }
            };

            var w = F(1, 1);
            Console.WriteLine(w);
            ImageGenerator.Generate(F,levels);
        }
        static double F(double x1, double x2) => (x1 - p) * (x1 - p) + (x2 - q) * (x2 - q) - 2 * x1 * x2 / (p + q);
    }
}
