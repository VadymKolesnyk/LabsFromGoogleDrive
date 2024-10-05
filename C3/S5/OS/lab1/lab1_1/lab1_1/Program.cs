using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace lab1_1
{
    public class Synchronization
    {
        public ManualResetEvent QueueIsNotFull { get; }
        public ManualResetEvent QueueIsNotEmpty { get; }
        public Mutex OneProduct { get; }
        public Mutex ManufMutex { get; }
        public Mutex ConsMutex { get; }
        public Queue<Product> ProdQueue { get; }
        public int Capacity { get; }
        public Random Random { get; }
        public Synchronization(int capacity)
        {
            ProdQueue = new Queue<Product>(capacity);
            Capacity = capacity;
            QueueIsNotFull = new ManualResetEvent(initialState: true);
            QueueIsNotEmpty = new ManualResetEvent(initialState: false);
            Console.WriteLine("Очередь пуста");
            OneProduct = new Mutex();
            ManufMutex = new Mutex();
            ConsMutex = new Mutex();
            Random = new Random((int)DateTime.Now.Ticks);
        }

    }
    public class Product
    {
        public static int Counter { get; private set; } = 0;
        public int Id { get; }
        public Product()
        {
            Id = Counter++;
        }
    }
    public class Manufacturer
    {
        public static int Counter { get; private set; } = 0;
        public int Id { get; }
        private Thread threadProduce;
        private Synchronization workPlace;
        public bool IsWorking { get; private set; }
        public Manufacturer(Synchronization workPlace)
        {
            Id = Counter++;
            this.workPlace = workPlace;
            threadProduce = new Thread(Produce)
            {
                IsBackground = true
            };
            IsWorking = false;
        }
        public void StartWorking()
        {
            IsWorking = true;
            threadProduce.Start();
        }
        public void StopWorking()
        {
            IsWorking = false;
        }
        private void Produce()
        {
            while (IsWorking)
            {
                workPlace.ManufMutex.WaitOne();
                workPlace.QueueIsNotFull.WaitOne();

                workPlace.OneProduct.WaitOne();
                if (workPlace.ProdQueue.Count == 1)
                {
                    Thread.Sleep(workPlace.Random.Next() % 5000 + 1000);
                    Product product = new Product();
                    workPlace.ProdQueue.Enqueue(product);
                    Console.WriteLine($"Производитель № {Id} произвел продукт № {product.Id}\t\tВ очереди {workPlace.ProdQueue.Count}");
                    workPlace.OneProduct.ReleaseMutex();
                }
                else
                {
                    workPlace.OneProduct.ReleaseMutex();
                    Thread.Sleep(workPlace.Random.Next() % 5000 + 1000);
                    Product product = new Product();
                    workPlace.ProdQueue.Enqueue(product);
                    Console.WriteLine($"Производитель № {Id} произвел продукт № {product.Id}\t\tВ очереди {workPlace.ProdQueue.Count}");
                }
                if (workPlace.ProdQueue.Count == 1)
                {
                    workPlace.QueueIsNotEmpty.Set();
                }
                if (workPlace.ProdQueue.Count == workPlace.Capacity)
                {
                    workPlace.QueueIsNotFull.Reset();
                    Console.WriteLine("Очередь полна");
                }
                workPlace.ManufMutex.ReleaseMutex();
                Thread.Sleep(workPlace.Random.Next() % 5000 + 1000);
            }
        }
    }
    public class Consumer
    {
        public static int Counter { get; private set; } = 0;
        private Thread threadConsume;
        private Synchronization eatingPlace;

        public bool IsEating { get; private set; }
        public int Id { get; }
        public Consumer(Synchronization eatingPlace)
        {
            Id = Counter++;
            this.eatingPlace = eatingPlace;
            threadConsume = new Thread(Consume)
            {
                IsBackground = true
            };
            IsEating = false;
        }
        public void StartEating()
        {
            IsEating = true;
            threadConsume.Start();
        }
        public void StopEating()
        {
            IsEating = false;
        }
        private void Consume()
        {
            while (IsEating)
            {
                eatingPlace.ConsMutex.WaitOne();
                eatingPlace.QueueIsNotEmpty.WaitOne();

                eatingPlace.OneProduct.WaitOne();
                if (eatingPlace.ProdQueue.Count == 1)
                {
                    Thread.Sleep(eatingPlace.Random.Next() % 2000 + 1000);
                    Product product = eatingPlace.ProdQueue.Dequeue();
                    Console.WriteLine($"Потребитель № {Id} забрал продукт № {product.Id}\t\tВ очереди {eatingPlace.ProdQueue.Count}");
                    eatingPlace.OneProduct.ReleaseMutex();
                }
                else
                {
                    eatingPlace.OneProduct.ReleaseMutex();
                    Thread.Sleep(eatingPlace.Random.Next() % 2000 + 1000);
                    Product product = eatingPlace.ProdQueue.Dequeue();
                    Console.WriteLine($"Потребитель № {Id} забрал продукт № {product.Id}\t\tВ очереди {eatingPlace.ProdQueue.Count}");
                }
                if (eatingPlace.ProdQueue.Count == 0)
                {
                    eatingPlace.QueueIsNotEmpty.Reset();
                    Console.WriteLine("Очередь пуста");
                }
                if (eatingPlace.ProdQueue.Count == eatingPlace.Capacity - 1)
                {
                    eatingPlace.QueueIsNotFull.Set();
                }
                eatingPlace.ConsMutex.ReleaseMutex();
                Thread.Sleep(eatingPlace.Random.Next() % 2000 + 1000);
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Synchronization place = new Synchronization(5);
            Manufacturer[] manufacturers = (new Manufacturer[5]).Select(m => new Manufacturer(place)).ToArray();
            Consumer[] consumers = (new Consumer[10]).Select(c => new Consumer(place)).ToArray();

            foreach (Manufacturer manufacturer in manufacturers)
                manufacturer.StartWorking();

            Thread.Sleep(18000);

            foreach (Consumer consumer in consumers)
                consumer.StartEating();

            Console.ReadLine();

            foreach (Manufacturer manufacturer in manufacturers)
                manufacturer.StopWorking();

            foreach (Consumer consumer in consumers)
                consumer.StopEating();

        }
    }
}
