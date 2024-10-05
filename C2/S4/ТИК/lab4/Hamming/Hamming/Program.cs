using System;
using System.IO;

namespace Hamming
{
    class Program
    {
        static string GetStringArray(byte[] bytes)
        {
            string print = "";
            foreach (byte b in bytes)
            {
                print += Convert.ToString(b + 256, 2).Remove(0, 1) + "|";
                // print += (char)b + "|";
            }
            return print;
        }
        static string GetBinaryString(byte[] bytes)
        {
            string str = "";
            foreach (byte b in bytes)
            {
                str += Convert.ToString(b + 256, 2).Remove(0, 1);
            }
            return str;
        }
        static byte[] AddHammingBits(byte[] bytes)
        {
            if (bytes.Length != 8) throw new Exception("Length != 8");
            string binaryString = GetBinaryString(bytes);
            binaryString = binaryString.Insert(0, "0");
            binaryString = binaryString.Insert(1, "0");
            binaryString = binaryString.Insert(3, "0");
            binaryString = binaryString.Insert(7, "0");
            binaryString = binaryString.Insert(15, "0");
            binaryString = binaryString.Insert(31, "0");
            binaryString = binaryString.Insert(63, "0");
            char[] s = { '0', '0', '0', '0', '0', '0', '0', '0' };
            for (int i = 0; i < binaryString.Length; i++)
            {
                if (i % 2 == 0 && binaryString[i] == '1')
                    s[0] = (s[0] == '0') ? '1' : '0';
                if (((i + 1) / 2) % 2 == 1 && binaryString[i] == '1')
                    s[1] = (s[1] == '0') ? '1' : '0';
                if (((i + 1) / 4) % 2 == 1 && binaryString[i] == '1')
                    s[2] = (s[2] == '0') ? '1' : '0';
                if (((i + 1) / 8) % 2 == 1 && binaryString[i] == '1')
                    s[3] = (s[3] == '0') ? '1' : '0';
                if (((i + 1) / 16) % 2 == 1 && binaryString[i] == '1')
                    s[4] = (s[4] == '0') ? '1' : '0';
                if (((i + 1) / 32) % 2 == 1 && binaryString[i] == '1')
                    s[5] = (s[5] == '0') ? '1' : '0';
                if (((i + 1) / 64) % 2 == 1 && binaryString[i] == '1')
                    s[6] = (s[6] == '0') ? '1' : '0';
                if (binaryString[i] == '1')
                    s[7] = (s[7] == '0') ? '1' : '0';
            }
            for (int i = 0; i < 7; i++)
            {
                if (s[i] == '1')
                    s[7] = (s[7] == '0') ? '1' : '0';
            }
            char[] chars = binaryString.ToCharArray();
            chars[0] = s[0];
            chars[1] = s[1];
            chars[3] = s[2];
            chars[7] = s[3];
            chars[15] = s[4];
            chars[31] = s[5];
            chars[63] = s[6];
            binaryString = new string(chars);
            binaryString += s[7];
            bytes = new byte[9];
            for (int i = 0; i < 9; i++)
            {
                bytes[i] = Convert.ToByte(binaryString[(8 * i)..(8 * (i + 1))], 2);
            }
            return bytes;
        }

