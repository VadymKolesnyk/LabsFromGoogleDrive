using SharpGL;
using SharpGL.Enumerations;
using SharpGL.SceneGraph;
using System;
using System.Windows.Forms;

namespace Lab3
{
    public partial class OpenGLForm : Form
    {

        #region Initialization
        public OpenGLForm()
        {
            InitializeComponent();
        }
        private void OpenGLInit(object sender, EventArgs e)
        {
            OpenGL gl = openGLControl1.OpenGL;

            gl.Enable(OpenGL.GL_DEPTH_TEST);
            gl.Enable(OpenGL.GL_LIGHTING);
            gl.Enable(OpenGL.GL_NORMALIZE);
            gl.Enable(OpenGL.GL_COLOR_MATERIAL);
            gl.ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            InitCamera();
            InitScene(gl);

        }
        private void InitCamera()
        {
            camera.Theta = 45;
            camera.Phi = 45;
            camera.RotationDiraction = Rotation.None;
            camera.Radius = 20;
        }
        private void InitScene(OpenGL gl)
        {
            Star star = new Star();
            star.EnableLight(gl);
            Surface surface = new Surface()
            {
                Function = (x, y) => Math.Sin(x) + Math.Cos(y),
                ColorLine = new GLColor(0.7f, 0.1f, 0.3f, 1f),
                Xmax = 50,
                Xmin = -50,
                Ymax = 50,
                Ymin = -50,
                Xrows = 500,
                Yrows = 500
            };
            scene.Objects.Add(surface);
            scene.Objects.Add(star);
        }

        #endregion

        readonly Scene scene = new Scene();
        readonly Camera camera = new Camera();
        private void OpenGLDraw(object sender, SharpGL.RenderEventArgs args)
        {
            OpenGL gl = openGLControl1.OpenGL;
            scene.Render(gl);
            camera.SetCamera(gl, Width, Height);
        }

        private void OpenGLResized(object sender, EventArgs e)
        {
            OpenGL gl = openGLControl1.OpenGL;
            camera.SetCamera(gl, Width, Height);
        }

        private void OpenGLKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.KeyCode)
            {
                case Keys.D1:
                    camera.RotationDiraction = Rotation.None;
                    break;
                case Keys.D2:
                    camera.RotationDiraction = Rotation.Phi;
                    break;
                case Keys.D3:
                    camera.RotationDiraction = Rotation.Theta;
                    break;
                case Keys.O:
                    camera.ProectionCamera = Proection.Ortho;
                    break;
                case Keys.P:
                    camera.ProectionCamera = Proection.Perspective;
                    break;
                case Keys.W:
                    camera.Theta -= 1;
                    if (camera.Theta <= 0)
                        camera.Theta += 360;
                    break;
                case Keys.A:
                    camera.Phi += 1;
                    if (camera.Phi > 360)
                        camera.Phi -= 360;
                    break;
                case Keys.S:
                    camera.Theta += 1;
                    if (camera.Theta > 360)
                        camera.Theta -= 360;
                    break;
                case Keys.D:
                    camera.Phi -= 1;
                    if (camera.Phi < 0)
                        camera.Phi += 360;
                    break;
                case Keys.Add:
                    camera.Radius *= 0.9;
                    break;
                case Keys.Subtract:
                    camera.Radius /= 0.9;
                    break;
                case Keys.Escape:
                    Application.Exit();
                    break;
                default:
                    break;
            }
        }
    }
}
