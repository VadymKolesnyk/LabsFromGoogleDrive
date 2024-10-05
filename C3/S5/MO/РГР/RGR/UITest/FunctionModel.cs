using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MO;

namespace UITest
{
    class FunctionModel
    {
        private readonly Random random = new Random((int)DateTime.Now.ToBinary());
        public double StartPoint { get; set; } = 0;
        public double StartTemperature { get; set; } = 10;
        public int AmountOfIterations { get; set; } = 100000;
        private double AckleyFunction(double x)
        {
            return -20 * Math.Exp(-0.2 * Math.Sqrt(0.5 * x * x)) - Math.Exp(0.5 * (Math.Cos(2 * Math.PI * x))) + Math.E + 20;
        }
        public double TargetFunction(double x)
        {
            return AckleyFunction(x - 5) + 0.5 * AckleyFunction(x) + 0.6 * AckleyFunction(x + 5);
        }
        public double Start()
        {
            var s = new SimulatedAnnealing<double>
            (
                energy: TargetFunction,
                newState: (x, t) =>
                {
                    var res = x + t * Math.Tan(Math.PI * random.NextDouble() - (Math.PI / 2));
                    return res > 10 ? 10 : res < -10 ? -10 : res;
                },
                temperature: k => StartTemperature / k
            );
            return s.FindMinimum(StartPoint, AmountOfIterations);
        }
    }
}
