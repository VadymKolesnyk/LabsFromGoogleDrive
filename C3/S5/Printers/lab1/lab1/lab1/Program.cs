using System;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Text;
using System.Windows.Forms;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {

            using BinaryWriter writer = new BinaryWriter(File.Open(@"C:\Users\Vadik\Google Диск\Универ\3 курс\5 семестр\Принтеры\lab1\file.pcl",FileMode.Create),Encoding.Default);
            char esc = (char)ConsoleKey.Escape;
            writer.Write((esc + "E ").ToCharArray());// сброс принтера
            writer.Write((esc + "&l26a0o0E ").ToCharArray());   // A4, вертикальная страница, top margin = 0
            writer.Write((esc + "*p0x0Y ").ToCharArray()); 
            writer.Write((esc + "*c5611x8416Y ").ToCharArray()); // picture frame (logical size)
            writer.Write((esc + "*p0x0Y ").ToCharArray());
            writer.Write((esc + "*c0T ").ToCharArray());        // 0 в HP/GL2 в тек. позиции

            writer.Write((esc + "%1B ").ToCharArray());// hp-gl/2 
            writer.Write("IN;".ToCharArray());     // инициализация                                              
            writer.Write("SP1;".ToCharArray()); // выбор ручки (1 - черный, 5 - синий)    
            writer.Write("SC 0,3.3867,0,-3.3867,2;".ToCharArray()); // 
            writer.Write("IR0,100,0,100;".ToCharArray()); //    Устанавливает местоположения P1 и P2 в процентах от рамки изображения PCL.

            writer.Write("PU0,236;".ToCharArray()); // передвинуть ручку                внешняя рамка 10х5 см (2 см от вверха стр.)
            writer.Write("EA1181,827;".ToCharArray()); // рисовать прямоугольник

            writer.Write("PU59,295; ".ToCharArray()); // рамка фотографии 3х4 см (0.5 от внешней рамки)
            writer.Write("EA413,768; ".ToCharArray());


            writer.Write((esc + "%1A ").ToCharArray());// pcl
            writer.Write((esc + "(8U ").ToCharArray()); // набор символов

            writer.Write((esc + "*p420x350Y ").ToCharArray());
            writer.Write((esc + "(s1p20h20v24s3b16602T ").ToCharArray()); // шрифт
            writer.Write((esc + "&d0D ").ToCharArray()); // врубить режим подчеркивания
            writer.Write("Vadym Kolesyk ".ToCharArray());
            writer.Write((esc + "&d@ ").ToCharArray());  // вырубить режим подчеркивания
            writer.Write((esc + "*p520x+120Y ").ToCharArray());
            writer.Write((esc + "(s1p10h16v5s0b0T ").ToCharArray());
            writer.Write("Student ".ToCharArray());
            writer.Write((esc + "*p520x+120Y ").ToCharArray());
            writer.Write((esc + "(s1p20h12v1s-3b3T ").ToCharArray());
            writer.Write("vakol2001@gmail.com ".ToCharArray());
            writer.Write((esc + "*p520x+120Y ").ToCharArray());
            writer.Write((esc + "(s1p100h15v24s3b0T ").ToCharArray());
            writer.Write("Kyiv ".ToCharArray());
            writer.Write((esc + "(s10h12v0s0b4099T").ToCharArray());


            int w = 3;
            int h = 4;

            Bitmap temp = new Bitmap(@"C:\Users\Vadik\Google Диск\Универ\3 курс\5 семестр\Принтеры\lab1\lab1\lab1\printer.jpg");
            Bitmap img = new Bitmap(temp, new Size((int)(w * 600 / 2.54), (int)(h * 600 / 2.54)));
            byte[,] bitmap = new byte[img.Height, (int)Math.Ceiling(img.Width / 8.0)];
            for (int i = 0; i < img.Height; i++)
            {
                for (int j = 0; j < img.Width / 8; j++)
                {
                    for (int s = 0; s < 8; s++)
                    {
                        Color oc = img.GetPixel(j * 8 + s, i);
                        byte grayScale = (oc.R * 0.3) + (oc.G * 0.59) + (oc.B * 0.11) > 127 ? (byte)0 : (byte)1;
                        bitmap[i, j] = (byte)((bitmap[i, j] << 1) | grayScale);
                    }
                }
                if (img.Width / 8 != (int)Math.Ceiling(img.Width / 8.0))
                {
                    for (int s = 0; s <  img.Width % 8; s++)
                    {
                        Color oc = img.GetPixel((img.Width / 8) * 8 + s, i);
                        byte grayScale = (oc.R * 0.3) + (oc.G * 0.59) + (oc.B * 0.11) > 127 ? (byte)0 : (byte)1;
                        bitmap[i, img.Width / 8] = (byte)((bitmap[i, img.Width / 8] << 1) | grayScale);
                    }
                    bitmap[i, img.Width / 8] = (byte)(bitmap[i, img.Width / 8] << 8 - img.Width % 8);
                }
            }

            writer.Write((esc + "*t600R ").ToCharArray());
            writer.Write((esc + "*p59x295Y ").ToCharArray());  // в левый вверхний угол рамки
            writer.Write((esc + "*r"+ (int)(w * 600 / 2.54) + "s" + (int)(h * 600 / 2.54) + "T ").ToCharArray());

            writer.Write((esc + "*r1A ").ToCharArray());

            for (int i = 0; i < bitmap.GetLength(0); i++)
            {
                writer.Write((esc + "*b" + bitmap.GetLength(1) + "W").ToCharArray());
                for (int j = 0; j < bitmap.GetLength(1); j++)
                {
                    writer.Write(bitmap[i, j]);
                }

            }
            writer.Write((esc + "*rC").ToCharArray());

            writer.Write((esc + "E ").ToCharArray()); 
            writer.Close();







            try
            {
                File.Delete("C:\\Users\\Vadik\\Google Диск\\Универ\\3 курс\\5 семестр\\Принтеры\\lab1\\file.pdf");
            }
            catch (IOException e)
            {
                MessageBox.Show(e.Message,"Невозможно продолжить");
                Process.GetCurrentProcess().Kill();
            }
            Process pdf = new Process();
            pdf.StartInfo.FileName = @"C:\Program Files (x86)\Adobe\Acrobat DC\Acrobat\Acrobat.exe";
            Process convertor = new Process();
            convertor.StartInfo.FileName = @"C:\Users\Vadik\Google Диск\Универ\3 курс\5 семестр\Принтеры\WinPCLtoPDF.exe";
            convertor.StartInfo.Arguments = "\"C:\\Users\\Vadik\\Google Диск\\Универ\\3 курс\\5 семестр\\Принтеры\\lab1\\file.pcl\"";
            convertor.Start();
            convertor.WaitForExit();

            pdf.StartInfo.Arguments = "/A page=1=OpenActions \"C:\\Users\\Vadik\\Google Диск\\Универ\\3 курс\\5 семестр\\Принтеры\\lab1\\file.pdf\"";
            pdf.Start();
        }
    }
}
