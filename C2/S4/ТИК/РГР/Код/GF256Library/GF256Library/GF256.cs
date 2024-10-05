using System;
namespace GF256Library
{
    public class GF256
    {
        //--------------Структура объекотв----------------//
        private byte value;

        //----Перегрузка базовых методов объекта---------//
        public bool Equals(GF256 obj)
        {
            return obj.value == this.value;
        }
        public override bool Equals(object obj)
        {
             return false;
        }
        public override int GetHashCode()
        {
            return this.value.GetHashCode();
        }
        public override string ToString()
        {
            return this.value.ToString();
        }

        //----Статические поля - характеристики самого поля----//
        public static byte[] PossibleMods { get; } = { 29, 43, 45, 77, 95, 99, 101, 105, 113, 135, 141, 169, 195, 207, 231, 245 };
        private static byte mod = 29;
        public static byte[] Degree { get; } = { 0, 0, 1, 25, 2, 50, 26, 198, 3, 223, 51, 238, 27, 104, 199, 75, 4, 100, 224, 14, 52, 141, 239, 129, 28, 193, 105, 248, 200, 8, 76, 113, 5, 138, 101, 47, 225, 36, 15, 33, 53, 147, 142, 218, 240, 18, 130, 69, 29, 181, 194, 125, 106, 39, 249, 185, 201, 154, 9, 120, 77, 228, 114, 166, 6, 191, 139, 98, 102, 221, 48, 253, 226, 152, 37, 179, 16, 145, 34, 136, 54, 208, 148, 206, 143, 150, 219, 189, 241, 210, 19, 92, 131, 56, 70, 64, 30, 66, 182, 163, 195, 72, 126, 110, 107, 58, 40, 84, 250, 133, 186, 61, 202, 94, 155, 159, 10, 21, 121, 43, 78, 212, 229, 172, 115, 243, 167, 87, 7, 112, 192, 247, 140, 128, 99, 13, 103, 74, 222, 237, 49, 197, 254, 24, 227, 165, 153, 119, 38, 184, 180, 124, 17, 68, 146, 217, 35, 32, 137, 46, 55, 63, 209, 91, 149, 188, 207, 205, 144, 135, 151, 178, 220, 252, 190, 97, 242, 86, 211, 171, 20, 42, 93, 158, 132, 60, 57, 83, 71, 109, 65, 162, 31, 45, 67, 216, 183, 123, 164, 118, 196, 23, 73, 236, 127, 12, 111, 246, 108, 161, 59, 82, 41, 157, 85, 170, 251, 96, 134, 177, 187, 204, 62, 90, 203, 89, 95, 176, 156, 169, 160, 81, 11, 245, 22, 235, 122, 117, 44, 215, 79, 174, 213, 233, 230, 231, 173, 232, 116, 214, 244, 234, 168, 80, 88, 175 };
       
        
        //----Свойства и методы для работы с характеристиками поля----//
        public static byte Mod
        {
            get
            {
                return mod;
            }
            set
            {
                foreach (byte posMod in PossibleMods)
                {
                    if (posMod == value)
                    {
                        mod = value;
                        SetDegree();
                    }
                }
            }
        }   
        private static void SetDegree()
        {
            byte x = 1;
            for (int i = 1; i < 255; i++)
            {
                if ((x & 0b10000000) == 0b10000000)
                {
                    x <<= 1;
                    x ^= mod;
                }
                else
                {
                    x <<= 1;
                }
                Degree[x] = (byte)(i);
            }
        }

        //----Перегрузка явного и неявного преобразования типов----//
        public static implicit operator GF256(int v)
        {
            return new GF256 { value = (byte)v };
        }
        public static explicit operator int(GF256 v)
        {
            return v.value;
        }

        //----Перегрузка операторов сравнения----//
        public static bool operator ==(GF256 first, GF256 second)
        {
            return first.Equals(second);
        }
        public static bool operator !=(GF256 first, GF256 second)
        {
            return !first.Equals(second);
        }

        //----Определение операторов суммы(+), произведения(*), частного(/), возведения в степень(^)----//
        public static GF256 operator +(GF256 first, GF256 second)
        {
            return first.value ^ second.value;
        }
        public static GF256 operator *(GF256 first, GF256 second)
        {
            if (first == 0 || second == 0)
            {
                return 0;
            }
            byte d = (byte)((Degree[(int)first] + Degree[(int)second]) % 255);
            for (int i = 1; i < Degree.Length; i++)
            {
                if (Degree[i] == d)
                {
                    return i;
                }
            }
            return -1;
        }
        public static GF256 operator /(GF256 first, GF256 second)
        {
            if (first == 0)
            {
                return 0;
            }
            if (second == 0)
            {
                throw new DivideByZeroException();
            }
            int newPow = (Degree[(int)first] - Degree[(int)second]) % 255;
            newPow = (newPow < 0) ? newPow + 255 : newPow;
            byte d = (byte)(newPow);
            for (int i = 1; i < Degree.Length; i++)
            {
                if (Degree[i] == d)
                {
                    return i;
                }
            }
            return -1;
        }
        public static GF256 operator ^(GF256 baze, int power)
        {
            if (power == 0)
            {
                return 1;
            }
            if (baze == 0 && power > 0)
            {
                return 0;
            }
            if (baze == 0 && power < 0)
            {
                throw new InvalidOperationException("Raising 0 to a degree less than 0");
            }
            int newPow = (Degree[(int)baze] * power) % 255;
            newPow = (newPow < 0) ? newPow + 255 : newPow;
            byte d = (byte)(newPow);
            for (int i = 1; i < Degree.Length; i++)
            {
                if (Degree[i] == d)
                {
                    return i;
                }
            }
            return -1;
        }
    }
}
