using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UITest
{
    enum CharacterСlass
    {
        Fighter,
        Magic,
        Cleric,
        Rogue,
        Ranger,
        Static
    }
    class Player
    {
        public string Name { get; set; }
        public uint Level { get; set; } 
        public uint Speed { get; set; }
        public CharacterСlass Class { get; set; }
        public uint Strength { get; set; }
    }
}
