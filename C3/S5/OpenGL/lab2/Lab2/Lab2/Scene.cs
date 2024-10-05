using SharpGL;
using SharpGL.Enumerations;
using SharpGL.SceneGraph.Quadrics;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Scene
    {
        public List<IRender> Objects { get; } = new List<IRender>();
        private static void RenderAxes(OpenGL gl)
        {
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.MatrixMode(MatrixMode.Modelview);
            gl.LoadIdentity();
            gl.LineWidth(1.5f);
            gl.Begin(BeginMode.Lines);
            {
                gl.Color(1.0f, 0.0f, 0.0f); // Красный y
                gl.Vertex(0.0f, -5.0f, 0.0f);
                gl.Vertex(0.0f, 10.0f, 0.0f);
                gl.Color(0.0f, 1.0f, 0.0f); // Зеленый x
                gl.Vertex(-5.0f, 0.0f, 0.0f);
                gl.Vertex(10.0f, 0.0f, 0.0f);
                gl.Color(0.0f, 0.0f, 1.0f); // Синий z
                gl.Vertex(0.0f, 0.0f, -5.0f);
                gl.Vertex(0.0f, 0.0f, 10.0f);
            }
            gl.End();
            Cylinder x = new Cylinder();
            Cylinder y = new Cylinder();
            Cylinder z = new Cylinder();
            x.CreateInContext(gl);
            y.CreateInContext(gl);
            z.CreateInContext(gl);
            x.QuadricDrawStyle = y.QuadricDrawStyle = z.QuadricDrawStyle = DrawStyle.Fill;
            x.BaseRadius = y.BaseRadius = z.BaseRadius = 0.15;
            x.Height = y.Height = z.Height = 0.5;
            gl.Color(1.0f, 0.0f, 0.0f);
            gl.Translate(0, 10, 0);
            gl.Rotate(-90, 0, 0);
            y.Render(gl, 0);

            gl.Color(0.0f, 1.0f, 0.0f);
            gl.LoadIdentity();
            gl.Translate(10, 0, 0);
            gl.Rotate(0, 90, 0);
            x.Render(gl, 0);

            gl.Color(0.0f, 0.0f, 1.0f);
            gl.LoadIdentity();
            gl.Translate(0, 0, 10);

            z.Render(gl, 0);
            gl.LoadIdentity();
        }
        public void Render(OpenGL gl)
        {
            RenderAxes(gl);
            foreach (var obj in Objects)
            {
                obj.Render(gl);
            }
        }
    }
}
