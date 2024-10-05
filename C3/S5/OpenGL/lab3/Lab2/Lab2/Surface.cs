using SharpGL;
using SharpGL.Enumerations;
using SharpGL.SceneGraph;
using System;
using System.Linq;

namespace Lab3
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
        private float[] normals;
        public Surface()
        {
            ModelViewMatrix.SetIdentity();
        }
        public void CalcVertices()
        {
            vertices = new double[Xrows * Yrows * 3];
            normals = new float[Xrows * Yrows * 3];
            int iterator = 0;
            float xStep = (Xmax - Xmin) / Xrows;
            float yStep = (Ymax - Ymin) / Yrows;
            for (int i = 0; i < Xrows; i ++)
            {
                for (int j = 0; j < Yrows; j ++)
                {
                    float[] dx = new float[] {  (Xmin + (i + 1) * xStep) - (Xmin + (i - 1) * xStep),
                                                (float)(Function(Xmin + (i + 1) * xStep, Ymin + j * yStep) - Function(Xmin + (i - 1) * xStep, Ymin + j * yStep)),
                                                0};
                    float[] dy = new float[] {  0,
                                                (float)(Function(Xmin + i * xStep, Ymin + (j + 1) * yStep) - Function(Xmin + i * xStep, Ymin + (j - 1) * yStep)),
                                                (Ymin + (j + 1) * yStep) - (Ymin + (j - 1) * yStep)};
                    normals[iterator] = dx[2] * dy[1] - dx[1] * dy[2];
                    vertices[iterator++] = Xmin + i * xStep;
                    normals[iterator] = dx[0] * dy[2] - dx[2] * dy[0];
                    vertices[iterator++] = Function(Xmin + i * xStep, Ymin + j * yStep);
                    normals[iterator] = dx[1] * dy[0] - dx[0] * dy[1];
                    vertices[iterator++] = Ymin + j * yStep;
                }
            }
        }
        public void Render(OpenGL gl)
        {
            if (vertices is null)
            {
                CalcVertices();
            }
            gl.MatrixMode(MatrixMode.Modelview);
            gl.LoadMatrix(ModelViewMatrix.AsRowMajorArray);
            gl.Color(ColorLine);
            gl.PointSize(3);
            gl.EnableClientState(OpenGL.GL_VERTEX_ARRAY);
            gl.EnableClientState(OpenGL.GL_NORMAL_ARRAY);
            gl.VertexPointer(3, 0, vertices);
            gl.NormalPointer(OpenGL.GL_FLOAT, 0, normals);
            gl.DrawArrays(OpenGL.GL_POINTS, 0, Xrows * Yrows);
            gl.DisableClientState(OpenGL.GL_VERTEX_ARRAY);
            gl.DisableClientState(OpenGL.GL_NORMAL_ARRAY);
            gl.LoadIdentity();

        }
    }
}
