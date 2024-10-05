using SharpGL;
using SharpGL.Enumerations;
using SharpGL.SceneGraph;
using System;
using System.Windows.Forms;

namespace Lab2
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
            Octahedron octahedron = new Octahedron()
            {
                ColorLine = new GLColor(0.1f, 0.5f, 0.7f, 1f)
            };
            Cube cube = new Cube()
            {
                Mode = PolygonMode.Filled
            };
            Surface surface = new Surface()
            {
                Function = (x, y) => Math.Sin(x) + Math.Cos(y),
                ColorLine = new GLColor(0.7f, 0.1f, 0.3f, 1f),
                Xmax = 100,
                Xmin = -100,
                Ymax = 100,
                Ymin = -100,
                Xrows = 1000,
                Yrows = 1000
            };
            gl.MatrixMode(MatrixMode.Modelview);
            gl.LoadIdentity();
            gl.Translate(4, 5, 1);
            gl.Scale(1.5, 1.5, 1.5);
            gl.Rotate(27, 1, 0, 0);

            octahedron.ModelViewMatrix = gl.GetModelViewMatrix();
            gl.LoadIdentity();
            gl.Translate(-4, 5, -1);
            gl.Rotate(-45, 0, 1, 0);

            cube.ModelViewMatrix = gl.GetModelViewMatrix();

            scene.Objects.Add(cube);
            scene.Objects.Add(octahedron);
            scene.Objects.Add(surface);
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
