using SharpGL;
using SharpGL.Enumerations;
using SharpGL.SceneGraph;

namespace Lab2
{
    class Cube : IRender
    {
        public Matrix ModelViewMatrix { get; set; } = new Matrix(4, 4);
        public PolygonMode Mode { get; set; } = PolygonMode.Lines;
        public GLColor ColorLine { get; set; } = new GLColor(0, 0, 0, 1);
        public GLColor ColorFill { get ; set ; } = new GLColor(1, 1, 1, 1);
        float x = 0;
        public Cube()
        {
            ModelViewMatrix.SetIdentity();
        }
        public void Render(OpenGL gl)
        {
            gl.MatrixMode(MatrixMode.Modelview);
            gl.LoadMatrix(ModelViewMatrix.AsRowMajorArray);
            gl.Rotate(x++, 0, 0);
            gl.Color(ColorLine);
            gl.LineWidth(2);
            gl.PolygonMode(FaceMode.FrontAndBack, PolygonMode.Lines);
            RenderPolygons(gl);
            if (Mode == PolygonMode.Filled)
            {
                gl.Color(ColorFill);
                gl.LineWidth(2);
                gl.PolygonMode(FaceMode.FrontAndBack, PolygonMode.Filled);
                RenderPolygons(gl);
            }


            gl.LoadIdentity();
        }

        private static void RenderPolygons(OpenGL gl)
        {
            gl.Begin(BeginMode.QuadStrip);
            {
                gl.Vertex(1, 1, 1);
                gl.Vertex(-1, 1, 1);
                gl.Vertex(1, -1, 1);
                gl.Vertex(-1, -1, 1);
                gl.Vertex(1, -1, -1);
                gl.Vertex(-1, -1, -1);
                gl.Vertex(1, 1, -1);
                gl.Vertex(-1, 1, -1);
                gl.Vertex(1, 1, 1);
                gl.Vertex(-1, 1, 1);
            }
            gl.End();
            gl.Begin(BeginMode.Quads);
            {
                gl.Vertex(1, 1, 1);
                gl.Vertex(1, -1, 1);
                gl.Vertex(1, -1, -1);
                gl.Vertex(1, 1, -1);

                gl.Vertex(-1, 1, 1);
                gl.Vertex(-1, -1, 1);
                gl.Vertex(-1, -1, -1);
                gl.Vertex(-1, 1, -1);
            }
            gl.End();
        }
    }
}
