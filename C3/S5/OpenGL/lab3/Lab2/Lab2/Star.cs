using SharpGL;
using SharpGL.Enumerations;
using SharpGL.SceneGraph.Core;
using SharpGL.SceneGraph.Quadrics;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Lab3
{
    class Star : IRender
    {
        public double Phi { get; set; } = 0;
        public double H { get; set; } = 5;
        public double Radius { get; set; } = 10;
        public LightName LightName { get; set; } = LightName.Light0;
        public Rotation RotationDiraction { get; set; } = Rotation.Phi;
        void Rotate()
        {
            while (true)
            {
                switch (RotationDiraction)
                {
                    case Rotation.None:
                        break;
                    case Rotation.Phi:
                        Phi += 1;
                        if (Phi > 360)
                        {
                            Phi -= 360;
                        }
                        break;
                    case Rotation.Theta:
                        throw new Exception("Rotation.Theta cannot be used in Star rotation");
                }
                Thread.Sleep(1000 / 30);
            }
        }
        Task RotateAsync() => Task.Run(Rotate);
        public Star()
        {
            RotateAsync();
        }
        public void Render(OpenGL gl)
        {
            gl.MatrixMode(MatrixMode.Modelview);
            gl.LoadIdentity();

            gl.Light(LightName, LightParameter.Position, new float[] {  (float)(Math.Sin(Phi / 180 * Math.PI) * Radius),
                                                                        (float)H,
                                                                        (float)(Math.Cos(Phi / 180 * Math.PI) * Radius), 1 });
            gl.Light(LightName, LightParameter.Diffuse, new float[] { 1, 1, 1 });
            gl.Light(LightName, LightParameter.Specular, new float[] { 1, 1, 1 });
            gl.Light(LightName, LightParameter.ConstantAttenuatio, 0.4f);
            gl.Light(LightName, LightParameter.QuadraticAttenuation, 0.005f);
            gl.Disable(OpenGL.GL_LIGHTING);
            gl.PolygonMode(FaceMode.FrontAndBack, PolygonMode.Filled);
            Sphere star = new Sphere()
            {
                Radius = 0.3,
                QuadricDrawStyle = DrawStyle.Fill,

            };
            star.CreateInContext(gl);
            gl.Color(1.0, 1.0, 1.0);
            gl.Translate(Math.Sin(Phi / 180 * Math.PI) * Radius, H, Math.Cos(Phi / 180 * Math.PI) * Radius);
            star.Render(gl, RenderMode.Design);
            gl.Enable(OpenGL.GL_LIGHTING);
            gl.LoadIdentity();
        }
        public void EnableLight(OpenGL gl)
        {
            gl.Enable((uint)LightName);
        }
    }
}
