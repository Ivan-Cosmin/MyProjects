using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Security;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using TheApp.Models.BusinessLogicLayer;
using TheApp.Models.EntityLayer;
using TheApp.ViewModels.Commands;

namespace TheApp.ViewModels
{
    internal class LoginVM : BasePropertyChanged
    {
        public LoginVM() 
        { 
            TypeUsers = new ObservableCollection<string>
            {
                "Admin",
                "Cashier"
            };

            User = new User();
        }

        LoginBLL loginBLL = new LoginBLL();

        public User User { get; set; }
        public ObservableCollection<string> TypeUsers { get; set; }

        private ICommand loginCommand;
        public ICommand LoginCommand
        {
            get
            {
                if (loginCommand == null)
                {
                    loginCommand = new RelayCommand(Login);
                }
                return loginCommand;
            }
        }

        public void Login(object parameter)
        {
            try 
            {
                loginBLL.ValidateLogin(User);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
