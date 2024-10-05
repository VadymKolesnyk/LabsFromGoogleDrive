using System;
using System.Threading;
using System.Threading.Tasks;

namespace Lab2
{
    internal class Generator
    {
        public Generator()
        {
            First.SecondProcessor = Second;
            Second.SecondProcessor = First;
        }

        public Processor First { get; } = new Processor(id: 1);
        public Processor Second { get; } = new Processor(id: 2);

        public async Task StartAsync()
        {
            Task first = Task.Run(() => StartForOne(First, 1));
            Task second = Task.Run(() => StartForOne(Second, 3));
            await first;
            await second;
        }

        private static void StartForOne(Processor processor, int speed)
        {
            Random random = new Random();
            while (true)
            {
                Thread.Sleep(random.Next(500 * speed, 1500 * speed));
                processor.AddProcessAsync(new Process(random.Next(2000 / speed, 3000 / speed)));
            }
        }
    }
}
