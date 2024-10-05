using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.ComTypes;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using MO;

namespace UITest
{
    class GameModel
    {
        private readonly Random random = new Random((int)DateTime.Now.ToBinary());
        public List<Player> Players { get; } = new List<Player>();
        public double StartTemperature { get; set; } = 5000;
        public int AmountOfIterations { get; set; } = 100000;
        public double EnergyFunction(Game comands)
        {
            double energy = 0;

            long speedComand1 = comands.Comand1.Sum(player => player.Speed);
            long strengthComand1 = comands.Comand1.Sum(player => player.Strength);
            long levelComand1 = comands.Comand1.Sum(player => player.Level);
            var classesComand1 = comands.Comand1.GroupBy(player => player.Class).ToDictionary(x => x.Key, g => g.Count());

            long speedComand2 = comands.Comand2.Sum(player => player.Speed);
            long strengthComand2 = comands.Comand2.Sum(player => player.Strength);
            long levelComand2 = comands.Comand2.Sum(player => player.Level);
            var classesComand2 = comands.Comand2.GroupBy(player => player.Class).ToDictionary(x => x.Key, g => g.Count());

            energy += 10 * (levelComand2 - levelComand1);
            energy += (speedComand2 - speedComand1);
            energy += 2 * (strengthComand2 - strengthComand1);
            energy = Math.Abs(energy);
            foreach (CharacterСlass characterСlass in Enum.GetValues(typeof(CharacterСlass)))
            {
                energy += 5 * Math.Abs(classesComand2.GetValueOrDefault(characterСlass) - classesComand1.GetValueOrDefault(characterСlass));
            }
            return energy;
        }
        public Game NewStateFunction(Game game, double temp)
        {
            return new Game(game).Exchange(random.Next(game.Comand1.Length), random.Next(game.Comand2.Length));
        }
        public double TemperatureFunction(int x)
        {
            return StartTemperature / x;
        }
        public Game Start()
        {
            var s = new SimulatedAnnealing<Game>
            (
                energy: EnergyFunction,
                newState: NewStateFunction,
                temperature: TemperatureFunction
            );
            Game game = new Game(Players);
            return s.FindMinimum(game, AmountOfIterations);
            //return game;
        }
    }
}
