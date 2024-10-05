using System;


namespace Cyclic_codes
{
    class Program
    {
        static int[] BuildMatrix(byte mod)
        {
            mod %= 0b100000;
            int[] table = new int[32];
            byte x = 1;
            table[0] = -1;
            table[1] = 0;
            for (int i = 1; i < 31; i++)
            {
                if ((x & 0b10000) == 0b10000)
                {
                    x <<= 1;
                    x ^= mod;
                    x %= 0b100000;
                }
                else
                {
                    x <<= 1;
                }
                table[x] = (byte)i;
            }
            return table;
        }

        static byte[] Code(byte[] data, byte mod)
        {
            string s = "";
            foreach (byte b in data)
            {
                s += Convert.ToString(b + 256, 2).Remove(0, 1);  
            }
            s = s[0..26];
            Console.WriteLine(s);
            byte controlBits = Div(s + "00000", mod);
            data[3] = (byte)((data[3] & 0b11000000) | (controlBits << 1));
            s = "";
            foreach (byte b in data)
            {
                s += Convert.ToString(b + 256, 2).Remove(0, 1);
            }
            s = s[0..31];
            Console.WriteLine(s);
            return data;
        }

        static byte Uncode(byte[] data, byte mod)
        {
            string s = "";
            foreach (byte b in data)
            {
                s += Convert.ToString(b + 256, 2).Remove(0, 1);
            }
            s = s[0..31];
            Console.WriteLine(s);
            byte controlBits = Div(s, mod);
            return controlBits;
        }

        private static byte Div(string s, byte mod)
        {
            bool[] index = {    (mod & 0b100000) == 0b100000, (mod & 0b10000) == 0b10000,
                                (mod & 0b1000) == 0b1000, (mod & 0b100) == 0b100, (mod & 0b10) == 0b10, (mod & 0b1) == 0b1 };
            char[] str = s.ToCharArray();
            for (int i = 0; i < str.Length - 5; i++)
            {
                if (str[i] == '1')
                {
                    for (int j = 0; j < 6; j++)
                    {
                        if (index[j])
                        {
                            str[i + j] = (str[i + j] == '1') ? '0' : '1';
                        }
                    }
                }
            }
            Console.WriteLine(new string(str[^5..]));
            return Convert.ToByte(new string(str[^5..]), 2);
        }

        static byte[] Transfer(byte[] bytes, int mistakes)
        {
            Random random = new Random((int)DateTime.Now.Ticks);
            for (int i = 0; i < mistakes; i++)
            {
                int b = random.Next(bytes.Length);
                int index = random.Next(8);
                bytes[b] = (byte)(bytes[b] ^ (1 << index));
            }
            return bytes;
        }
        static void Main(string[] args)
        {


            byte mod = 0b101001;
            int[] table = BuildMatrix(mod);
            for (int i = 1; i < 32; i++)
            {
                Console.WriteLine(Convert.ToString(32 + i, 2)[1..] + "\t" + table[i]);
            }
            byte[] data = { 0b01010101, 0b11111111, 0b00000010, 0b10 << 6 };
            data = Code(data, mod);
            data = Transfer(data, 1);
            Console.WriteLine(30 - table[Uncode(data, mod)]);
        }
    }
}
