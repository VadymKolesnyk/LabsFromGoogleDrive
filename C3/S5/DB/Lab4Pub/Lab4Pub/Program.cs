using StackExchange.Redis;
using System;
using System.Linq;

ConnectionMultiplexer redis = ConnectionMultiplexer.Connect("localhost:6379");
Console.WriteLine("{имя канала} {текст сообщения}");
while (true)
{
    string readed = Console.ReadLine();
    string[] input = readed.Split(' ');
    if (input.Length >= 2)
    {
        redis.GetSubscriber().Publish(input.First(), readed[(input.First().Length + 1)..]);
    }
} 