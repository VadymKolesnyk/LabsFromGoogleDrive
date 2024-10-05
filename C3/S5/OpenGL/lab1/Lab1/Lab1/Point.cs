namespace Lab1
{
    class Point
    {
        public double X { get; set; }
        public double Y { get; set; }

        public Point()
        {
            X = Y = 0;
        }

        public Point(double x, double y)
        {
            X = x;
            Y = y;
        }
    }
}
