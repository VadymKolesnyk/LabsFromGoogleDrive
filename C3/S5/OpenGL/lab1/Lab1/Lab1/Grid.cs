using Newtonsoft.Json;
using SharpGL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab1
{
    class Grid
    {
        private Color colorBackground;
        public Color ColorBackground
        {
            get { return colorBackground; }
            set
            {
                colorBackground = value;
                if (gLControl != null)
                {
                    gLControl.OpenGL.ClearColor(value.R / 255f, value.G / 255f, value.B / 255f, 0);
                }
            }
        }
        public Color ColorGrid { get; set; }
        public Color ColorAxes { get; set; }
        public int GridWidth { get; set; }
        public int AxesWidth { get; set; }
        public double Scale { get; set; }
        [JsonIgnore]
        private OpenGLControl gLControl;
        [JsonIgnore]
        public OpenGLControl GLControl
        {
            get { return gLControl; }
            set 
            {
                gLControl = value;
                gLControl.OpenGL.ClearColor(ColorBackground.R / 255f, ColorBackground.G / 255f, ColorBackground.B / 255f, 0);
            }
        }
        public void Draw()
        {
            OpenGL gl = GLControl.OpenGL;
            double width = GLControl.Width / Scale;
            double height = GLControl.Height / Scale;
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadIdentity();
            gl.Ortho2D(-width / 2, width / 2, -height / 2, height / 2);

            gl.Color(ColorGrid.ToGLColor());
            gl.LineWidth(GridWidth);
            gl.Begin(OpenGL.GL_LINES);
            for (int i = 1; i < width / 2; i++)
            {
                gl.Vertex(i, -height);
                gl.Vertex(i, height);
                gl.Vertex(-i, -height);
                gl.Vertex(-i, height);
            }
            for (int i = 1; i < height / 2; i++)
            {
                gl.Vertex(-width, i);
                gl.Vertex(width, i);
                gl.Vertex(-width, -i);
                gl.Vertex(width, -i);
            }

            gl.Color(ColorAxes.ToGLColor());
            gl.LineWidth(AxesWidth);
            gl.Vertex(0, -height);
            gl.Vertex(0, height);
            gl.Vertex(-width, 0);
            gl.Vertex(width, 0);
            gl.End();

        }
    }
}
