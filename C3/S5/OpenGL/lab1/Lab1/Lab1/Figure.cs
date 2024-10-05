using System.Collections.Generic;
using SharpGL;
using SharpGL.SceneGraph;

namespace Lab1
{

    class Figure
    {
        public List<Point> Vertices { get; set; }

        public void Move(double x, double y)
        {
            foreach (Point vertex in Vertices)
            {
                vertex.X += x;
                vertex.Y += y;
            }
        }
        public void Draw(OpenGL gl, GLColor colorFill, GLColor colorLine, int lineWidth)
        {
            gl.PolygonMode(OpenGL.GL_FRONT_AND_BACK, OpenGL.GL_FILL);
            gl.Color(colorFill);
            DrawPolygon(gl);
            gl.LineWidth(lineWidth);
            gl.PolygonMode(OpenGL.GL_FRONT_AND_BACK, OpenGL.GL_LINE);
            gl.Color(colorLine);
            DrawPolygon(gl);
        }

        private void DrawPolygon(OpenGL gl)
        {
            gl.Begin(OpenGL.GL_POLYGON);
            foreach (Point vertex in Vertices)
            {
                gl.Vertex(vertex.X, vertex.Y);
            }
            gl.End();
        }
    }
}
