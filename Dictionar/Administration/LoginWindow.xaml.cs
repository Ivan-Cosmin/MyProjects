using System;
using System.Collections.Generic;
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
using System.IO;
using System.Xml.Serialization;
using Dictionar.Administration;



namespace Dictionar
{
    /// <summary>
    /// Interaction logic for LoginWindow.xaml
    /// </summary>
    public partial class LoginWindow : Window
    {
        public LoginWindow()
        {
            InitializeComponent();
        }
        private void TextBox_TextChanged(object sender, TextChangedEventArgs e)
        {
        }

        private void LogIn_Click(object sender, RoutedEventArgs e)
        {
            string username = usernameBox.Text;
            string password = passwordBox.Password;

            //file
            string[] accounts = File.ReadAllLines("accounts.txt");

            foreach (string account in accounts)
            {
                string[] parts = account.Split(':');
                if (parts.Length == 2)
                {
                    string storedUsername = parts[0];
                    string storedPassword = parts[1];

                    if (username == storedUsername && password == storedPassword)
                    {
                        AdminWindow adminWindow = new AdminWindow();
                        adminWindow.Show();
                        this.Close();
                    }
                    else
                    {
                        MessageBox.Show("Username or password are wrong!");
                    }
                }
            }
        }
    }
}
