using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UITest
{
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
}
