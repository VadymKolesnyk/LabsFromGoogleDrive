using SharpGL;
using SharpGL.Enumerations;
using SharpGL.SceneGraph;
namespace Lab2
{
    interface IRender
    {
        GLColor ColorLine { get; set; }
        GLColor ColorFill { get; set; }
        Matrix ModelViewMatrix { get; set; }
        PolygonMode Mode { get; set; }
        void Render(OpenGL gl);
    }
}
