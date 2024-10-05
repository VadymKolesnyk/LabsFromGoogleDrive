using SharpGL;
using SharpGL.Enumerations;
using SharpGL.SceneGraph;
using System;

namespace Lab2
{
    class Surface : IRender
    {
        public Matrix ModelViewMatrix { get; set; } = new Matrix(4, 4);
        public PolygonMode Mode { get; set; } = PolygonMode.Lines;
        public GLColor ColorLine { get; set; } = new GLColor(0, 0, 0, 1);
        public GLColor ColorFill { get; set; } = new GLColor(1, 1, 1, 1);
        public Func<double, double, double> Function { get; set; } = (x , y) => x + y;
        public float Xmin { get; set; } = -10;
        public float Xmax { get; set; } = 10;
        public float Ymin { get; set; } = -10;
        public float Ymax { get; set; } = 10;
        public int Xrows { get; set; } = 100;
        public int Yrows { get; set; } = 100;
        private double[] vertices;
        public Surface()
        {
            ModelViewMatrix.SetIdentity();
        }
        public void CalcVertices()
        {
            vertices = new double[Xrows * Yrows * 3];
            int iterator = 0;
            float xStep = (Xmax - Xmin) / Xrows;
            float yStep = (Ymax - Ymin) / Yrows;
            for (int i = 0; i < Xrows; i ++)
            {
                for (int j = 0; j < Yrows; j ++)
                {
                    vertices[iterator++] = Xmin + i * xStep;
                    vertices[iterator++] = Function(Xmin + i * xStep, Ymin + j * yStep);
                    vertices[iterator++] = Ymin + j * yStep;
                }
            }
        }
        public void Render(OpenGL gl)
        {
            if (vertices == null)
            {
                CalcVertices();
            }
            gl.MatrixMode(MatrixMode.Modelview);
            gl.LoadMatrix(ModelViewMatrix.AsRowMajorArray);
            gl.Color(ColorLine);
            gl.PointSize(2);
            gl.EnableClientState(OpenGL.GL_VERTEX_ARRAY);
            gl.VertexPointer(3, 0, vertices);
            gl.DrawArrays(OpenGL.GL_POINTS, 0, Xrows * Yrows);
            gl.DisableClientState(OpenGL.GL_VERTEX_ARRAY);
            gl.LoadIdentity();

        }
    }
}
