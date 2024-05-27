using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using TheApp.Models.DataAccessLayer;
using TheApp.Models.EntityLayer;

namespace TheApp.Models.BusinessLogicLayer
{
    internal class ProductStockBLL
    {

        ProductStockDAL stockDAL = new ProductStockDAL();

        public ObservableCollection<Product> ProductsList = new ObservableCollection<Product>();
        public ObservableCollection<ProductStock> ProductStocksList = new ObservableCollection<ProductStock>();

        private void Validation(ProductStock stock)
        {
            if (stock == null)
            {
                throw new ArgumentNullException("stock");
            }
            if (stock.Product == null || stock.Product.Barcode == null)
            {
                throw new Exception("Select a valid Product!");
            }
            if (stock.UnitOfMeasure == null)
            {
                throw new Exception("Unit of Measure must be set!");
            }
            if (stock.Quantity <= 0)
            {
                throw new Exception("Quantity must be greater than 0!");
            }
            if (stock.PurchasePrice <= 0)
            {
                throw new Exception("Purchase Price must be greater than 0!");
            }
            if (stock.SellingPrice <= 0)
            {
                throw new Exception("Selling Price must be greater than 0!");
            }
            if (stock.SupplyDate == null)
            {
                throw new Exception("Supply Date must be set!");
            }
            if (stock.ExpiryDate == null)
            {
                throw new Exception("Expiry Date must be set!");
            }
            if (stock.SupplyDate > stock.ExpiryDate)
            {
                throw new Exception("Supply Date must be before Expiry Date!");
            }
        }

        internal void AddStock(ProductStock stock)
        {
            Validation(stock);
            stockDAL.AddStock(stock);
            ProductStocksList.Add(stock);
        }

        internal ObservableCollection<Product> GetProductsList()
        {
            ProductDAL productDAL = new ProductDAL();
            return productDAL.GetProductsList();
        }
        internal ObservableCollection<ProductStock> GetProductStocksList()
        {
            return stockDAL.GetProductStockList();
        }
    }
}
