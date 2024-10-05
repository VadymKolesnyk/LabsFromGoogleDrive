using System;
using StackExchange.Redis;

void PrintCounts(IDatabase db)
{
    Console.WriteLine("------------");
    for (int i = 0; i < 5; i++)
    {

        Console.WriteLine($"count{i} = " + db.StringGet($"count{i}"));

    }
    Console.WriteLine("------------");
}

ConnectionMultiplexer redis = ConnectionMultiplexer.Connect("localhost:6379,allowAdmin=true");
redis.GetServer("localhost:6379").FlushAllDatabases();
var db = redis.GetDatabase(0);

PrintCounts(db);

var tran = db.CreateTransaction();
for (int i = 0; i < 5; i++)
{
    tran.StringSetAsync($"count{i}", i);
}
tran.Execute();
PrintCounts(db);
tran = db.CreateTransaction();
for (int i = 0; i < 5; i++)
{
    tran.StringIncrementAsync($"count{i}");
}
PrintCounts(db);
tran.Execute();
PrintCounts(db);