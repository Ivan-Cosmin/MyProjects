using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using TheApp.Models.BusinessLogicLayer;
using TheApp.Models.EntityLayer;
using TheApp.ViewModels.Commands;
using TheApp.Views;

namespace TheApp.ViewModels
{
    internal class CashierVM : BasePropertyChanged
    {
        public CashierVM()
        {
            cashierBLL = new CashierBLL();
            Stock = new ProductStock();
            Receipt = new Receipt();
            StockToAddInReceipt = new ProductStock();
        }

        CashierBLL cashierBLL;
        public ObservableCollection<ProductOnReceipt> ProductsReceiptList
        {
            get => cashierBLL.ProductsReceiptList;
            set => cashierBLL.ProductsReceiptList = value;
        }
        public ObservableCollection<ProductStock> StocksList
        {
            get => cashierBLL.StocksList;
            set => cashierBLL.StocksList = value;
        }

        private DateTime _date;
        public DateTime Date
        {
            get => _date;
            set
            {
                _date = value;
                NotifyPropertyChanged("Date");
            }
        }

        private int _quantity;
        private ProductStock _stock;
        private ProductStock _stockToAddInReceipt;
        private Receipt _receipt;
        private ProductOnReceipt _productOnReceipt;
        public int Quantity
        {
            get => _quantity;
            set
            {
                _quantity = value;
                NotifyPropertyChanged("Quantity");
            }
        }
        public ProductStock Stock
        {
            get => _stock;
            set
            {
                _stock = value;
                NotifyPropertyChanged("Stock");
            }
        }
        public ProductStock StockToAddInReceipt
        {
            get => _stockToAddInReceipt;
            set
            {
                _stockToAddInReceipt = value;
                NotifyPropertyChanged("StockToAddInReceipt");
            }
        }
        public Receipt Receipt
        {
            get => _receipt;
            set
            {
                _receipt = value;
                NotifyPropertyChanged("Receipt");
            }
        }
        public ProductOnReceipt ProductOnReceipt
        {
            get => _productOnReceipt;
            set
            {
                _productOnReceipt = value;
                NotifyPropertyChanged("ProductOnReceipt");
            }
        }

        private ICommand addCommand;
        private ICommand deleteCommand;
        private ICommand searchCommand;
        private ICommand addProductCommand;
        private ICommand removeCommand;
        public ICommand AddCommand
        {
            get
            {
                if (addCommand == null)
                {
                    addCommand = new RelayCommand(AddReceipt);
                }
                return addCommand;
            }
        }
        public ICommand DeleteCommand
        {
            get
            {
                if (deleteCommand == null)
                {
                    deleteCommand = new RelayCommand(DeleteReceipt);
                }
                return deleteCommand;
            }
        }
        public ICommand SearchCommand
        {
            get
            {
                if (searchCommand == null)
                {
                    searchCommand = new RelayCommand(SearchProduct);
                }
                return searchCommand;
            }
        }
        public ICommand AddProductCommand
        {
            get
            {
                if (addProductCommand == null)
                {
                    addProductCommand = new RelayCommand(AddProductToReceipt);
                }
                return addProductCommand;
            }
        }
        public ICommand RemoveCommand
        {
            get
            {
                if (removeCommand == null)
                {
                    removeCommand = new RelayCommand(RemoveProductFromReceipt);
                }
                return removeCommand;
            }
        }


        private void AddProductToReceipt(object obj)
        {
            try
            {
                if (StockToAddInReceipt.Product.Barcode == null)
                    throw new Exception("Please select a product to add to the receipt");

                int quantity = GetQuantity();  

                cashierBLL.AddProductToReceipt(StockToAddInReceipt, quantity);
                MessageBox.Show("Product added to receipt successfully");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private int GetQuantity()
        {
            NumericWindow numericWindow = new NumericWindow();
            NumericVM numericVM = new NumericVM
            {
                CloseAction = () => numericWindow.Close()
            };
            numericWindow.DataContext = numericVM;
            numericWindow.ShowDialog();

            return numericVM.InputNumber.Value;
        }

        private void AddReceipt(object obj)
        {
            try
            {
                Receipt.Date = DateTime.Now;
                cashierBLL.AddReceipt(Receipt);
                MessageBox.Show("Receipt added successfully");
                ClearAll();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void DeleteReceipt(object obj)
        {
            try
            {
                cashierBLL.DeleteReceipt();
                MessageBox.Show("Receipt deleted successfully");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void SearchProduct(object obj)
        {
            try
            {
                Stock.ExpiryDate = Date;
                cashierBLL.SearchProduct(Stock);
                StocksList = cashierBLL.StocksList;
                NotifyPropertyChanged("StocksList");
                ClearSlots();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void RemoveProductFromReceipt(object obj)
        {
            try
            {
                cashierBLL.RemoveProductFromReceipt(ProductOnReceipt);
                MessageBox.Show("Product removed from receipt successfully");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void ClearSlots()
        { 
            Stock = new ProductStock();
            Date = DateTime.MinValue;
        }

        private void ClearAll()
        {
            Receipt = new Receipt();
            ClearSlots();
        }
    }
}
