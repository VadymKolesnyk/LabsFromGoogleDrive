using SharpGL.SceneGraph;

namespace Lab1
{
    class Color
    {
        public byte R { get; set; }
        public byte G { get; set; }
        public byte B { get; set; }
        public Color()
        {
            R = G = B = 0;
        }
        public Color(byte r, byte g, byte b)
        {
            R = r;
            G = g;
            B = b;
        }
        public GLColor ToGLColor()
        {
            return new GLColor(R / 255f, G / 255f, B / 255f, 0);
        }
    }
}
