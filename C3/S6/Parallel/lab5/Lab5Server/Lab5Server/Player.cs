using System;
using System.Net.Sockets;
using System.Text;
using System.Threading;

namespace Lab5Server
{
    class Player
    {
        const int StopGameFlag = -1; // если вопросы закончились, то мы это сообщаем клиентам спомощью отправки -1
        private static int count = 0; // статическое поле для присваивания id игрокам
        public int Id { get; } 
        public string Name { get; private set; } 

        public string Results { get; set; } // строка для результатов
        public int[] Answers { get; private set; } // массив ответов

        private readonly Socket socket; // сокет соединения 
        private readonly Semaphore waiterForPlayers; // семафор для синхронизации игроков
        private readonly Semaphore waiterForServer; // семафор для синхронизации сервера

        public Player(Socket socket, Semaphore waiterForPlayers, Semaphore waiterForServer)
        {
            Id = Interlocked.Increment(ref count); // атомантый инкремент счетчика и результата присваивание в id
            this.socket = socket;
            this.waiterForPlayers = waiterForPlayers;
            this.waiterForServer = waiterForServer;
            Register(); // функция регистрации игрока
        }

        private void Register()
        {
            byte[] sizeBytes = new byte[sizeof(int)]; // резервируем место под int - размер сообщения 
            socket.Receive(sizeBytes, sizeof(int), SocketFlags.None); // получаем вначале размер сообщения 
            int size = BitConverter.ToInt32(sizeBytes); // десериализируем int
            byte[] data = new byte[size]; // резервируем место под само сообщение
            socket.Receive(data); // получаем сообщение
            string name = Encoding.Unicode.GetString(data, 0, size); // десериализируем сообщение
            Name = name; // записываем имя
            Console.WriteLine($"[{DateTime.Now.ToLongTimeString(),8}] : Подключился {Name} , его id = {Id}");

            string message = $"Приветствую, {Name}, твой номер {Id}"; // сообщение ответа
            data = Encoding.Unicode.GetBytes(message); // сериализацируем сообщение в байты
            socket.Send(BitConverter.GetBytes(data.Length)); // отправляем вначале размер сообщения 
            socket.Send(data); // а потом и само сообщение
        }

        public void Play(Question[] questions) // функция в которой и просходит игра
        {
            Answers = new int[questions.Length]; // инициализация массива ответов
            for (int i = 0; i < questions.Length; i++) // по очереди отправляем вопросы
            {
                waiterForPlayers.WaitOne(); // дожидаемся разрешения сервера
                SendQuestion(questions[i]); // отправка вопроса
                ReceiveAnswer(i); // получение ответа
                waiterForServer.Release(); // сообщаем, что получем ответ
            }
        }

        private void SendQuestion(Question question)
        {
            // склениваем вопросы и ответы в отду строчку
            StringBuilder questionWithAnswers = new StringBuilder($"{question.QuestionText} :\n");
            foreach (var answer in question.Answers)
            {
                questionWithAnswers.Append($"\t{answer}\n");
            }

            byte[] data = Encoding.Unicode.GetBytes(questionWithAnswers.ToString()); // сериализацируем сообщение в байты
            socket.Send(BitConverter.GetBytes(data.Length)); // отправляем вначале размер сообщения 
            socket.Send(data); // а потом и само сообщение
        }

        private void ReceiveAnswer(int questionNumber)
        {
            byte[] answerBytes = new byte[sizeof(int)];  // резервируем место под int - размер сообщения 
            socket.Receive(answerBytes, sizeof(int), SocketFlags.None); // получаем вначале размер сообщения 
            int answer = BitConverter.ToInt32(answerBytes); // десериализируем int
            Answers[questionNumber] = answer; // запись ответа в массив
            Console.WriteLine($"[{DateTime.Now.ToLongTimeString(),8}] : Игрок {Name} (id = {Id}) ответил на вопрос. Его ответ: {answer}");
        }

        internal void SendResults() // отправка результатов клиенту
        {
            waiterForPlayers.WaitOne(); // дожидаемся разрешения сервера
            socket.Send(BitConverter.GetBytes(StopGameFlag)); // отпровляем код того, что вопросов больше нет
            byte[] data = Encoding.Unicode.GetBytes(Results); // сериализацируем сообщение в байты
            socket.Send(BitConverter.GetBytes(data.Length)); // отправляем вначале размер сообщения 
            socket.Send(data); // а потом и само сообщение
        }

    }
}
