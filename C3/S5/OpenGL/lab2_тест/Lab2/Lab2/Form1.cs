using SharpGL;
using SharpGL.Shaders;
using SharpGL.Enumerations;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SharpGL.VertexBuffers;
using SharpGL.SceneGraph;

namespace Lab2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        ShaderProgram shaderProgram = new ShaderProgram();
        VertexBuffer vertexBuffer = new VertexBuffer();
        VertexBufferArray vertexBufferArray = new VertexBufferArray();
        float[] vertices = {
            // Первый треугольник
             0.5f,  0.5f, 0.0f,  // Верхний правый угол
             0.5f, -0.5f, 0.0f,  // Нижний правый угол
            -0.5f,  0.5f, 0.0f,  // Верхний левый угол
            // Второй треугольник
             0.5f, 0.5f, 0.0f,  // Нижний правый угол
            -0.5f, -0.5f, 0.0f,  // Нижний левый угол
            -0.5f,  0.5f, 0.0f   // Верхний левый угол  
            };
        private void openGLControl1_Load(object sender, EventArgs e)
        {
            var gl = openGLControl1.OpenGL;
            shaderProgram.Create(gl,
                ManifestResourceLoader.LoadTextFile(@"Shaders\VertexShader.vert"),
                ManifestResourceLoader.LoadTextFile(@"Shaders\FragmentShader.frag"), null);
            vertexBufferArray.Create(gl);
            vertexBuffer.Create(gl);
            vertexBufferArray.Bind(gl);
            vertexBuffer.Bind(gl);
            vertexBuffer.SetData(gl, 0, vertices, false, 3);
            vertexBuffer.Unbind(gl);
            vertexBufferArray.Unbind(gl);

        }
        double timeValue = 0;
        private void openGLControl1_OpenGLDraw(object sender, SharpGL.RenderEventArgs args)
        {


            var gl = openGLControl1.OpenGL;

            gl.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            gl.Clear(OpenGL.GL_COLOR_BUFFER_BIT | OpenGL.GL_DEPTH_BUFFER_BIT);
            gl.PolygonMode(OpenGL.GL_FRONT_AND_BACK, OpenGL.GL_FILL);
            shaderProgram.Bind(gl);
            double greenValue = (Math.Sin(timeValue) / 2) + 0.5;
            timeValue += 0.1;
            //gl.Uniform4(shaderProgram.GetUniformLocation(gl, "ourColor"), 0.0f, (float)greenValue, 0.0f, 1.0f);
            Matrix trans = new Matrix(new double[4, 4]);
            trans.SetIdentity();
            trans[0, 1] = 2;
            shaderProgram.SetUniformMatrix4(gl, "transform", trans.AsColumnMajorArrayFloat);
            vertexBufferArray.Bind(gl);
            gl.DrawArrays(OpenGL.GL_TRIANGLES, 0, 6);
            vertexBufferArray.Unbind(gl);
            //gl.MatrixMode(OpenGL.GL_MODELVIEW);
            //gl.LoadIdentity();
            ////gl.GetFloatv(GL_MODELVIEW_MATRIX, m);
            //gl.LookAt(
            //    300.0f, 0.0f, 0.0f,
            //    5.0f, 5.0f, 5.0f,
            //    0.0f, 1.0f, 0.0f
            //);
        }
    }
}
