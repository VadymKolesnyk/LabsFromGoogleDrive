using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace Lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            int variant = 14;

            First(variant);
            Console.WriteLine('\n' + new string('-', 50));
            Second(variant);
            Console.WriteLine('\n' + new string('-', 50));
            Third(variant);
            Console.WriteLine('\n' + new string('-', 50));
            Fourth(variant);
            Console.WriteLine('\n' + new string('-', 50));
            Fifth(variant);
        }

        static int WrapperInt32(ref int target, int argument, Func<int, int, int> calc)
        {
            int valueAtTheBegin, calculatedValue;
            int currentValue = target;
            do
            {
                valueAtTheBegin = currentValue;
                calculatedValue = calc(valueAtTheBegin, argument);
                currentValue = Interlocked.CompareExchange(ref target, calculatedValue, valueAtTheBegin);
            } while (currentValue != valueAtTheBegin);
            return calculatedValue;
        }

        static long WrapperInt64WithIndex(ref long target, ref long index, long argument, long argumentIndex, Func<long, long, long> calc)
        {
            long valueAtTheBegin, calculatedValue;
            long indexAtTheBegin;
            long currentValue = target;
            long currentIndex = index;
            do
            {
                valueAtTheBegin = currentValue;
                indexAtTheBegin = currentIndex;
                calculatedValue = calc(valueAtTheBegin, argument);
                currentValue = Interlocked.CompareExchange(ref target, calculatedValue, valueAtTheBegin);
                if (calculatedValue != valueAtTheBegin)
                {
                    currentIndex = Interlocked.CompareExchange(ref index, argumentIndex, indexAtTheBegin);
                }
            } while (currentValue != valueAtTheBegin || currentIndex != indexAtTheBegin);
            return calculatedValue;
        }

        static Ttarget WrapperClass<Ttarget, Tagrument>(ref Ttarget target, Tagrument argument, Func<Ttarget, Tagrument, Ttarget> calc) where Ttarget : class
        {
            Ttarget valueAtTheBegin, calculatedValue;
            Ttarget currentValue = target;
            do
            {
                valueAtTheBegin = currentValue;
                calculatedValue = calc(valueAtTheBegin, argument);
                currentValue = Interlocked.CompareExchange(ref target, calculatedValue, valueAtTheBegin);
            } while (currentValue != valueAtTheBegin);
            return calculatedValue;
        }

        private static void First(int variant)
        {
            Random rand = new Random();
            var input = Enumerable.Repeat(0, variant * 10000).Select(i => rand.Next()).ToList();

            Console.WriteLine();
            int xor = 0;
            input.AsParallel().ForAll(element => WrapperInt32(ref xor, element, (a, b) => a ^ b));
            Console.WriteLine($"C синхронизацией\txor = {xor}");

            xor = 0;
            input.AsParallel().ForAll(element => xor ^= element);
            Console.WriteLine($"Без синхронизацией\txor = {xor}");

            xor = 0;
            xor = input.Aggregate(xor, (a, b) => a ^ b);
            Console.WriteLine($"Последовательный метод\txor = {xor}");
        }

        private static void Second(int variant)
        {
            Random rand = new Random();
            var input = Enumerable.Repeat(0, variant * 10000)
                                  .Select(i => ((long)rand.Next(int.MinValue, int.MaxValue) << 32) | (long)rand.Next(int.MinValue, int.MaxValue))
                                  .ToList();
            Console.WriteLine();
            long max = long.MinValue, min = long.MaxValue;
            long maxIndex = -1, minIndex = -1;
            input.AsParallel().Select((value, index) => (Value: value, Index: index)).ForAll(element =>
                {
                    WrapperInt64WithIndex(ref max, ref maxIndex, element.Value, element.Index, Math.Max);
                    WrapperInt64WithIndex(ref min, ref minIndex, element.Value, element.Index, Math.Min);
                });
            Console.WriteLine($"C синхронизацией\tmax = input[{maxIndex}]\t= {max}\t\tmin = input[{minIndex}]\t= {min}");

            max = long.MinValue; min = long.MaxValue;
            maxIndex = -1; minIndex = -1;
            input.AsParallel().Select((value, index) => (Value: value, Index: index)).ForAll(element =>
                {
                    long oldMax = max;
                    max = Math.Max(element.Value, max);
                    if (oldMax != max)
                    {
                        maxIndex = element.Index;
                    }
                    long oldMin = min;
                    min = Math.Min(element.Value, min);
                    if (oldMin != min)
                    {
                        minIndex = element.Index;
                    }
                });
            Console.WriteLine($"Без синхронизацией\tmax = input[{maxIndex}]\t= {max}\t\tmin = input[{minIndex}]\t= {min}");

            max = input.Max();
            min = input.Min();
            Console.WriteLine($"Последовательный метод\tmax = input[{input.IndexOf(max)}]\t= {max}\t\tmin = input[{input.IndexOf(min)}]\t= {min}");
        }

        private static void Third(int variant)
        {
            Random rand = new Random();
            var input = Enumerable.Repeat(0, variant * 10000).Select(i => (long)rand.Next(0, 0xFFFFFF + 1) << 20).ToList();
            #region Вывод маленького массива
            //var input = Enumerable.Repeat(0, 10).Select(i => ((long)rand.Next(-2, 2))).ToList();
            //foreach (var item in input)
            //{
            //    Console.Write(item + "\t");
            //}
            #endregion
            Console.WriteLine();

            var medians = input.AsParallel()
                               .Select((value, index) => (Value: value, Index: index))
                               .OrderBy(element => element.Value)
                               .Skip((input.Count - 1) / 2)
                               .Take(input.Count % 2 == 1 ? 1 : 2)
                               .ToList();
            var indexes = medians.Select(element => element.Index).ToList();
            double median = medians.Average(element => element.Value);
            string indexString = string.Join("; ", indexes.Select(index => index.ToString()).ToArray());
            Console.WriteLine($"\t\t\tmedian = input[{indexString}]\t= {median}");

            Console.WriteLine();

            int locker = 0; // 0 - unlocked, 1 - locked
            var dictionary = new Dictionary<long, ListOfIndexes>();

            input.AsParallel()
                 .Select((value, index) => (Value: value, Index: index))
                 .ForAll(element =>
                 {
                     while (Interlocked.CompareExchange(ref locker, 1, 0) != 0);
                     dictionary.TryAdd(element.Value, new ListOfIndexes());
                     Interlocked.Exchange(ref locker, 0);
                     WrapperClass(ref dictionary[element.Value].list, element.Index, (list, element) => list.Add(element));
                 });
            long max = long.MinValue;
            long maxKey = 0;
            dictionary.AsParallel()
                      .ForAll(element => WrapperInt64WithIndex(ref max, ref maxKey, element.Value.List.Count, element.Key, Math.Max));
            long moda = maxKey;
            indexString = string.Join("; ", dictionary[maxKey].List.OrderBy(index => index).Select(index => index.ToString()).ToArray());
            Console.WriteLine($"C синхронизацией\tmoda = input[{indexString}]\t= {moda}");


            dictionary = new Dictionary<long, ListOfIndexes>();
            foreach (var value in input.Distinct())
            {
                dictionary.Add(value, new ListOfIndexes());
            }
            input.AsParallel()
                 .Select((value, index) => (Value: value, Index: index))
                 .ForAll(element => dictionary[element.Value].List = dictionary[element.Value].List.Add(element.Index));
            max = long.MinValue;
            maxKey = 0;
            dictionary.AsParallel()
                      .ForAll(element =>
                      {
                          long oldMax = max;
                          max = Math.Max(element.Value.List.Count, max);
                          if (oldMax != max)
                          {
                              maxKey = element.Key;
                          }
                          WrapperInt64WithIndex(ref max, ref maxKey, element.Value.List.Count, element.Key, Math.Max);
                      });
            moda = maxKey;
            indexString = string.Join("; ", dictionary[maxKey].List.OrderBy(index => index).Select(index => index.ToString()).ToArray());
            Console.WriteLine($"Без синхронизацией\tmoda = input[{indexString}]\t= {moda}");

            var res = input.Select((value, index) => (Value: value, Index: index))
                           .GroupBy(element => element.Value)
                           .OrderBy(group => group.LongCount())
                           .Last();
            moda = res.Key;
            indexString = string.Join("; ", res.OrderBy(element => element.Index).Select(element => element.Index.ToString()).ToArray());
            Console.WriteLine($"Последовательный метод\tmoda = input[{indexString}]\t= {moda}");
        }

        private static void Fourth(int variant)
        {
            Random rand = new Random();
            var vectorA = Enumerable.Repeat(0, variant * 10000).Select(i => rand.Next(-100, 100)).ToList();
            var vectorB = Enumerable.Repeat(0, variant * 10000).Select(i => rand.Next(-100, 100)).ToList();
            Console.WriteLine();
            int dot = 0;
            vectorA.AsParallel()
                   .Select((value, index) => value * vectorB[index])
                   .ForAll(element => WrapperInt32(ref dot, element, (a, b) => a + b));
            Console.WriteLine($"C синхронизацией\tdot = {dot}");

            dot = 0;
            vectorA.AsParallel()
                   .Select((value, index) => value * vectorB[index])
                   .ForAll(element => dot += element);
            Console.WriteLine($"Без синхронизацией\tdot = {dot}");

            dot = vectorA.Select((value, index) => value * vectorB[index]).Sum();
            Console.WriteLine($"Последовательный метод\tdot = {dot}");
        }

        private static void Fifth(int variant)
        {
            Random rand = new Random();
            var input = Enumerable.Repeat(0, variant * 10000).Select(i => rand.Next(0, 100)).ToList();
            Console.WriteLine();
            AtomicInteger sum = new AtomicInteger();
            input.AsParallel().ForAll(element => sum.AddAndGet(element));
            Console.WriteLine($"Через AddAndGet\t\tsum = {sum}");
            sum.Set(0);

            input.AsParallel().ForAll(element =>
            {
                int oldValue;
                int newValue;
                do
                {
                    oldValue = sum.Get();
                    newValue = oldValue + element;
                } while (!sum.CompareAndSet(oldValue, newValue));
            });
            Console.WriteLine($"Через CompareAndSet\tsum = {sum}");
            int notSyncSum = 0;
            input.AsParallel().ForAll(element => notSyncSum += element);

            Console.WriteLine($"Без синхронизации\tsum = {notSyncSum}");
            Console.WriteLine($"Последовательный метод\tsum = {input.Sum()}");
            Console.WriteLine();

            var oldSum = sum.Get();
            Parallel.For(0, oldSum, i => sum.DecrimentAndGet());
            Parallel.For(0, oldSum, i => oldSum--);
            Console.WriteLine($"C синхронизацией\tsum = {sum}");
            Console.WriteLine($"Без синхронизации\tsum = {oldSum}");
        }
    }
}
