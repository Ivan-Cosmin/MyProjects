using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TheApp.Models.DataAccessLayer;
using TheApp.Models.EntityLayer;

namespace TheApp.Models.BusinessLogicLayer
{
    internal class UsersBLL
    {
        public ObservableCollection<User> UsersList = new ObservableCollection<User>();
        public ObservableCollection<string> TypeUserList = new ObservableCollection<string>();
        UserDAL userDAL = new UserDAL();

        internal void AddUser(User user)
        {
            try
            {
                ValidateUser(user);
                ValidateUserExistence(user);
                userDAL.ValidateExistence(user);
                userDAL.AddUser(user);
                UsersList.Add(user);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void DeleteUser(User user)
        {
            try
            {
                ValidateUser(user);
                ValidateUserNonExistence(user);
                userDAL.DeleteUser(user);
                user.Deleted = true;
            }
            catch(Exception ex)
            {
                throw ex;
            }
        }

        internal void ModifyUser(User selectedUser, User user)
        {
            try
            {
                ValidateUser(user);
                ValidateUser(selectedUser);
                ValidateUserNonExistence(selectedUser);
                userDAL.ModifyUser(selectedUser,user);
                selectedUser.Username = user.Username;
                selectedUser.Password = user.Password;
                selectedUser.Type = user.Type;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        internal void GetUsersList()
        {
            UsersList = userDAL.GetUsersList();
        }
        internal void GetTypeUserList()
        {
            TypeUserList = userDAL.GetTypeUserList();
        }

        internal void ValidateUser(User user)
        {
            if (user == null)
            {
                throw new ArgumentNullException("user");
            }
            if (user.Username == null || user.Username == "")
            {
                throw new Exception("Username must be set!");
            }
            if (user.Password == null || user.Password == "")
            {
                throw new Exception("Password must be set!");
            }
            if (user.Type == null || user.Type == "")
            {
                throw new Exception("Type must be set!");
            }
            if(!TypeUserList.Contains(user.Type))
            {
                throw new Exception("Invalid Type!");
            }
        }

        internal void ValidateUserExistence(User user)
        {
            if (user == null)
            {
                throw new ArgumentNullException("user");
            }
            if (UsersList.Contains(user))
            {
                throw new Exception("User exist already!");
            }
        }

        internal void ValidateUserNonExistence(User user)
        {
            if (user == null)
            {
                throw new ArgumentNullException("user");
            }
            if (!UsersList.Contains(user))
            {
                throw new Exception("User does not exist!");
            }
        }

        internal void ActivateUser(User user)
        {
            try
            {
                ValidateUser(user);
                ValidateUserNonExistence(user);
                userDAL.ActivateUser(user);
                user.Deleted = false;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}
