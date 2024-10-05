    using OfficeOpenXml;
    using System;
    using System.Diagnostics;
    using System.IO;
    using System.Threading;

    namespace lab1
    {

        class MatrixSum
        {
            public int[,] A { get; }
            public int[,] B { get; }
            public int[,] Result { get; private set; }

            private readonly int zeroDimension;
            private readonly int firstDimension;

            public MatrixSum(int[,] a, int[,] b)
            {
                if (a is null)
                {
                    throw new ArgumentNullException(nameof(a));
                }

                if (b is null)
                {
                    throw new ArgumentNullException(nameof(b));
                }

                (zeroDimension, firstDimension) = (a.GetLength(0), a.GetLength(1));
                if ((zeroDimension != b.GetLength(0)) || (firstDimension != b.GetLength(1)))
                {
                    throw new ArgumentException($"{nameof(a)} and {nameof(b)} are incompatible to add");
                }
                (A, B) = (a, b);
                Result = new int[zeroDimension, firstDimension];
            }

            public void PartialSum(int startRow, int endRow)
            {
                if (startRow < 0 || endRow < 0 || startRow > zeroDimension || endRow > zeroDimension)
                {
                    throw new IndexOutOfRangeException($"Index out of range for {nameof(startRow)} or {nameof(endRow)}");
                }
                if (endRow <= startRow) 
                {
                    return;
                }
                for (int i = startRow ; i < endRow; i++)
                {
                    for (int j = 0; j < firstDimension; j++)
                    {
                        Result[i, j] = A[i, j] + B[i, j];
                    }
                }
            }

            public void FullSum() => PartialSum(0, zeroDimension);
        }
        class Program
        {
            static void Main(string[] args)
            {
                int maxThread = 10  ;
                int maxStepSize = 10;
                long[,] table = new long[maxStepSize, maxThread];

            for (int i = 1; i <= maxStepSize; i++)
            {
                int size = i * 100;
                int[,] a = RandomMatrix(size, 0, 10);
                int[,] b = RandomMatrix(size, 0, 10);
                for (int j = 0; j < 10; j++)
                {
                    var serialSum = new MatrixSum(a, b);
                    var clock = new Stopwatch();
                    clock.Start();
                    serialSum.FullSum();
                    clock.Stop();
                    table[i - 1, 0] += clock.ElapsedTicks;
                }
                table[i - 1, 0] /= 10;
                for (int numberThreads = 2; numberThreads <= maxThread; numberThreads++)
                {
                    for (int j = 0; j < 10; j++)
                    {
                        long tiks = SumInThreads(numberThreads, a, b);
                        table[i - 1, numberThreads - 1] += tiks;
                    }
                    table[i - 1, numberThreads - 1] /= 10;
                }
            }
            PrintMatrix(table);

                #region Вывод в ексель
                var package = new ExcelPackage();
                var sheet = package.Workbook.Worksheets.Add("table");
                for (int i = 0; i < maxStepSize; i++)
                {
                    for (int j = 0; j < maxThread; j++)
                    {
                        sheet.Cells[i + 3, j + 3].Value = table[i, j];
                    }
                }
                File.WriteAllBytes("table.xlsx", package.GetAsByteArray());
                #endregion



        }

            private static long SumInThreads(int numberThreads, int[,] a, int[,] b)
            {
                int size = a.GetLength(0);
                var parallelSum = new MatrixSum(a, b);

                var clock = new Stopwatch();
                clock.Start();
                double rowsPerThread = size / (double)numberThreads;
                Thread[] threads = new Thread[numberThreads];
                for (int i = 0; i < numberThreads; i++)
                {
                    int startRow = (int)(i * rowsPerThread);
                    int endRow = (int)((i + 1) * rowsPerThread);
                    threads[i] = new Thread(() => parallelSum.PartialSum(startRow, endRow));
                    threads[i].Start();
                }
                foreach (var thread in threads)
                {
                    thread.Join();
                }
                clock.Stop();
                return clock.ElapsedTicks;
            }


            #region I/O for matrixs
        private static void PrintMatrix(long[,] a)
        {
            Console.Write($"         ");
            for (int j = 0; j < a.GetLength(1); j++)
            {
                Console.Write($"+---------");
            }
            Console.WriteLine("+");
            Console.Write(@"  N \ T  ");
            for (int j = 0; j < a.GetLength(1); j++)
            {
                Console.Write($"| { (j + 1),-7} ");
            }
            Console.WriteLine("|");
            Console.Write($"+--------");
            for (int j = 0; j < a.GetLength(1); j++)
            {
                Console.Write($"+---------");
            }
            Console.WriteLine("+");
            for (int i = 0; i < a.GetLength(0); i++)
            {
                Console.Write($"| {(i + 1) * 100,-6} ");
                for (int j = 0; j < a.GetLength(1); j++)
                {
                    Console.Write($"| {a[i, j],-7} ");
                }
                Console.WriteLine("|");
            }
            Console.Write($"+--------");
            for (int j = 0; j < a.GetLength(1); j++)
            {
                Console.Write($"+---------");
            }
            Console.WriteLine("+");
        }

        private static int[,] RandomMatrix(int n, int leftBound, int rightBound)
        {
            var rand = new Random();
            int[,] result = new int[n, n];
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    result[i, j] = rand.Next(leftBound, rightBound);
                }
            }
            return result;
        }
        #endregion

        }
    }
