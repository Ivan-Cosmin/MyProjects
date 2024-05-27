using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using TheApp.Models.DataAccessLayer;
using TheApp.Models.EntityLayer;
using TheApp.Views;

namespace TheApp.Models.BusinessLogicLayer
{
    internal class LoginBLL
    {
        LoginDAL loginDAL = new LoginDAL();
        public void ValidateLogin(User user)
        {
            if (user.Username == null)
            {
               throw new Exception ("Please enter username");
            }

            if(user.Password == null)
            {
                throw new Exception("Please enter password");
            }

            string userType = loginDAL.ValidateLogin(user);

            if(userType == "Admin")
            {
                OpenAdminWindow();
            }
            else if(userType == "Cashier")
            {
                
               OpenCashierWindow();
               try
                {
                    WriteStringToFile(user.Username, "CashierLog.txt");
                }
                catch (Exception ex)
                {
                    throw new Exception("Error writing to file", ex);
                }
            }
            else
            {
                throw new Exception("Invalid username or password");
            }
        }

        private void OpenCashierWindow()
        {
            var secondWindow = new CashierWindow();
            Application.Current.MainWindow.Hide();
            secondWindow.Show();
            secondWindow.Closed += (s, e) =>
            {
                Application.Current.MainWindow.Show();
            };
        }

        private void OpenAdminWindow()
        {
            var secondWindow = new AdminWindow();
            Application.Current.MainWindow.Hide();
            secondWindow.Show();
            secondWindow.Closed += (s, e) =>
            {
                Application.Current.MainWindow.Show();
            };
        }

        private void WriteStringToFile(string content, string filePath)
        {
            try
            {
                using (StreamWriter writer = new StreamWriter(filePath, append: true))
                {
                    writer.WriteLine(content);
                }
            }
            catch (Exception ex)
            {
                throw new Exception("Error writing to file", ex);
            }
        }
    }
}
