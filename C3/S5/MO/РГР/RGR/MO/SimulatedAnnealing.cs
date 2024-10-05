using System;
using System.Collections.Generic;
using System.Text;

namespace MO
{
    public class SimulatedAnnealing <T>
    {
        public Func<T, double> Energy { get; }
        public Func<int, double> Temperature { get; } = (k => 1.0 / k);
        public Func<T , double , T> NewState { get; }
        private readonly Random random;
        private SimulatedAnnealing()
        {
            random = new Random((int)DateTime.Now.ToBinary());
        }
        public SimulatedAnnealing(Func<T, double> energy, Func<T, double, T> newState) : this()
        {
            Energy = energy ?? throw new ArgumentNullException("energy");
            NewState = newState ?? throw new ArgumentNullException("newState");
        }
        public SimulatedAnnealing(Func<T, double> energy, Func<T, double, T> newState, Func<int, double> temperature) : this(energy, newState)
        {
            Temperature = temperature ?? throw new ArgumentNullException("temperature");
        }

        public T FindMinimum(T startPoint, int amountOfIterations = 100000)
        {
            double tempetature, deltaEnergy, globalMinimumEnergy, curEnergy, nextEnergy;
            T curState, nextState, globalMinimumPoint;

            curState = globalMinimumPoint = startPoint;
            curEnergy = globalMinimumEnergy = Energy(startPoint);

            for (int i = 1; i <= amountOfIterations; i++)
            {
                tempetature = Temperature(i);
                nextState = NewState(curState, tempetature);
                nextEnergy = Energy(nextState);
                deltaEnergy = nextEnergy - curEnergy;
                if (deltaEnergy < 0 || random.NextDouble() < Math.Exp(-deltaEnergy / tempetature))
                {
                    curState = nextState;
                    curEnergy = nextEnergy;
                    if (nextEnergy < globalMinimumEnergy)
                    {
                        globalMinimumEnergy = nextEnergy;
                        globalMinimumPoint = nextState;
                    }
                }

            }
            return globalMinimumPoint;
        }
    }
}
