using System.Windows;

namespace Dictionar
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            
        }
        private void Login_Click(object sender, RoutedEventArgs e)
        {
            LoginWindow login = new LoginWindow();
            login.Show();
        }

        private void Dictionary_Click(object sender, RoutedEventArgs e)
        {
            SearchPage search = new SearchPage();
            search.Show();
        }

        private void Gameplay_Click(object sender, RoutedEventArgs e)
        {
            Gamemode gamemode = new Gamemode();
            gamemode.Show();
        }
    }
}
