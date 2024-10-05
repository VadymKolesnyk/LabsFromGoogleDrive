using System;
using System.IO;
using System.Diagnostics;

namespace Archiver
{
    class Arcive
    {
        public static void Do(int buf)
        {
            Console.WriteLine("Выберите файл для архивации: \n1 - data.txt\n2 - data.png\n3 - data.exe\n4 - test.txt");
            int a = Convert.ToInt32(Console.ReadLine());
            string file;
            string result;
            switch (a)
            {
                case 1:
                    file = @"data\data.txt";
                    break;
                case 2:
                    file = @"data\data.png";
                    break;
                case 3:
                    file = @"data\data.exe";
                    break;
                case 4:
                    file = @"data\test.txt";
                    break;
                case 5:
                    file = @"data\da81_kolesnyk_vd_lab2_v15.docx";
                    break;
                case 6:
                    file = @"data\SchoolVideo.mp4";
                    break;
                default:
                    Console.WriteLine("Не правильный ввод");
                    return;
            }
            result = @"archived\" + file[5..] + ".arhiv";
            Stopwatch sw = new Stopwatch();
            sw.Start();
            using BinaryReader reader = new BinaryReader(File.Open(file, FileMode.Open));
            byte[] temp = new byte[buf];
            long length = reader.BaseStream.Length;
            ulong[] states = new ulong[256];
            int amount = 0;
            while (length - reader.BaseStream.Position > buf) //читаем входной файл и счичает количество встречаний каждого символа
            {
                temp = reader.ReadBytes(buf);
                for (int i = 0; i < buf; i++)
                {
                    if (states[temp[i]] == 0)
                        amount++;
                    states[temp[i]]++;
                }
            }
            int last = (int)(length - reader.BaseStream.Position); // досчитываем конец файла
            temp = reader.ReadBytes(last);
            for (int i = 0; i < last; i++)
            {
                if (states[temp[i]] == 0)
                    amount++;
                states[temp[i]]++;
            }
            Node[] nodes = new Node[256]; // создаем массив, который будем потом сортировать и объединять последнии символы
            for (int i = 0; i < 256; i++)
            {
                nodes[i] = new Leaf((byte)i, states[i]);
            }
            CompInv<Node> rev = new CompInv<Node>(); // сравнитель для сортировки в обратном порядке
            Array.Sort(nodes, rev);
            int size = amount;
            while (size != 1) // Метод Хафмана - объединение наименьших элементов и сортировка на каждом шагу
            {
                nodes[size - 2] = new NodeMid(nodes[size - 2], nodes[size - 1]);
                size--;
                Array.Sort(nodes, 0, size, rev);
            }
            Tree tree = new Tree(nodes[0], amount);
            string[] codes = tree.GetCodes(); // Получение кодов символов в масив строк
            int[,] patterns = new int[2, 256]; // Массив паттернов для подальшей записи в файл
            const int mult = 0;
            const int plus = 1;
            for (int i = 0; i < 256; i++)
            {
                patterns[plus, i] = Convert.ToInt32("0" + codes[i], 2); // записываем код в числовом формате
                patterns[mult, i] = codes[i].Length; // записываем длину кода
            }
            int curMult;
            int curPlus;
            byte[] codeBuf = new byte[buf]; // буфер для записи в файл
            int bufSize = 0;
            byte curByte = 0;
            byte curByteSize = 8;
            reader.BaseStream.Position = 0; // подготавливаем файл для повторного считывания
            using BinaryWriter writer = new BinaryWriter(File.Open(result, FileMode.Create));
            writer.BaseStream.Position = 1; // пропускаем место для подальшей записи туда количества свободных бит в последнем байте
            tree.WriteToFile(writer); // записываем дерево в файл
            while (length - reader.BaseStream.Position > buf)
            {
                temp = reader.ReadBytes(buf);
                for (int i = 0; i < buf; i++) // обрадатываем следующий символ
                {
                    curMult = patterns[mult, temp[i]];
                    curPlus = patterns[plus, temp[i]];
                    while (curMult > curByteSize) // формировка байта для записи в файл
                    {
                        curByte = (byte)(curByte << curByteSize);
                        curByte += (byte)(curPlus >> (curMult - curByteSize));
                        curPlus -= (curPlus >> (curMult - curByteSize)) << (curMult - curByteSize);
                        curMult -= curByteSize;
                        curByteSize = 8;
                        AddByte(codeBuf, curByte, ref bufSize, writer); // функция записи байта в файл через буфер
                    }
                    curByte = (byte)(curByte << curMult);
                    curByte += (byte)curPlus;
                    curByteSize -= (byte)curMult;
                }
            }
            last = (int)(length - reader.BaseStream.Position);
            temp = reader.ReadBytes(last);
            for (int i = 0; i < last; i++) // доделываем обработку для последних байтах из изходного файла
            {
                curMult = patterns[mult, temp[i]];
                curPlus = patterns[plus, temp[i]];
                while (curMult > curByteSize)
                {
                    curByte = (byte)(curByte << curByteSize);
                    curByte += (byte)(curPlus >> (curMult - curByteSize));
                    curPlus -= (curPlus >> (curMult - curByteSize)) << (curMult - curByteSize);
                    curMult -= curByteSize;
                    curByteSize = 8;
                    AddByte(codeBuf, curByte, ref bufSize, writer);
                }
                curByte = (byte)(curByte << curMult);
                curByte += (byte)curPlus;
                curByteSize -= (byte)curMult;
            }
            curByte = (byte)(curByte << curByteSize); // формируем последний байт 
            AddByte(codeBuf, curByte, ref bufSize, writer); // запись буфера в файл
            Array.Resize(ref codeBuf, bufSize);
            writer.Write(codeBuf);
            writer.BaseStream.Position = 0;
            writer.Write(curByteSize);
            reader.Close();
            writer.Close();
            sw.Stop();
            Console.WriteLine(sw.ElapsedMilliseconds + " ms"); // вывод времени действия программы
        }
        static void AddByte(byte[] codeBuf, byte curByte, ref int size, BinaryWriter writer) // функция записи байта в файл через буфер
        {
            if (size == codeBuf.Length) // если буфер полный записываем его в файл в обнуляем буфер
            {
                writer.Write(codeBuf);
                size = 0;
            }
            codeBuf[size] = curByte; // запись байта в буфер
            size++;
        }
    }
}
