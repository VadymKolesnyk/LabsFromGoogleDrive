using StackExchange.Redis;
using System;
using System.IO;

using StreamWriter sw = new StreamWriter(Path.GetFullPath("../../../output.txt")); 
ConnectionMultiplexer redis = ConnectionMultiplexer.Connect("localhost:6379");
redis.GetSubscriber().Subscribe("*", (channel, message) =>
{
    string output = $"{"[" + (DateTime.Now) + "]",-30} {"<" + channel + ">",-20} \"{message}\"";
    sw.WriteLine(output);
    Console.WriteLine(output);
});
Console.ReadKey();
sw.Close();