        static bool Correct(ref byte[] bytes, int mode = 1)
        {
            if (bytes.Length != 9) throw new Exception("Length != 9");
            string binaryString = GetBinaryString(bytes);
            char[] read = { binaryString[0], binaryString[1], binaryString[3], binaryString[7], binaryString[15], binaryString[31], binaryString[63], binaryString[71] };
            char[] calculated = { '0', '0', '0', '0', '0', '0', '0' };
            char s8 = '0';
            for (int i = 0; i < binaryString.Length - 1; i++)
            {
                if (binaryString[i] == '1')
                    s8 = (s8 == '0') ? '1' : '0';
            }
            char[] chars = binaryString[..^1].ToCharArray();
            chars[0] = chars[1] = chars[3] = chars[7] = chars[15] = chars[31] = chars[63] = '0';
            binaryString = new string(chars);
            for (int i = 0; i < binaryString.Length; i++)
            {
                if (i % 2 == 0 && binaryString[i] == '1')
                    calculated[0] = (calculated[0] == '0') ? '1' : '0';
                if (((i + 1) / 2) % 2 == 1 && binaryString[i] == '1')
                    calculated[1] = (calculated[1] == '0') ? '1' : '0';
                if (((i + 1) / 4) % 2 == 1 && binaryString[i] == '1')
                    calculated[2] = (calculated[2] == '0') ? '1' : '0';
                if (((i + 1) / 8) % 2 == 1 && binaryString[i] == '1')
                    calculated[3] = (calculated[3] == '0') ? '1' : '0';
                if (((i + 1) / 16) % 2 == 1 && binaryString[i] == '1')
                    calculated[4] = (calculated[4] == '0') ? '1' : '0';
                if (((i + 1) / 32) % 2 == 1 && binaryString[i] == '1')
                    calculated[5] = (calculated[5] == '0') ? '1' : '0';
                if (((i + 1) / 64) % 2 == 1 && binaryString[i] == '1')
                    calculated[6] = (calculated[6] == '0') ? '1' : '0';
            }
            for (int i = 0; i < 7; i++)
            {
                calculated[i] = (calculated[i] == read[i]) ? '0' : '1';
            }
            for (int i = 0; i < 4; i++)
            {
                char temp = calculated[i];
                calculated[i] = calculated[6 - i];
                calculated[6 - i] = temp;
            }
            chars = binaryString.ToCharArray();
            if (mode == 1)
            {
                binaryString = new string(chars);
                binaryString = binaryString.Remove(63, 1);
                binaryString = binaryString.Remove(31, 1);
                binaryString = binaryString.Remove(15, 1);
                binaryString = binaryString.Remove(7, 1);
                binaryString = binaryString.Remove(3, 1);
                binaryString = binaryString.Remove(1, 1);
                binaryString = binaryString.Remove(0, 1);
                bytes = new byte[8];
                for (int i = 0; i < 8; i++)
                {
                    bytes[i] = Convert.ToByte(binaryString[(8 * i)..(8 * (i + 1))], 2);
                }
                if (s8 != read[7] || Convert.ToInt32(new string(calculated), 2) != 0)
                    return true;
                else
                    return false;
            }
            int index = Convert.ToInt32(new string(calculated), 2) - 1;
            if (s8 != read[7] && index > 0 && index < binaryString.Length)
            {
                chars[index] = (binaryString[index] == '0') ? '1' : '0';
            }
            binaryString = new string(chars);
            binaryString = binaryString.Remove(63, 1);
            binaryString = binaryString.Remove(31, 1);
            binaryString = binaryString.Remove(15, 1);
            binaryString = binaryString.Remove(7, 1);
            binaryString = binaryString.Remove(3, 1);
            binaryString = binaryString.Remove(1, 1);
            binaryString = binaryString.Remove(0, 1);
            bytes = new byte[8];
            for (int i = 0; i < 8; i++)
            {
                bytes[i] = Convert.ToByte(binaryString[(8 * i)..(8 * (i + 1))], 2);
            }
            if (s8 == read[7] && Convert.ToInt32(new string(calculated), 2) != 0)
                return true;
            else
                return false;
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
            // Console.WriteLine("Введите имя файла: ");
            // string file = Console.ReadLine();
            string file = "input.txt";
            using BinaryReader reader = new BinaryReader(File.Open(file, FileMode.Open));
            using BinaryWriter writer = new BinaryWriter(File.Open("output.txt", FileMode.Create));
            Console.WriteLine("Выберите режим: \n1 - обраружение ошибок (одно- , двух- или трехбитвые ошибки)\n2 - исправление однобитовых ошибок, обнаружение двухбитовых (при наличии трехбитовых некоректная работа)");
            string choise = Console.ReadLine();
            if (choise != "1" && choise != "2")
            {
                throw new Exception("choise != 1 or 2");
            }
            Console.WriteLine("Введите максимальное количество ошибок, которое может быть в 8 байтах исходного файла:");
            int maxMistakes = Convert.ToInt32(Console.ReadLine());
            maxMistakes++;
            Random random = new Random((int)DateTime.Now.Ticks);
            byte[] bytes;
            bool mistake;
            while (reader.BaseStream.Length - reader.BaseStream.Position > 8)
            {
                bytes = reader.ReadBytes(8);
                Console.WriteLine(GetStringArray(bytes));
                bytes = AddHammingBits(bytes);
                bytes = Transfer(bytes, random.Next(maxMistakes));
                mistake = Correct(ref bytes, Convert.ToInt32(choise));
                Console.WriteLine(GetStringArray(bytes));
                Console.WriteLine((mistake) ? "В выходном файле ошибка может присутствовать" : "В выходном файле ошибки нет");
                writer.Write(bytes);
            }
            int lastBytes = (int)(reader.BaseStream.Length - reader.BaseStream.Position);
            bytes = reader.ReadBytes((int)(reader.BaseStream.Length - reader.BaseStream.Position));
            Console.WriteLine(GetStringArray(bytes));
            Array.Resize(ref bytes, 8);
            bytes = AddHammingBits(bytes);
            bytes = Transfer(bytes, random.Next(maxMistakes));
            mistake = Correct(ref bytes, Convert.ToInt32(choise));
            Array.Resize(ref bytes, lastBytes);
            Console.WriteLine(GetStringArray(bytes));
            Console.WriteLine((mistake) ? "В выходном файле ошибка может присутствовать" : "В выходном файле ошибки нет");
            writer.Write(bytes);

            reader.Close();
        }
    }
}

