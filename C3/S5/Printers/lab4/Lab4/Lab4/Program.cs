using System;
using System.Drawing;
using System.IO;
using System.Linq;

namespace Lab4
{
    public static class BitmapExtensions
    {
        public static Color GetBWPixel(this Bitmap image, int x, int y)
        {
            Color color = image.GetPixel(x, y);
            if ((color.R * 0.3) + (color.G * 0.59) + (color.B * 0.11) > 127)
                return Color.White;
            else
                return Color.Black;
        }
    }
    class Program
    {
        static string pattern = "";
        static int DecodeNumeral(byte[] code)
        {
            if (code.Length != 7)
            {
                throw new ArgumentException("code.Length may be 7");
            }

            int codeNum = Convert.ToInt32(new(code.Select(b => Convert.ToChar(b + '0')).ToArray()), 2);
            (int num, char col) = codeNum switch
            {
                0b0001101 => (0, 'A'),
                0b0011001 => (1, 'A'),
                0b0010011 => (2, 'A'),
                0b0111101 => (3, 'A'),
                0b0100011 => (4, 'A'),
                0b0110001 => (5, 'A'),
                0b0101111 => (6, 'A'),
                0b0111011 => (7, 'A'),
                0b0110111 => (8, 'A'),
                0b0001011 => (9, 'A'),
                
                0b0100111 => (0, 'B'),
                0b0110011 => (1, 'B'),
                0b0011011 => (2, 'B'),
                0b0100001 => (3, 'B'),
                0b0011101 => (4, 'B'),
                0b0111001 => (5, 'B'),
                0b0000101 => (6, 'B'),
                0b0010001 => (7, 'B'),
                0b0001001 => (8, 'B'),
                0b0010111 => (9, 'B'),

                0b1110010 => (0, 'C'),
                0b1100110 => (1, 'C'),
                0b1101100 => (2, 'C'),
                0b1000010 => (3, 'C'),
                0b1011100 => (4, 'C'),
                0b1001110 => (5, 'C'),
                0b1010000 => (6, 'C'),
                0b1000100 => (7, 'C'),
                0b1001000 => (8, 'C'),
                0b1110100 => (9, 'C'),
                _ => throw new ArgumentException("Invalid code"),
            };
            pattern += col;
            return num;
        }
        static bool CheckCode(byte[] code)
        {
            return !(code.Length != 95 ||
                !code[0..3].SequenceEqual(new byte[] { 1, 0, 1 }) ||
                !code[45..50].SequenceEqual(new byte[] { 0, 1, 0, 1, 0 }) ||
                !code[^3..].SequenceEqual(new byte[] { 1, 0, 1 }));
        }
        static void Main(string[] args)
        {
            Bitmap image = new Bitmap("img/barcode.jpg");
            Color color = Color.White;
            int start = -1;
            int end = image.Width;
            while (image.GetBWPixel(++start, image.Height / 2) != Color.Black);
            while (image.GetBWPixel(--end, image.Height / 2) != Color.Black);
            const int length = 95;
            double h = (double)(end - start + 1) / length;
            Console.WriteLine(h);
            byte[] code = new byte[length];
            for (int i = 0; i < length; i++)
            {
                double sum = 0;
                int count = 0; 
                for (int j = start + (int)(i * h) ; j < start + (int)((i + 1) * h); j++)
                {
                    if (image.GetBWPixel(j, image.Height / 2) == Color.Black)
                    {
                        sum++;
                    }
                    count++;
                }
                if (sum / count < 0.5)
                {
                    code[i] = 0;
                }
                else
                {
                    code[i] = 1;
                }
            }
            for (int i = 0; i < length; i++)
            {
                Console.Write(code[i]);
            }
            Console.WriteLine();
            if (CheckCode(code))
            {
                int[] result = new int[13];
                int index = 1;
                for (int i = 0; i < 6; i++)
                {
                    result[index++] = DecodeNumeral(code[(3 + 7 * i)..(3 + 7 * (i + 1))]);
                }
                for (int i = 0; i < 6; i++)
                {
                    result[index++] = DecodeNumeral(code[(50 + 7 * i)..(50 + 7 * (i + 1))]);
                }
                Console.WriteLine(pattern);
                result[0] = pattern switch
                {
                    "AAAAAACCCCCC" => 0,
                    "AABABBCCCCCC" => 1,
                    "AABBABCCCCCC" => 2,
                    "AABBBACCCCCC" => 3,
                    "ABAABBCCCCCC" => 4,
                    "ABBAABCCCCCC" => 5,
                    "ABBBAACCCCCC" => 6,
                    "ABABABCCCCCC" => 7,
                    "ABABBACCCCCC" => 8,
                    "ABBABACCCCCC" => 9,
                    _ => throw new Exception("Invalid code"),
                };
                Console.WriteLine(new string(result.Select(n => Convert.ToChar(n + '0')).ToArray()));
                int control = 0;
                for (int i = 0; i < 6; i++)
                {
                    control += result[2 * i] + 3 * result[2 * i + 1];
                }
                control %= 10;
                control = 10 - control;
                if (control == result[12])
                {
                    Console.WriteLine("Контрольная сумма совпала");
                }
                else
                {
                    Console.WriteLine("Контрольная не сумма совпала");
                }
            }
            else
            {
                Console.WriteLine("Invalid code");
            }
        }
    }
}
