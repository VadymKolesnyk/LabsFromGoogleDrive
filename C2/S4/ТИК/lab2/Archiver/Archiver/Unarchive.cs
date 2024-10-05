using System;
using System.Diagnostics;
using System.IO;

namespace Archiver
{
    class Unarchive
    {
        public static void Do(int buf)
        {
            Console.WriteLine("Выберите файл для разархивации: \n1 - data.txt.arhiv\n2 - data.png.arhiv\n3 - data.exe.arhiv\n4 - test.txt.arhiv");
            int a = Convert.ToInt32(Console.ReadLine());
            string file;
            string result;
            switch (a)
            {
                case 1:
                    file = @"archived\data.txt.arhiv";
                    break;
                case 2:
                    file = @"archived\data.png.arhiv";
                    break;
                case 3:
                    file = @"archived\data.exe.arhiv";
                    break;
                case 4:
                    file = @"archived\test.txt.arhiv";
                    break;
                case 5:
                    file = @"archived\da81_kolesnyk_vd_lab2_v15.docx.arhiv";
                    break;
                case 6:
                    file = @"archived\SchoolVideo.mp4.arhiv";
                    break;
                default:
                    Console.WriteLine("Не правильный ввод");
                    return;
            }
            result = @"unarchived\" + file[9..^6];
            Stopwatch sw = new Stopwatch();
            sw.Start();
            using BinaryReader reader = new BinaryReader(File.Open(file, FileMode.Open));
            using BinaryWriter writer = new BinaryWriter(File.Open(result, FileMode.Create));

            byte lastByteEmpty = reader.ReadByte();
            int sizeTree = reader.ReadInt32();
            int posOfZero = reader.ReadInt32();
            byte[] treeArray = reader.ReadBytes(sizeTree);
            Tree tree = Tree.BildTree(sizeTree, treeArray , posOfZero); // создание дерева
            //Console.WriteLine(tree.GiveInfo());
            tree.Uncode(reader, writer, lastByteEmpty, buf);
            reader.Close();
            writer.Close();
            sw.Stop();
            Console.WriteLine(sw.ElapsedMilliseconds + " ms");
        }
    }
}
