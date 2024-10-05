using System;
using System.Collections.Concurrent;
using System.Threading;
using System.Threading.Tasks;
#pragma warning disable CS4014 // Так как этот вызов не ожидается, выполнение существующего метода продолжается до тех пор, пока вызов не будет завершен
namespace Lab2
{
    internal class Processor
    {
        public Processor(int id)
        {
            Id = id;
        }

        public int MaxSizeOfQueue { get; private set; } = 0;
        private readonly SemaphoreSlim semaphoreAdd = new SemaphoreSlim(1, 1);

        public bool Working { get; private set; } = false;
        public Processor SecondProcessor { get; set; }
        public int Id { get; }

        public ConcurrentQueue<Process> Queue { get; } = new ConcurrentQueue<Process>();

        public Task AddProcessAsync(Process process)
        {
            return Task.Run(async () =>
            {
                await semaphoreAdd.WaitAsync();
                Queue.Enqueue(process);
                Console.WriteLine($"Process {process.Id} is in queue {Id}");
                if (Queue.Count > MaxSizeOfQueue)
                {
                    MaxSizeOfQueue = Queue.Count;
                    Console.WriteLine($"+-------------------------------+\n" +
                                      $"| New maximum of queue {Id,1} = {MaxSizeOfQueue,-5}|\n" +
                                      $"+-------------------------------+");
                }

                if (!Working)
                {
                    StartAsync();
                }
                if (!SecondProcessor.Working)
                {
                    SecondProcessor.StartAsync();
                }
                semaphoreAdd.Release();
            });
        }
        public Task StartAsync()
        {
            Working = true;
            return Task.Run(Start);
        }

        private void Start()
        {
            while (Queue.TryDequeue(out Process process) || SecondProcessor.Queue.TryDequeue(out process))
            {
                Console.WriteLine($"\t\t\t\t\t\t\tProcess {process.Id} is being handled on processor {Id}");
                Thread.Sleep(process.Weight);
                Console.WriteLine($"\t\t\t\t\t\t\tProcess {process.Id} was handled on processor {Id}");
            }
            Working = false;
        }
    }
}
