using System;
using System.Collections.Generic;
using System.IO;


namespace Archiver
{
    class Tree // Класс дерево 
    {

        private Node Root { get; set; } // Корень дерева
        private int Size { get; set; } // Количество листьев в девере
        public Tree(Node root, int size)
        {
            Root = root;
            Size = size;
        }
        public static Tree BildTree(int size, byte[] treeArray, int posOfZero) // постройка дерева из масива байтов, который считывается из файла
        {
            int current = -1;
            Node root = CreateNode(treeArray, ref current, posOfZero);
            return new Tree(root, (size + 2) / 3);
        }
        private static Node CreateNode(byte[] treeArray, ref int current, int posOfZero) // создание узла дерева
        {
            current++;
            if (current == posOfZero)
            {
                return new Leaf(0, 0);
            }
            else if (treeArray[current] == 0)
            {
                return new NodeMid(CreateNode(treeArray, ref current, posOfZero), CreateNode(treeArray, ref current, posOfZero));
            }
            else
            {
                return new Leaf(treeArray[current], 0);
            }
        }
        public void Uncode(BinaryReader reader, BinaryWriter writer, byte lastByteEmpty, int buf) // расшифровка кода Хаффмана
        {
            byte[] codeBuf = new byte[buf];
            long length = reader.BaseStream.Length;
            int sizeCodeBuf = 0;
            Node current = Root;
            byte[] temp;
            while (length - reader.BaseStream.Position > buf)
            {
                temp = reader.ReadBytes(buf);
                for (int i = 0; i < buf; i++)
                {
                    for (int j = 0; j < 8; j++) // обрабатываем код побитово
                    {
                        Treatment(((byte)(temp[i] << j)) / 128, codeBuf, ref sizeCodeBuf, ref current, writer); // обработка бита
                    }
                }
            }
            int last = (int)(length - reader.BaseStream.Position);
            temp = reader.ReadBytes(last);
            for (int i = 0; i < last - 1; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    Treatment(((byte)(temp[i] << j)) / 128, codeBuf, ref sizeCodeBuf, ref current, writer);
                }
            }
            for (int j = 0; j < (8 - lastByteEmpty); j++)
            {
                Treatment(((byte)(temp[last - 1] << j)) / 128, codeBuf, ref sizeCodeBuf, ref current, writer);
            }
            AddByte(codeBuf, ((Leaf)current).Key, ref sizeCodeBuf, writer);
            writer.Write(codeBuf, 0, sizeCodeBuf);

        }
        private void Treatment(int curBit, byte[] codeBuf, ref int sizeCodeBuf, ref Node current, BinaryWriter writer)// обработка бита
        { // проход по дереву пока не будет встречен лист дерева
            if (current.GetType() == new Leaf(0, 0).GetType()) 
            {
                AddByte(codeBuf, ((Leaf)current).Key, ref sizeCodeBuf, writer);
                current = Root;
            }
            if (curBit == 0)
            {
                current = ((NodeMid)current).Zero;
            }
            else if (curBit == 1)
            {
                current = ((NodeMid)current).One;
            }
        }
        private void AddByte(byte[] codeBuf, byte curByte, ref int size, BinaryWriter writer) // функция записи байта в файл через буфер
        {
            if (size == codeBuf.Length) // если буфер полный записываем его в файл в обнуляем буфер
            {
                writer.Write(codeBuf);
                size = 0;
            }
            codeBuf[size] = curByte; // запись байта в буфер
            size++;
        }
        public string[] GetCodes() // Получение кодов символов в масив строк
        {
            string[] codes = new string[256];
            Array.Fill(codes, ""); // обнуляем строки
            InorderCode(Root, codes, ""); // обход дерева
            return codes;
        }
        private void InorderCode(Node node, string[] codes, string code) // обход дерева
        {
            if (node.GetType() == new Leaf(0, 0).GetType()) // когда доходим до листка, то записываем его путь
            {
                codes[((Leaf)node).Key] = code;
            }
            else
            {
                InorderCode(((NodeMid)node).Zero, codes, code + "0");
                InorderCode(((NodeMid)node).One, codes, code + "1");
            }
        }

        private void InorderWrite(Node node, byte[] tree, ref int current, ref int posOfZero)
        {
            if (node.GetType() == new Leaf(0, 0).GetType()) // если дошли до листка, то запись его кода
            {
                if (((Leaf)node).Key == 0)
                {
                    posOfZero = current;
                }
                tree[current++] = ((Leaf)node).Key;
            }
            else
            {
                tree[current++] = 0;
                InorderWrite(((NodeMid)node).Zero, tree, ref current, ref posOfZero);
                InorderWrite(((NodeMid)node).One, tree, ref current, ref posOfZero);
            }
        }
        public void WriteToFile(BinaryWriter writer) //запись девера в файл
        {
            int posOfZero = -1;
            writer.Write(Size + (Size - 1)); // определение размера масива
            byte[] tree = new byte[Size + (Size - 1)];
            int current = 0;
            InorderWrite(Root, tree, ref current, ref posOfZero); // обход дерева
            writer.Write(posOfZero);
            writer.Write(tree);
        }
        public string GiveInfo()
        {
            return Root.GiveInfo();
        }
    }
    abstract class Node : IComparable<Node> // класс узла дерева
    {
        public ulong Value { get; protected set; }

        public int CompareTo(Node n)
        {
            return Value.CompareTo(n.Value);
        }
        abstract public string GiveInfo();
        abstract public string GiveInfo(string str);

    }
    class NodeMid : Node // узел дерева - не лист
    {
        public Node Zero { get; private set; }
        public Node One { get; private set; }

        public NodeMid(Node zero, Node one)
        {
            this.Zero = zero;
            this.One = one;
            this.Value = zero.Value + one.Value;
        }

        public override string GiveInfo()
        {
            return "Value:\t" + Value + "\n\t\t0)  " + Zero.GiveInfo("\t\t") + "\n\t\t1)  " + One.GiveInfo("\t\t");

        }

        public override string GiveInfo(string str)
        {
            return "Value:\t" + Value + "\n\t\t" + str + "0)  " + Zero.GiveInfo(str + "\t\t") + "\n\t\t" + str + "1)  " + One.GiveInfo(str + "\t\t");
        }
    }
    class Leaf : Node // лист
    {
        public byte Key { get; private set; }

        public Leaf(byte key, ulong value)
        {
            this.Key = key;
            this.Value = value;
        }

        public override string GiveInfo()
        {
            return "Byte:\t<" + Convert.ToString(this.Key + 256, 16).Remove(0, 1) + ">\tValue:\t" + this.Value;
        }

        public override string GiveInfo(string str)
        {
            return "Byte:\t<" + Convert.ToString(this.Key + 256, 16).Remove(0, 1) + ">\tValue:\t" + this.Value;
        }
    }

    class CompInv<T> : IComparer<T>
        where T : Node
    {
        public int Compare(T x, T y)
        {
            return y.CompareTo(x);
        }
    }
}
