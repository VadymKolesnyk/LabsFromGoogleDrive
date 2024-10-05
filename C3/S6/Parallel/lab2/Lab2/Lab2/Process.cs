namespace Lab2
{
    internal class Process
    {
        private static int count = 0;

        public int Id { get; }
        public int Weight { get; }

        public Process(int weight)
        {
            Weight = weight;
            Id = ++count;
        }
    }
}
