using Neo4jClient;
using System;
using System.Collections.Generic;
using System.Linq;
namespace Lab3
{
    class Person
    {
        public string Name { get; set; }
        public override string ToString()
        {
            return $"Name : {Name};";
        }
    }
    class Film
    {
        public string Name { get; set; }
        public int Year { get; set; }
        public override string ToString()
        {
            return $"Name : {Name}\tYear: {Year};";
        }
    }
    class Program
    {
        static void AddPersonNode(IGraphClient client, string name)
        {
            client.Cypher
                .Create($"(p:Person {{Name: '{name}'}})")
                .ExecuteWithoutResults();
        }
        static void AddFilmNode(IGraphClient client, string name, int year)
        {
            client.Cypher
                .Create($"(f:Film {{Name: '{name}', Year: '{year}'}})")
                .ExecuteWithoutResults();
        }
        static void AddPayedInRelation(IGraphClient client, string personName, string filmName)
        {
            var query = client.Cypher
                .Match($"(:Person {{Name: '{personName}'}})-[r:PlayedIn]->(:Film {{Name: '{filmName}'}})")
                .Return(r => r.Count())
                .Results;
            if (query.First() == 0)
            {
                client.Cypher
                    .Match($"(p:Person {{Name: '{personName}'}})", $"(f:Film {{Name: '{filmName}'}})")
                    .Create("(p)-[:PlayedIn]->(f)")
                    .ExecuteWithoutResults();
            }

        }
        static IEnumerable<Person> GetCommonActors(IGraphClient client, string film1, string film2)
        {
            return client.Cypher
                .Match($"(:Film {{Name: '{film1}'}})<--(p:Person)-->(:Film {{Name: '{film2}'}})")
                .Return<Person>("p")
                .Results;
        }
        static IEnumerable<Film> GetCommonFilms(IGraphClient client, string actor1, string actor2)
        {
            return client.Cypher
                .Match($"(:Person {{Name: '{actor1}'}})-->(f:Film)<--(:Person {{Name: '{actor2}'}})")
                .Return<Film>("f")
                .Results;
        }
        static void Main(string[] args)
        {
            var client = new GraphClient(new Uri("http://localhost:7474/db/data"), "vadim", "vadim");
            client.Connect();
            bool z = true;
            if (z)
            {
                client.Cypher
                    .Match("(n)") // MATCH (n)
                    .DetachDelete("n")
                    .ExecuteWithoutResults();

                for (int i = 0; i < 7; i++)
                {
                    AddPersonNode(client, $"Actor {i + 1}");
                }
                for (int i = 0; i < 5; i++)
                {
                    AddFilmNode(client, $"Film {i + 1}", 1990 + i);
                }
            }
            var actors = client.Cypher
                .Match("(p:Person)")
                .Return<Person>("p")
                .Results.OrderBy(p => p.Name).ToArray();
            var films = client.Cypher
                .Match("(f:Film)")
                .Return<Film>("f")
                .Results.OrderBy(f => f.Name).ToArray();
            if (z)
            { 
                Random random = new Random();
                foreach (Person actor in actors)
                {
                    int count = random.Next(2, 4);
                    for (int i = 0; i < count; i++)
                    {
                        AddPayedInRelation(client, actor.Name, films[random.Next(films.Count())].Name);
                    }

                }
            }
           
            for (int i = 0; i < films.Length; i++)
            {
                for (int j = i + 1; j < films.Length; j++)
                {
                    var commonActors = GetCommonActors(client, films[i].Name, films[j].Name);
                    Console.WriteLine($"{films[i].Name} and {films[j].Name} (Count = {commonActors.Count()}):");
                    foreach (Person actor in commonActors)
                    {
                        Console.WriteLine("\t" + actor);
                    }
                }
            }
            Console.WriteLine("---------------------------------------");
            for (int i = 0; i < actors.Length; i++)
            {
                for (int j = i + 1; j < actors.Length; j++)
                {
                    var commonFilms = GetCommonFilms(client, actors[i].Name, actors[j].Name);
                    Console.WriteLine($"{actors[i].Name} and {actors[j].Name} (Count = {commonFilms.Count()}):");
                    foreach (Film film in commonFilms)
                    {
                        Console.WriteLine("\t" + film);
                    }
                }
            }
            var q = client.Cypher
                .Match("p = shortestPath((start:Person) - [*] - (end:Person))")
                .Where("id(start) > id(end)")
                .Return((start, end, p) => new { Start = start.As<Person>(), End = end.As<Person>(), Length = p.Length()})
                .Results.OrderBy(r => -r.Length); //match p = shortestPath((start:Person) - [*] - (end:Person)) where id(start)>id(end) return start as Start, end as End, length(p)-1 as Between order by -length(p)
            Console.WriteLine("+---------------------+---------------------+-----------+");
            Console.WriteLine("|        Start        |         End         |  Between  |");
            Console.WriteLine("+---------------------+---------------------+-----------+");
            foreach (var item in q)
            {
                Console.Write($"| {item.Start,-19} ");
                Console.Write($"| {item.End,-19} ");
                Console.WriteLine($"| {item.Length - 1,9} |");
            }
            Console.WriteLine("+---------------------+---------------------+-----------+");
        }
    }
}
