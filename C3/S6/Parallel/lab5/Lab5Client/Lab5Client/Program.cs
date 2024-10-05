using System;
using System.Net.Sockets;
using System.Net;
using System.Text;

namespace Lab5Client
{
    class Program
    {
        const int StopGameFlag = -1; // если мы получим такой размер сообщения, значит вопросы закончились
        static readonly int port = 8005; // порт сервера
        static readonly string host = "127.0.0.1"; // адрес сервера
        static readonly Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp); // сокет соединения
        static void Main(string[] args)
        {
            Console.Write("Введите имя: "); // Вводим имя игрока
            string name = Console.ReadLine();
            try
            {

                Register(name); // подключение к серверу и регистрация в игре

                Play(); // сам процес игры

                GetResults(); // получение результатов

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
            Console.Read();
        }

        private static void Register(string name)
        {
            IPEndPoint ipPoint = new IPEndPoint(IPAddress.Parse(host), port); // создаем IpPoint
            socket.Connect(ipPoint); // подключаемся к серверу

            byte[] data = Encoding.Unicode.GetBytes(name); // сериализацируем имя в байты
            socket.Send(BitConverter.GetBytes(data.Length)); // отправляем вначале размер сообщения 
            socket.Send(data); // а потом и само сообщение

            byte[] sizeBytes = new byte[sizeof(int)]; // резервируем место под int - размер сообщения 
            socket.Receive(sizeBytes, sizeof(int), SocketFlags.None); // получаем вначале размер сообщения 
            int size = BitConverter.ToInt32(sizeBytes); // десериализируем int
            data = new byte[size]; // резервируем место под само сообщение
            socket.Receive(data); // получаем сообщение
            string message = Encoding.Unicode.GetString(data, 0, size); // десериализируем сообщение
            Console.WriteLine(message);
        }
        private static void Play()
        {
            while (true) // игра происходит в безконечном цикле, с выходом по break
            {
                byte[] sizeBytes = new byte[sizeof(int)]; // резервируем место под int - размер сообщения 
                socket.Receive(sizeBytes, sizeof(int), SocketFlags.None); // получаем вначале размер сообщения
                int size = BitConverter.ToInt32(sizeBytes); // десериализируем int
                if (size == StopGameFlag) // проверяем если размер сообщения StopGameFlag = -1, то это значит, что вопросов больше нет
                {
                    break; // тогда выходим из цикла
                }
                byte[] data = new byte[size]; // резервируем место под само сообщение
                socket.Receive(data); // получаем сообщение
                string message = Encoding.Unicode.GetString(data, 0, size); // десериализируем сообщение
                Console.WriteLine("Вопрос:\n" + message);

                Console.Write("Введите ответ (число 1, 2 или 3) : "); // вводим ответ
                int answer; 
                while (!int.TryParse(Console.ReadLine(), out answer) || answer <= -1 || answer >= 4) // считываем ответ, пока не будет введен правильный
                {
                }
                socket.Send(BitConverter.GetBytes(answer)); // отправляем ответ
            }
        }

        private static void GetResults()
        {
            byte[] sizeBytes = new byte[sizeof(int)]; // резервируем место под само сообщение
            socket.Receive(sizeBytes, sizeof(int), SocketFlags.None); // получаем вначале размер сообщения
            int size = BitConverter.ToInt32(sizeBytes); // десериализируем int
            byte[] data = new byte[size]; // резервируем место под само сообщение
            socket.Receive(data); // получаем сообщение
            string message = Encoding.Unicode.GetString(data, 0, size); // десериализируем сообщение
            Console.WriteLine("Результаты:\n" + message);
        }
    }
}
