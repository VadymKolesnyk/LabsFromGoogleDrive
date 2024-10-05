using SharpGL;
using SharpGL.Enumerations;
using System;
using System.Threading;
using System.Threading.Tasks;

namespace Lab3
{
    enum Rotation
    {
        None,
        Phi,
        Theta
    }
    enum Proection
    {
        Ortho,
        Perspective
    }
    class Camera
    {
        public double Phi { get; set; } = 0;
        public double Theta { get; set; } = 0;
        public double Radius { get; set; } = 15;
        public Rotation RotationDiraction { get; set; } = Rotation.None;
        public Proection ProectionCamera { get; set; } = Proection.Perspective;
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
                        Theta += 1;
                        if (Theta > 360)
                        {
                            Theta -= 360;
                        }
                        break;
                }
                Thread.Sleep(1000/30);
            }
        }
        Task RotateAsync() => Task.Run(Rotate);
        public Camera() => RotateAsync();
        public void SetCamera(OpenGL gl, double width, double height)
        {
            gl.MatrixMode(MatrixMode.Projection);
            gl.LoadIdentity();
            switch (ProectionCamera)
            {
                case Proection.Ortho:
                gl.Ortho(-12 * (width / height), 12 * (width / height), -12, 12, -100, 100);
                    break;
                case Proection.Perspective:
                    gl.Perspective(60.0f, width / height, 0.01, 500.0);
                    break;
                default:
                    break;
            }
            gl.LookAt(
                Radius * Math.Sin(Theta / 180 * Math.PI) * Math.Cos(Phi / 180 * Math.PI),
                Radius * Math.Cos(Theta / 180 * Math.PI),
                Radius * Math.Sin(Theta / 180 * Math.PI) * Math.Sin(Phi / 180 * Math.PI),
                0, 0, 0,
                0, Theta > 180 ? -1 : 1, 0) ;
            gl.MatrixMode(MatrixMode.Modelview);

        }
    }
}
