using Newtonsoft.Json;
using System;
using System.Collections.Concurrent;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;

namespace Lab5Server
{
    class Server
    {
        const int maxPlayers = 5; // максимальное кол-во игроков

        private readonly int port = 8005; // порт для приема входящих запросов
        private readonly IPAddress host = IPAddress.Parse("127.0.0.1"); // localhost
        private readonly Semaphore waiterForPlayers = new Semaphore(0, maxPlayers); // семафор для синхронизации игроков
        private readonly Semaphore waiterForServer = new Semaphore(0, maxPlayers);  // семафор для синхронизации сервера
        private readonly Question[] questions; // массив вопросов

        private readonly ConcurrentDictionary<int, Player> players = new ConcurrentDictionary<int, Player>(); // словарь игроков. Туда зонятся подключенные игроки
        public Server()
        {
            questions = JsonConvert.DeserializeObject<Question[]>(File.ReadAllText("questions.json")); // десериализируем вопросы из json
        }
        public Server(string host, int port) : this()
        {
            this.port = port;
            this.host = IPAddress.Parse(host);
        }

        public void Run() // метод запуска сервера. Сюда заходим главный поток
        {
            // создаем и подключам сокет на прослушку входящих подключений
            IPEndPoint ipPoint = new IPEndPoint(this.host, this.port); 
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            socket.Bind(ipPoint);
            socket.Listen(maxPlayers);

            Console.WriteLine($"[{DateTime.Now.ToLongTimeString(),8}] : Сервер работает. Напишите /start когда подключиться нужное количество игроков.");
            InputListenAsync(); // функция, которая в новом потоке ожидает ввода /start для запуска игры
            while (true)
            {
                HandleAsync(socket.Accept()); // ждем подключения и запускаем его обработку в новом потоке
            }
        }

        private Task InputListenAsync() => Task.Run(() =>
        {
            while (true) // в безконечном цикле ждет пока не будет введено /start
            {
                string command = Console.ReadLine();
                if (command.Trim().ToLower() == "/start")
                {
                    Start(); // когда будет введено запускает игру
                    return;
                }
            }
        });

        private Task HandleAsync(Socket socket) => Task.Run(() => // асинхонная обработка подключенния
        {
            try
            {
                Player player = new Player(socket, waiterForPlayers, waiterForServer); // создаем класс Player инкапсулирующий работу и игроком
                players[player.Id] = player; // добавляем игрока в словарь игроков
                player.Play(questions); // зачинаем игру с игроком 
                player.SendResults(); // отправляем результаты игры

                socket.Shutdown(SocketShutdown.Both);
            }
            catch (SocketException ex) // перехватываем исключения сокета и выводим их сообщения на экран
            {
                Console.WriteLine(ex.Message);
            }
            finally // в блоке finally закрываем соккет
            {
                socket.Close();
            }

        });

        private void Start()
        {
            Console.WriteLine($"[{DateTime.Now.ToLongTimeString(),8}] : Игра начинается.");
            for (int j = 0; j < questions.Length; j++) // по очереди для каждого вопроса 
            {
                Console.WriteLine($"[{DateTime.Now.ToLongTimeString(),8}] : Отправка вопроса № {j + 1}.");
                waiterForPlayers.Release(players.Count); // Разблокируем всех игроков для отправки вопроса
                for (int i = 0; i < players.Count; i++) // дожидаемся ответов на вопрос от всех игроков
                {
                    waiterForServer.WaitOne(); 
                }
            }
            Console.WriteLine($"[{DateTime.Now.ToLongTimeString(),8}] : Подсчет результатов.");
            CalculateResults(); // подсчет результатов
            waiterForPlayers.Release(players.Count); // Разблокируем всех игроков для отправки результатов

        }

        private void CalculateResults()
        {
            var resultArray = players.Select(kvp => new { Name = kvp.Value.Name, CorrectAnswers = CountCorrectAnswers(kvp.Value) })
                                     .OrderByDescending(player => player.CorrectAnswers)
                                     .Select((player, i) => $" {i + 1,2} : {player.Name,8}\t({player.CorrectAnswers} правильных ответа)")
                                     .ToArray(); // получаем результаты как строчки из имени игрока и кол-во правильных ответов, сортированные по убыванию
            Console.WriteLine($"[{DateTime.Now.ToLongTimeString(),8}] : Результаты :\n\t   " + string.Join("\n\t   ", resultArray));
            string result = string.Join("\n", resultArray); // склеиваем строчки
            foreach (var player in players)
            {
                player.Value.Results = result; // записываем строку результатов в соответствующее свойство у игрока.
            }
        }

        private int CountCorrectAnswers(Player player) // функция подсчета правильных ответов
        {
            return player.Answers.Where((answer , i) => answer == questions[i].CorrectAnswer).Count();
        }
    }
}
