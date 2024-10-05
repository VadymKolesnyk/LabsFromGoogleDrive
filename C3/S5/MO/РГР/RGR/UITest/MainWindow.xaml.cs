using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace UITest
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            FunctionPage.Visibility = Visibility.Collapsed;
            MainPage.Visibility = Visibility.Visible;
            GamePage.Visibility = Visibility.Collapsed;
            GamePlayersGrid.ItemsSource = gameModel.Players;

            gameModel.Players.AddRange(InitializePlayers());



        }

        #region FunctionPage
        FunctionModel functionModel = new FunctionModel();
        private void FunctionButton_Click(object sender, RoutedEventArgs e)
        {
            FunctionPage.Visibility = Visibility.Visible;
            MainPage.Visibility = Visibility.Collapsed;
        }
        private void FunctionBack_Click(object sender, RoutedEventArgs e)
        {
            FunctionPage.Visibility = Visibility.Collapsed;
            MainPage.Visibility = Visibility.Visible;
        }
        private void FunctionStart_Click(object sender, RoutedEventArgs e)
        {
            if (double.TryParse(StartPointBox.Text.Replace('.', ','), out double startPoint) && 
                double.TryParse(StartTemperatureBox.Text.Replace('.', ','), out double startTemperature) &&
                int.TryParse(AmountOfIterationsBox.Text, out int amountOfIterations))
            {
                if (Math.Abs(startPoint) > 10)
                    MessageBox.Show(this, "Стартовая точка выходит за диапазон (-10; 10)","Ошибка входных данных");
                if (startTemperature < 0)
                    MessageBox.Show(this, "Начальная температура меньше нуля", "Ошибка входных данных");
                if (amountOfIterations < 0)
                    MessageBox.Show(this, "Количество итераций меньше нуля", "Ошибка входных данных");
                functionModel.StartPoint = startPoint;
                functionModel.StartTemperature = startTemperature;
                functionModel.AmountOfIterations = amountOfIterations;
                FunctionResult.Text = "Результат: " + functionModel.Start();
            }
            else
            {
                MessageBox.Show(this, "Некоректный формат входных данных", "Ошибка входных данных");
            }

        }
        #endregion

        #region GamePage
        GameModel gameModel = new GameModel();
        private void GameButton_Click(object sender, RoutedEventArgs e)
        {
            GamePage.Visibility = Visibility.Visible;
            MainPage.Visibility = Visibility.Collapsed;
        }
        private void GameBack_Click(object sender, RoutedEventArgs e)
        {
            GamePage.Visibility = Visibility.Collapsed;
            MainPage.Visibility = Visibility.Visible;
        }

        GridViewColumnHeader lastHeaderClicked = null;
        ListSortDirection lastDirection = ListSortDirection.Ascending;
        void GameComandHeader_Click(object sender, RoutedEventArgs e)
        {
            GridViewColumnHeader headerClicked = e.OriginalSource as GridViewColumnHeader;
            ListView comand = sender as ListView;
            if (comand.ItemsSource == null)
            {
                return;
            }
            ListSortDirection direction;
            if (headerClicked != lastHeaderClicked)
            {
                direction = ListSortDirection.Ascending;
            }
            else
            {
                if (lastDirection == ListSortDirection.Ascending)
                {
                    direction = ListSortDirection.Descending;
                }
                else
                {
                    direction = ListSortDirection.Ascending;
                }
            }
            ICollectionView dataView = CollectionViewSource.GetDefaultView(comand.ItemsSource);
            dataView.SortDescriptions.Clear();
            SortDescription sd = new SortDescription(headerClicked.Column.Header as string, direction);
            dataView.SortDescriptions.Add(sd);
            dataView.Refresh();
            lastHeaderClicked = headerClicked;
            lastDirection = direction;
        }
        private void GameStart_Click(object sender, RoutedEventArgs e)
        {
            Game game = gameModel.Start();
            GameComand1.ItemsSource = game.Comand1;
            GameComand1Level.Text = $"Level: {game.Comand1.Sum(p => p.Level)}";
            GameComand1Speed.Text = $"Speed: {game.Comand1.Sum(p => p.Speed)}";
            GameComand1Strength.Text = $"Strength: {game.Comand1.Sum(p => p.Strength)}";

            GameComand2.ItemsSource = game.Comand2;
            GameComand2Level.Text = $"Level: {game.Comand2.Sum(p => p.Level)}";
            GameComand2Speed.Text = $"Speed: {game.Comand2.Sum(p => p.Speed)}";
            GameComand2Strength.Text = $"Strength: {game.Comand2.Sum(p => p.Strength)}";
        }
        #endregion




        private static List<Player> InitializePlayers()
        {
            return new List<Player>
            {
                new Player
                {
                    Name = "Player # 1",
                    Level = 1,
                    Speed = 2,
                    Strength = 3,
                    Class = CharacterСlass.Cleric
                },
                new Player
                {
                    Name = "Player # 2",
                    Level = 1,
                    Speed = 3,
                    Strength = 1,
                    Class = CharacterСlass.Fighter
                },
                new Player
                {
                    Name = "Player # 3",
                    Level = 2,
                    Speed = 5,
                    Strength = 1,
                    Class = CharacterСlass.Fighter
                },
                new Player
                {
                    Name = "Player # 4",
                    Level = 3,
                    Speed = 1,
                    Strength = 4,
                    Class = CharacterСlass.Magic
                },
                new Player
                {
                    Name = "Player # 5",
                    Level = 3,
                    Speed = 7,
                    Strength = 1,
                    Class = CharacterСlass.Magic
                },
                new Player
                {
                    Name = "Player # 6",
                    Level = 4,
                    Speed = 2,
                    Strength = 3,
                    Class = CharacterСlass.Ranger
                },
                new Player
                {
                    Name = "Player # 7",
                    Level = 4,
                    Speed = 3,
                    Strength = 4,
                    Class = CharacterСlass.Rogue
                },
                new Player
                {
                    Name = "Player # 8",
                    Level = 7,
                    Speed = 4,
                    Strength = 1,
                    Class = CharacterСlass.Rogue
                },
                new Player
                {
                    Name = "Player # 9",
                    Level = 7,
                    Speed = 5,
                    Strength = 3,
                    Class = CharacterСlass.Rogue
                },
                new Player
                {
                    Name = "Player # 10",
                    Level = 4,
                    Speed = 2,
                    Strength = 4,
                    Class = CharacterСlass.Cleric
                },
            };
        }


    }
}
