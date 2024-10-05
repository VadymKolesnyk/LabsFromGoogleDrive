using System.Collections.Immutable;

namespace Lab3
{
    class ListOfIndexes
    {
        internal ImmutableList<long> list = ImmutableList<long>.Empty;
        public ImmutableList<long> List { get => list; set => list = value; }
    }
}
