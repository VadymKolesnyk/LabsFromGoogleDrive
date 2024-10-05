using SharpGL;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            openGLControl1.MouseWheel += OpenGLControl1_MouseWheel;
        }

        readonly Grid grid = new Grid();
        private void openGLControl1_Load(object sender, EventArgs e)
        {
            var gl = this.openGLControl1.OpenGL;
            gl.ClearColor(1, 1, 1, 1);
            gl.Enable(OpenGL.GL_LINE_SMOOTH);
        }

        private void openGLControl1_OpenGLDraw(object sender, SharpGL.RenderEventArgs args)
        {
            var gl = this.openGLControl1.OpenGL;
            grid.Draw(gl, Width, Height);

        }
        private void OpenGLControl1_MouseWheel(object sender, MouseEventArgs e)
        {
            grid.Scale *= Math.Pow(1.1, e.Delta / 120);
        }
    }
}
