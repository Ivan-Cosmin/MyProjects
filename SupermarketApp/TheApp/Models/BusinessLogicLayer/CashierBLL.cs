using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data.SqlClient;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TheApp.Models.DataAccessLayer;
using TheApp.Models.EntityLayer;
using System.IO;

namespace TheApp.Models.BusinessLogicLayer
{
    internal class CashierBLL : BasePropertyChanged
    {
        public ObservableCollection<ProductOnReceipt> ProductsReceiptList = new ObservableCollection<ProductOnReceipt>();
        public ObservableCollection<ProductStock> StocksList = new ObservableCollection<ProductStock>();

        CashierDAL cashierDAL = new CashierDAL();

        internal void AddReceipt(Receipt receipt)
        {
            try
            {
                Validation(receipt);
                cashierDAL.AddReceipt(receipt);
                foreach (ProductOnReceipt productOnReceipt in ProductsReceiptList)
                {
                    receipt.CashierName = ReadCashierNameFromFile();
                    productOnReceipt.Receipt = receipt;
                    cashierDAL.AddProductStockInReceipt(productOnReceipt);
                }
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void Validation(Receipt receipt)
        {
            if (receipt == null)
            {
                throw new ArgumentNullException("stock");
            }
        }

        internal void RemoveProductFromReceipt(ProductOnReceipt productToRemove)
        {
            try
            {
                productToRemove.Stock.Quantity += productToRemove.Quantity;
                ProductsReceiptList.Remove(productToRemove);
                cashierDAL.UpdateStock(productToRemove.Stock);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void SearchProduct(ProductStock stock)
        {
            try
            {
                StocksList = cashierDAL.SearchProduct(stock);
                NotifyPropertyChanged("StocksList");
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void DeleteReceipt()
        {
            foreach (ProductOnReceipt productOnReceipt in ProductsReceiptList)
            {
                try
                {
                    RemoveProductFromReceipt(productOnReceipt);
                }
                catch (Exception ex)
                {
                    throw ex;
                }
            }
            ProductsReceiptList.Clear();

        }

        internal void AddProductToReceipt(ProductStock stockToAddInReceipt, int quantity)
        {
            if (stockToAddInReceipt.Quantity < quantity)
                throw new Exception("Not enough stock");
            if (quantity <= 0)
                throw new Exception("Quantity must be greater than 0");

            ProductOnReceipt productOnReceipt = new ProductOnReceipt
            {
                Stock = stockToAddInReceipt,
                Quantity = quantity,
                Price = stockToAddInReceipt.SellingPrice * quantity
            };
            ProductsReceiptList.Add(productOnReceipt);
            stockToAddInReceipt.Quantity -= quantity;
            NotifyPropertyChanged("ProductsReceiptList");

            cashierDAL.UpdateStock(stockToAddInReceipt);
        }

        private string ReadCashierNameFromFile()
        {
            try
            {
                string filePath = "calea_catre_fisier.txt";
                // Deschiderea fișierului și citirea primei linii
                using (StreamReader reader = new StreamReader(filePath))
                {
                    string line = reader.ReadLine();
                    string[] words = line.Split(new char[] { ' ', '\t' }, StringSplitOptions.RemoveEmptyEntries);
                    return words[0];
                }
            }
            catch (IOException ex)
            {
                throw(ex);
            }
        }
    }
}
