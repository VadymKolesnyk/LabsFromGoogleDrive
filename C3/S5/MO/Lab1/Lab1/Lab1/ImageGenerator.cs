using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Lab1
{
    static class ImageGenerator
    {
        const int size = 800;
        private static (double x, double y) Coord(int i, int j)
        {
            return ((double)i / 100 - 4, (double)-j / 100 - 4);

        } 
        public static void Generate(Func<double, double, double> func, Dictionary<double,Color> levels)
        {
            Bitmap bitmap = new Bitmap(size, size);
            for (int i = 0; i < bitmap.Width; i++)
            {
                for (int j = 0; j < bitmap.Height; j++)
                {
                    foreach (var level in levels)
                    {
                        var (x, y) = Coord(i, j);
                        if (Math.Abs(func(x,y) - level.Key) < 0.01 )
                        {
                            bitmap.SetPixel(i, j, level.Value);
                        }
                    }
                }
            }







            SaveFileDialog saveFileDialog = new SaveFileDialog
            {
                DefaultExt = "jpg",
                AddExtension = true,
                Filter = "Image files (*.jpg)|*.jpg|Bitmap files (*.bmp)|*.bmp",
                FileName = "image.jpg"
            };
            if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
                return;
            bitmap.Save(saveFileDialog.FileName);
        }
    }
}