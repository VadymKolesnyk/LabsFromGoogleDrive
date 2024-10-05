using System.Threading;

namespace Lab3
{
    class AtomicInteger
    {
        private int value;

        public AtomicInteger(int value) => this.value = value;

        public AtomicInteger() { }

        public int Get() => value;

        public void Set(int newValue) => Interlocked.Exchange(ref value, newValue);

        public bool CompareAndSet(int expect, int update) => Interlocked.CompareExchange(ref value, update, expect) == expect;

        public int DecrimentAndGet() => Interlocked.Decrement(ref value);

        public int GetAndIncrement() => Interlocked.Increment(ref value) - 1;

        public int GetAndDecriment() => Interlocked.Decrement(ref value) + 1;

        public int IncrementAndGet() => Interlocked.Increment(ref value);

        public int AddAndGet(int delta) => Interlocked.Add(ref value, delta);

        public int GetAndAdd(int delta) => Interlocked.Add(ref value, delta) - delta;

        public override string ToString() => value.ToString();
    }
}
