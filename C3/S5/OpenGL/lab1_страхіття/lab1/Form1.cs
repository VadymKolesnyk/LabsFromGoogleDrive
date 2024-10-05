
using SharpGL;
using SharpGL.SceneGraph;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab1
{
    public partial class Lab1 : Form
    {
        public Lab1()
        {
            InitializeComponent();

        }

        private void openGLControl_Load(object sender, EventArgs e)
        {
            OpenGL gl = this.openGLControl.OpenGL;
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.ClearColor(0, 0, 1, 0);
            gl.Enable(OpenGL.GL_LINE_SMOOTH);

        }
        double scale = 30;
        double x = 0;
        double y = 0;
        private void openGLControl_OpenGLDraw(object sender, SharpGL.RenderEventArgs args)
        {
            OpenGL gl = openGLControl.OpenGL;
            double width = openGLControl.Width / scale ;
            double height = openGLControl.Height / scale;
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.MatrixMode(OpenGL.GL_PROJECTION);
            gl.LoadIdentity();
            gl.Ortho2D(-width / 2, width / 2, -height / 2, height / 2);

            gl.Color(0.0, 0.48 , 1.0);
            gl.LineWidth(1);
            gl.Begin(OpenGL.GL_LINES);
            for (int i = 1; i < width  / 2; i ++) 
            {
                gl.Vertex(i, -height);
                gl.Vertex(i, height);
                gl.Vertex(-i, -height);
                gl.Vertex(-i, height);
            }
            for (int i = 1; i < height / 2; i++)
            {
                gl.Vertex(-width , i);
                gl.Vertex(width,i);
                gl.Vertex(-width,-i);
                gl.Vertex(width,-i);
            }

            gl.Color(0.0, 0.7, 1.0);
            gl.LineWidth(2);
            gl.Vertex(0, -height);
            gl.Vertex(0, height);
            gl.Vertex(-width, 0);
            gl.Vertex(width, 0);
            gl.End();
           // DrawKkangaroo(x, y, gl);
        }

        private void DrawKkangaroo(double x, double y, OpenGL gl)
        {
            gl.PolygonMode(OpenGL.GL_FRONT_AND_BACK, OpenGL.GL_FILL);
            gl.Color(1.0, 1.0, 0.0);
            DrawPoligons(x, y, gl);

            gl.LineWidth(2);
            gl.PolygonMode(OpenGL.GL_FRONT_AND_BACK, OpenGL.GL_LINE);
            gl.Color(0.0, 0.0, 0.0);
            DrawPoligons(x, y, gl);
        }

        private void DrawPoligons(double x, double y, OpenGL gl)
        {
            gl.Begin(OpenGL.GL_TRIANGLES);
            gl.Vertex(x + 1, y);
            gl.Vertex(x - 2, y);
            gl.Vertex(x - 2, y + 3);

            gl.Vertex(x -3, y);
            gl.Vertex(x - 2, y + 1);
            gl.Vertex(x - 2, y - 1);

            gl.Vertex(x - 2, y + 3);
            gl.Vertex(x - 2, y + 4.5);
            gl.Vertex(x - 3.5, y + 3);

            gl.Vertex(x, y);
            gl.Vertex(x + 2, y);
            gl.Vertex(x + 2, y - 2);

            gl.Vertex(x + 1, y - 1);
            gl.Vertex(x + 3, y - 3);
            gl.Vertex(x - 1, y - 3);
            gl.End();

            gl.Begin(OpenGL.GL_QUADS);
            gl.Vertex(x, y);
            gl.Vertex(x + 1, y - 1);
            gl.Vertex(x, y - 2);
            gl.Vertex(x - 1, y - 1);

            gl.Vertex(x + 2, y - 2);
            gl.Vertex(x + 4, y - 2);
            gl.Vertex(x + 5, y - 3);
            gl.Vertex(x + 3, y - 3);
            gl.End();
        }
        private void Lab1_Load(object sender, EventArgs e)
        {
        }

        private void openGLControl_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '+')
            {
                scale *= 1.1;
            }
            else if (e.KeyChar == '-')
            {
                scale /= 1.1;
            }
            else if (e.KeyChar == 'w' || e.KeyChar == 'ц')
            {
                x--;
            }
            else if (e.KeyChar == 'a' || e.KeyChar == 'ф')
            {
                x++;
            }
            else if (e.KeyChar == 's' || e.KeyChar == 'і')
            {
                x++;
            }
            else if (e.KeyChar == 'd' || e.KeyChar == 'в')
            {
                x--;
            }
        }

        //private void openGLControl_KeyDown(object sender, KeyEventArgs e)
        //{

        //}

        //private void openGLControl_KeyUp(object sender, KeyEventArgs e)
        //{

        //}
    }
}
