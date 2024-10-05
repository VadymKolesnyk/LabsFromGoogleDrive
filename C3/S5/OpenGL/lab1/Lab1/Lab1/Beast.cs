using System;
using System.Collections.Generic;
using SharpGL;
using SharpGL.SceneGraph;
using Newtonsoft.Json;

namespace Lab1
{
    class Beast
    {
        public Color ColorFill { get; set; }
        public Color ColorLine { get; set; }
        public int LineWidth { get; set; }
        [JsonProperty]
        public Point Center { get; private set; }
        public Point Vector { get; set; }
        public List<Figure> Figures { get; set; }
        [JsonIgnore]
        private OpenGL gl;
        [JsonIgnore]
        public OpenGL GL {
            get { return gl; }
            set { gl = value; }
        }
        public Beast()
        {
            ColorFill = new Color { R = 255, G = 255, B = 255 };
            ColorLine = new Color { R = 0, G = 0, B = 0 };
            LineWidth = 1;
            Center = new Point { X = 0, Y = 0 };
            Vector = new Point { X = 1, Y = 1 };
        }

        private void Move(double x, double y)
        {
            Center.X += x;
            Center.Y += y;
            foreach (Figure figure in Figures)
            {
                figure.Move(x, y);
            }
        }
        public void MoveAlongVector()
        { 
            Move(Vector.X, Vector.Y);
        }
        public void MoveAgainstVector()
        {
            Move(-Vector.X, -Vector.Y);
        }

        public void MoveTo(double x, double y)
        {
            foreach (Figure figure in Figures)
            {
                figure.Move(x - Center.X, y - Center.Y);
            }
            Center.X = x;
            Center.Y = y;
        }

        public void Draw()
        {
            if (gl != null)
            {
                GLColor glColorFill = ColorFill.ToGLColor();
                GLColor glColorLine = ColorLine.ToGLColor();
                foreach (Figure figure in Figures)
                {
                    figure.Draw(gl, glColorFill, glColorLine, LineWidth);
                }
            }

        }
    }
}
