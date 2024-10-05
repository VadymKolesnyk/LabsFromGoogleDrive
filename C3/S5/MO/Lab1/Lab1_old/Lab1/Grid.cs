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
        public double Scale { get; set; } = 10;
        public void Draw(OpenGL gl, double widthWindow, double heightWindow)
        {
            double width = widthWindow / Scale;
            double height = heightWindow / Scale;
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadIdentity();
            gl.Ortho2D(-width / 2, width / 2, -height / 2, height / 2);
            gl.Color(0.9, 0.9, 0.9);
            gl.LineWidth(1);
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
            gl.Color(0.4, 0.4, 0.4);
            gl.LineWidth(2);
            gl.Vertex(0, -height);
            gl.Vertex(0, height);
            gl.Vertex(-width, 0);
            gl.Vertex(width, 0);
            gl.End();

        }
    }
}
