using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using TheApp.Models.BusinessLogicLayer;
using TheApp.Models.DataAccessLayer;
using TheApp.Models.EntityLayer;
using TheApp.ViewModels.Commands;

namespace TheApp.ViewModels
{
    internal class ProductsVM : BasePropertyChanged
    {
        public ProductsVM()
        {
            try
            {
                productBLL = new ProductBLL();
                product = new Product();
                productBLL.GetProductsList();
                productBLL.GetCategoriesList();
                productBLL.GetManufacturersList();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private Product product;
        public Product Product
        {
            get { return product; }
            set
            {
                product = value;
                NotifyPropertyChanged("Product");
            }
        }
        private Product selectedProduct;
        public Product SelectedProduct
        {
            get { return selectedProduct; }
            set
            {
                selectedProduct = value;
                Product.Name = value.Name;
                Product.Barcode = value.Barcode;
                Product.Category = value.Category;
                Product.Manufacturer = value.Manufacturer;
                NotifyPropertyChanged("SelectedProduct");
                NotifyPropertyChanged("Product");
            }
        }

        ProductBLL productBLL;

        public ObservableCollection<Product> ProductsList
        {
            get => productBLL.ProductsList;
            set => productBLL.ProductsList = value;
        }
        public ObservableCollection<Category> CategoriesList
        {
            get => productBLL.CategoriesList;
            set => productBLL.CategoriesList = value;
        }
        public ObservableCollection<Manufacturer> ManufacturersList
        {
            get => productBLL.ManufacturersList;
            set => productBLL.ManufacturersList = value;
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
                    addCommand = new RelayCommand(AddProduct);
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
                    modifyCommand = new RelayCommand(ModifyProduct);
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
                    deleteCommand = new RelayCommand(DeleteProduct);
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
                    activateCommand = new RelayCommand(ActivateProduct);
                }
                return activateCommand;
            }
        }

        private void AddProduct(object parameter)
        {
            try
            {
                productBLL.AddProduct(Product);
                ProductsList = productBLL.ProductsList;
                MessageBox.Show("Product added successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void ModifyProduct(object parameter)
        {
            try
            {
                productBLL.ModifyProduct(SelectedProduct, Product);
                ProductsList = productBLL.ProductsList;
                MessageBox.Show("Product modified successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void DeleteProduct(object parameter)
        {
            try
            {
                productBLL.DeleteProduct(SelectedProduct);
                ProductsList = productBLL.ProductsList;
                MessageBox.Show("Product deleted successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void ActivateProduct(object parameter)
        {
            try
            {
                productBLL.ActivateProduct(SelectedProduct);
                ProductsList = productBLL.ProductsList;
                MessageBox.Show("Product activated successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Clear()
        {
            Product = new Product();
        }
    }
}
