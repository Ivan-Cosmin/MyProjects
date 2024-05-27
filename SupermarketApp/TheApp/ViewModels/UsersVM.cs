using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using TheApp.Models.BusinessLogicLayer;
using TheApp.Models.EntityLayer;
using TheApp.ViewModels.Commands;

namespace TheApp.ViewModels
{
    internal class UsersVM : BasePropertyChanged
    {
        public UsersVM()
        {
            try
            {
                usersBLL = new UsersBLL();
                user = new User();
                usersBLL.GetUsersList();
                usersBLL.GetTypeUserList();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private User user;
        public User User
        {
            get { return user; }
            set
            {
                user = value;
                NotifyPropertyChanged("User");
            }
        }
        private User selectedUser;
        public User SelectedUser
        {
            get { return selectedUser; }
            set
            {
                selectedUser = value;
                User.Username = value.Username;
                User.Password = value.Password;
                User.Type = value.Type;
                NotifyPropertyChanged("SelectedUser");
                NotifyPropertyChanged("User");
            }
        }

        UsersBLL usersBLL;

        public ObservableCollection<User> UsersList
        {
            get => usersBLL.UsersList;
            set => usersBLL.UsersList = value;
        }
        public ObservableCollection<string> TypeUserList
        {
            get => usersBLL.TypeUserList;
            set => usersBLL.TypeUserList = value;
        }

        private ICommand addCommand;
        private ICommand modifyCommand;
        private ICommand deleteCommand;
        private ICommand activateCommand;
        public ICommand AddCommand
        {
            get
            {
                if (addCommand == null)
                {
                    addCommand = new RelayCommand(AddUser);
                }
                return addCommand;
            }
        }
        public ICommand ModifyCommand
        {
            get
            {
                if (modifyCommand == null)
                {
                    modifyCommand = new RelayCommand(ModifyUser);
                }
                return modifyCommand;
            }
        }
        public ICommand DeleteCommand
        {
            get
            {
                if (deleteCommand == null)
                {
                    deleteCommand = new RelayCommand(DeleteUser);
                }
                return deleteCommand;
            }
        }
        public ICommand ActivateCommand
        {
            get
            {
                if (activateCommand == null)
                {
                    activateCommand = new RelayCommand(ActivateUser);
                }
                return activateCommand;
            }
        }

        private void ActivateUser(object obj)
        {
            try
            {
                usersBLL.ActivateUser(SelectedUser);
                MessageBox.Show("User activated successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        public void AddUser(object parameter)
        {
            try
            {
                usersBLL.AddUser(User);
                MessageBox.Show("User added successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        public void ModifyUser(object parameter)
        {
            try
            {
                usersBLL.ModifyUser(SelectedUser, User);
                MessageBox.Show("User modified successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        public void DeleteUser(object parameter)
        {
            try
            {
                usersBLL.DeleteUser(SelectedUser);
                MessageBox.Show("User deleted successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void Clear()
        {
            User = new User();
        }

    }
}
