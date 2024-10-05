using System;
using System.Collections.Generic;
using System.Linq;
using MO;



namespace ConsoleTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Random random = new Random((int)DateTime.Now.ToBinary());
            var s = new SimulatedAnnealing<double>(
                energy: x => F(x - 5) + 0.5 * F(x) + 0.6 * F(x + 5), 
                newState: (x, t) => x + t * Math.Tan(Math.PI * random.NextDouble() - (Math.PI / 2)), 
                temperature: k => 10.0 / k
                );
            Console.WriteLine($"{s.FindMinimum(3):0.00000000000000}");
            Console.WriteLine("Hello World!");

            GameModel gameModel = new GameModel();
            var l = new List<Player>
            {
                new Player
                {
                    Level = 4,
                    Speed = 2,
                    Strength = 4,
                    Class = CharacterСlass.Cleric
                },
                new Player
                {
                    Level = 1,
                    Speed = 2,
                    Strength = 3,
                    Class = CharacterСlass.Cleric
                },
                new Player
                {
                    Level = 1,
                    Speed = 3,
                    Strength = 1,
                    Class = CharacterСlass.Fighter
                },
                new Player
                {
                    Level = 2,
                    Speed = 5,
                    Strength = 5,
                    Class = CharacterСlass.Fighter
                },
                new Player
                {
                    Level = 3,
                    Speed = 1,
                    Strength = 6,
                    Class = CharacterСlass.Magic
                },
                new Player
                {
                    Level = 3,
                    Speed = 7,
                    Strength = 1,
                    Class = CharacterСlass.Magic
                },
                new Player
                {
                    Level = 4,
                    Speed = 2,
                    Strength = 3,
                    Class = CharacterСlass.Ranger
                },
                new Player
                {
                    Level = 5,
                    Speed = 3,
                    Strength = 4,
                    Class = CharacterСlass.Rogue
                },
                new Player
                {
                    Level = 7,
                    Speed = 4,
                    Strength = 1,
                    Class = CharacterСlass.Rogue
                },
                new Player
                {
                    Level = 7,
                    Speed = 5,
                    Strength = 3,
                    Class = CharacterСlass.Rogue
                },
            };
            PrintComands(new Game(l));
            gameModel.Players.AddRange(l);
            Console.WriteLine("\n\n\n");
            PrintComands(gameModel.Start()); 




        }
        static void PrintComands(Game game)
        {
            var c1 = game.Comand1;
            var c2 = game.Comand2;
            Console.WriteLine("Comand1:");
            foreach (var item in c1.OrderBy(x => - x.Level))
            {
                Console.WriteLine("-----------------------------------");
                Console.WriteLine($"\tLevel:    {item.Level}");
                Console.WriteLine($"\tClass:    {item.Class}");
                Console.WriteLine($"\tSpeed:    {item.Speed}");
                Console.WriteLine($"\tStrength: {item.Strength}");
            }
            Console.WriteLine("Total Speed = " + c1.Sum(x=> x.Speed));
            Console.WriteLine("Total Strength = " + c1.Sum(x => x.Strength));
            Console.WriteLine("Comand2:");
            foreach (var item in c2.OrderBy(x => -x.Level))
            {
                Console.WriteLine("-----------------------------------");
                Console.WriteLine($"\tLevel:    {item.Level}");
                Console.WriteLine($"\tClass:    {item.Class}");
                Console.WriteLine($"\tSpeed:    {item.Speed}");
                Console.WriteLine($"\tStrength: {item.Strength}");
            }
            Console.WriteLine("Total Speed = " + c2.Sum(x => x.Speed));
            Console.WriteLine("Total Strength = " + c2.Sum(x => x.Strength));
        }
        static double F(double x) => -20 * Math.Exp(-0.3 * Math.Sqrt(0.5 * x * x)) - Math.Exp(0.7 * (Math.Cos(2 * Math.PI * x))) + Math.E + 20;
    }


    enum CharacterСlass
    {
        Fighter,
        Magic,
        Cleric,
        Rogue,
        Ranger
    }
    class Player
    {
        public uint Level { get; set; }
        public uint Speed { get; set; }
        public CharacterСlass Class { get; set; }
        public uint Strength { get; set; }
    }
    class Game
    {
        public Player[] Comand1 { get; }
        public Player[] Comand2 { get; }

        public Game(Game previousGame)
        {
            Comand1 = previousGame.Comand1.Clone() as Player[];
            Comand2 = previousGame.Comand2.Clone() as Player[];
        }
        public Game(List<Player> players)
        {
            int count = players.Count;
            Comand1 = new Player[count / 2];
            Comand2 = new Player[count - count / 2];
            players.CopyTo(0, Comand1, 0, count / 2);
            players.CopyTo(count / 2, Comand2, 0, count - count / 2);
        }
        public Game Exchange(int i, int j)
        {
            var temp = Comand1[i];
            Comand1[i] = Comand2[j];
            Comand2[j] = temp;
            return this;
        }

    }
    class GameModel
    {
        private readonly Random random = new Random((int)DateTime.Now.ToBinary());
        public List<Player> Players { get; } = new List<Player>();
        public double StartTemperature { get; set; } = 1000;
        public int AmountOfIterations { get; set; } = 100000;


        public double EnergyFunction(Game comands)
        {
            double energy = 0;

            uint speedComand1 = (uint)comands.Comand1.Sum(player => player.Speed);
            uint strengthComand1 = (uint)comands.Comand1.Sum(player => player.Strength);
            uint[] levelsComand1 = comands.Comand1.Select(player => player.Level).OrderBy(level => -level).ToArray();
            var classesComand1 = comands.Comand1.GroupBy(player => player.Class).ToDictionary(x => x.Key, g => g.Count());

            uint speedComand2 = (uint)comands.Comand2.Sum(player => player.Speed);
            uint strengthComand2 = (uint)comands.Comand2.Sum(player => player.Strength);
            uint[] levelsComand2 = comands.Comand2.Select(player => player.Level).OrderBy(level => -level).ToArray();
            var classesComand2 = comands.Comand1.GroupBy(player => player.Class).ToDictionary(x => x.Key, g => g.Count());

            if (levelsComand2.Length > levelsComand1.Length)
            {
                levelsComand1 = levelsComand1.Append((uint)0).ToArray(); ;
            }
            else if (levelsComand1.Length > levelsComand2.Length)
            {
                levelsComand2 = levelsComand2.Append((uint)0).ToArray(); ;
            }

            for (int i = 0; i < levelsComand1.Length; i++)
            {
                energy += 10 * Math.Abs(levelsComand1[i] - levelsComand2[i]);
            }
            energy += Math.Abs(speedComand2 - speedComand1);
            energy += 2 * Math.Abs(strengthComand2 - strengthComand1);

            foreach (CharacterСlass characterСlass in Enum.GetValues(typeof(CharacterСlass)))
            {
                energy += 5 * Math.Abs(classesComand1.GetValueOrDefault(characterСlass) - classesComand2.GetValueOrDefault(characterСlass));
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
        }

    }
}
