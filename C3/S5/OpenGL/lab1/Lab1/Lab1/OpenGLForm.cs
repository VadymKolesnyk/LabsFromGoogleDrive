using SharpGL;
using System;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.IO;

namespace Lab1
{
    public partial class OpenGLForm : Form
    {
        public OpenGLForm()
        {
            InitializeComponent();
        }

        private void OpenGLControl_Load(object sender, EventArgs e)
        {
            OpenGL gl = this.openGLControl.OpenGL;

            gl.Enable(OpenGL.GL_LINE_SMOOTH);
            string jsonString = File.ReadAllText("../../Files/beast.json");
            beast = JsonConvert.DeserializeObject<Beast>(jsonString);
            beast.GL = openGLControl.OpenGL;
            jsonString = File.ReadAllText("../../Files/grid.json");
            grid = JsonConvert.DeserializeObject<Grid>(jsonString);
            grid.GLControl = openGLControl;

            
        }
        private void OpenGLControl_OpenGLDraw(object sender, SharpGL.RenderEventArgs args)
        {
            grid.Draw();
            beast.Draw();
        }

        private void OpenGLControl_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == 'w' || e.KeyChar == 'd' || e.KeyChar == 'ц' || e.KeyChar == 'в')
            {
                beast.MoveAlongVector();
            }
            else if(e.KeyChar == 'a' || e.KeyChar == 's' || e.KeyChar == 'ф' || e.KeyChar == 'і' || e.KeyChar == 'ы')
            {
                beast.MoveAgainstVector();
            }
            else if (e.KeyChar == ' ')
            {
                beast.MoveTo(0, 0);
            }
            else if (e.KeyChar == '+')
            {
                grid.Scale *= 1.1;
            }
            else if (e.KeyChar == '-')
            {
                grid.Scale /= 1.1;
            }
        }

        private void OpenGLForm_Load(object sender, EventArgs e)
        {

        }
    }
}
