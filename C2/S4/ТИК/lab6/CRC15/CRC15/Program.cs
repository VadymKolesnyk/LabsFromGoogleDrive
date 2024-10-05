using System;

namespace CRC15
{
    class Program
    {
        static ushort[] GetCRC16Table()
        {
            ushort[] table = new ushort[256];

            for (int i = 0; i < 256; i++)
            {
                ushort temp = (ushort)i;
                temp <<= 7;
                for (int j = 0; j < 8; j++)
                {
                    temp = (ushort)(((temp & 0x4000) == 0x4000) ? ((temp << 1) ^ 0x4599) : (temp << 1));
                }
                table[i] = (ushort)(temp & 0x7FFF);
            }   
            return table;
        }
        private static ushort CRC(ushort[] table, string data)
        {
            ushort crc = 0x7FFF;
            foreach (char ch in data)
            {
                crc = (ushort)((crc << 8) ^ table[((crc >> 7) & 0xFF) ^ ch]);
            }
            crc ^= 0x7FFF;
            crc &= 0x7FFF;
            return crc;
        }
        static void Main(string[] args)
        {
            ushort[] table = GetCRC16Table();
            for (int i = 0; i < 32; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Console.Write(Convert.ToString((table[8 * i + j]) + ushort.MaxValue + 1, 16)[1..] + '\t');
                }
                Console.WriteLine();
            }
            Console.WriteLine("\n\n");
            string data = "123456789";
            Console.WriteLine("Input:\t" + data);
            Console.WriteLine("Result:\t" + Convert.ToString(CRC(table, data) + ushort.MaxValue + 1, 16)[1..] + "\n");
            data = "123466789";
            Console.WriteLine("Input:\t" + data);
            Console.WriteLine("Result:\t" + Convert.ToString(CRC(table, data) + ushort.MaxValue + 1, 16)[1..] + "\n");
            data = "111111111";
            Console.WriteLine("Input:\t" + data);
            Console.WriteLine("Result:\t" + Convert.ToString(CRC(table, data) + ushort.MaxValue + 1, 16)[1..] + "\n");
        }
    }
}
