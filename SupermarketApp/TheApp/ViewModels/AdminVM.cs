using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using TheApp.ViewModels.Commands;
using TheApp.Views;


namespace TheApp.ViewModels
{
    internal class AdminVM
    {
        private ICommand usersCommand;
        private ICommand categoriesCommand;
        private ICommand productsCommand;
        private ICommand manufacturersCommand;
        private ICommand stocksCommand;
        private ICommand searchByManufacturersCommand;
        private ICommand receiptsCommand;

        public ICommand ReceiptsCommand
        {
            get
            {
                if (receiptsCommand == null)
                {
                    receiptsCommand = new RelayCommand(OpenReceipts);
                }
                return receiptsCommand;
            }
        }
        public ICommand SearchByManufacturersCommand
        {
            get
            {
                if (searchByManufacturersCommand == null)
                {
                    searchByManufacturersCommand = new RelayCommand(SearchByManufacturers);
                }
                return searchByManufacturersCommand;
            }
        }
        public ICommand UsersCommand
        {
            get
            {
                if (usersCommand == null)
                {
                    usersCommand = new RelayCommand(OpenUsers);
                }
                return usersCommand;
            }
        }
        public ICommand CategoriesCommand
        {
            get
            {
                if (categoriesCommand == null)
                {
                    categoriesCommand = new RelayCommand(OpenCategories);
                }
                return categoriesCommand;
            }
        }
        public ICommand ProductsCommand
        {
            get
            {
                if (productsCommand == null)
                {
                    productsCommand = new RelayCommand(OpenProducts);
                }
                return productsCommand;
            }
        }
        public ICommand ManufacturersCommand
        {
            get
            {
                if (manufacturersCommand == null)
                {
                    manufacturersCommand = new RelayCommand(OpenManufacturers);
                }
                return manufacturersCommand;
            }
        }
        public ICommand StocksCommand
        {
            get
            {
                if (stocksCommand == null)
                {
                    stocksCommand = new RelayCommand(OpenStocks);
                }
                return stocksCommand;
            }
        }

        private void OpenUsers(object obj)
        {
            var adminWindow = Application.Current.Windows.OfType<AdminWindow>().FirstOrDefault();
            if (adminWindow != null)
            {
                var usersWindow = new UsersWindow();
                adminWindow.Hide();
                usersWindow.Show();
                usersWindow.Closed += (s, e) =>
                {
                    adminWindow.Show();
                };
            }
            else
            {
                MessageBox.Show("AdminWindow not found.");
            }
        }
        private void OpenCategories(object obj)
        {
            var adminWindow = Application.Current.Windows.OfType<AdminWindow>().FirstOrDefault();
            if (adminWindow != null)
            {
                var categoriesWindow = new CategoriesWindow();
                adminWindow.Hide();
                categoriesWindow.Show();
                categoriesWindow.Closed += (s, e) =>
                {
                    adminWindow.Show();
                };
            }
            else
            {
                MessageBox.Show("AdminWindow not found.");
            }
        }

        private void OpenProducts(object obj)
        {
            var adminWindow = Application.Current.Windows.OfType<AdminWindow>().FirstOrDefault();
            if (adminWindow != null)
            {
                var productsWindow = new ProductsWindow();
                adminWindow.Hide();
                productsWindow.Show();
                productsWindow.Closed += (s, e) =>
                {
                    adminWindow.Show();
                };
            }
            else
            {
                MessageBox.Show("AdminWindow not found.");
            }
        }

        private void OpenManufacturers(object obj)
        {
            var adminWindow = Application.Current.Windows.OfType<AdminWindow>().FirstOrDefault();
            if (adminWindow != null)
            {
                var manufacturersWindow = new ManufacturersWindow();
                adminWindow.Hide();
                manufacturersWindow.Show();
                manufacturersWindow.Closed += (s, e) =>
                {
                    adminWindow.Show();
                };
            }
            else
            {
                MessageBox.Show("AdminWindow not found.");
            }
        }

        private void OpenStocks(object obj)
        {
            var adminWindow = Application.Current.Windows.OfType<AdminWindow>().FirstOrDefault();
            if (adminWindow != null)
            {
                var stocksWindow = new ProductStockWindow();
                adminWindow.Hide();
                stocksWindow.Show();
                stocksWindow.Closed += (s, e) =>
                {
                    adminWindow.Show();
                };
            }
            else
            {
                MessageBox.Show("AdminWindow not found.");
            }
        }

        private void SearchByManufacturers(object obj)
        {
            var adminWindow = Application.Current.Windows.OfType<AdminWindow>().FirstOrDefault();
            if (adminWindow != null)
            {
                var searchByManufacturersWindow = new SearchByManufacurerWindow();
                adminWindow.Hide();
                searchByManufacturersWindow.Show();
                searchByManufacturersWindow.Closed += (s, e) =>
                {
                    adminWindow.Show();
                };
            }
            else
            {
                MessageBox.Show("AdminWindow not found.");
            }
        }

        private void OpenReceipts(object obj)
        {
            //var adminWindow = Application.Current.Windows.OfType<AdminWindow>().FirstOrDefault();
            //if (adminWindow != null)
            //{
            //    var receiptsWindow = new ReceiptsWindow();
            //    adminWindow.Hide();
            //    receiptsWindow.Show();
            //    receiptsWindow.Closed += (s, e) =>
            //    {
            //        adminWindow.Show();
            //    };
            //}
            //else
            //{
            //    MessageBox.Show("AdminWindow not found.");
            //}
            throw new NotImplementedException();
        }

    }
}
