using System;
using System.IO;

namespace lab1_files
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Выберите файл: \n1 - data.txt\n2 - data.png\n3 - data.exe");
            int a = Convert.ToInt32(Console.ReadLine());
            string file;
            string result;
            if (a == 1)
            {
                file = "data.txt";
                result = "resulttxt.csv";
            }
            else if (a == 2)
            {
                file = "data.png";
                result = "resultpng.csv";
            }
            else if (a == 3)
            {
                file = "data.exe";
                result = "resultexe.csv";
            }
            else
            {
                Console.WriteLine("Не правильный ввод");
                return;
            }

            using BinaryReader reader = new BinaryReader(File.Open(file, FileMode.Open));
            byte[] temp = new byte[100];
            long length = reader.BaseStream.Length;
            ulong[] characters = new ulong[256];
            double[] probability = new double[256];
            double H = 0;
            double I = 0;

            while (length - reader.BaseStream.Position > 100)
            {
                temp = reader.ReadBytes(100);
                for (int i = 0; i < 100; i++)
                {
                    characters[temp[i]]++;
                }
            }
            int last = (int)(length - reader.BaseStream.Position);
            temp = reader.ReadBytes(last);
            reader.Close();
            for (int i = 0; i < last; i++)
            {
                characters[temp[i]]++;
            }
            for (int i = 0; i < 256; i++)
            {
                probability[i] = ((double)characters[i] / length);
                if (probability[i] != 0)
                    H += probability[i] * Math.Log2(1 / probability[i]);
            }
            I = H * length;
            using StreamWriter writer = new StreamWriter(File.Open(result, FileMode.OpenOrCreate));
            writer.WriteLine("H;" + $";{H:f10}");
            writer.WriteLine("I0;" + $";{I:f3}");
            Console.WriteLine("H\t  :  " + $"{H:f10}");
            Console.WriteLine("I0\t  :  " + $"{I:f3}");
            for (int i = 0; i < 256; i++)
            {
                writer.WriteLine("<" + Convert.ToString(i + 256, 2).Remove(0, 1) + ">;" + characters[i] + $";{probability[i]:f10}");
                Console.WriteLine(Convert.ToString(i+256,2).Remove(0, 1) + "  :  " + characters[i] + $"\t:   {probability[i]:f10}");
            }
            writer.Close();
        }
    }
}
