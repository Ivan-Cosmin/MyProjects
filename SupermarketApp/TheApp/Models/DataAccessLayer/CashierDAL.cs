using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data.SqlClient;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TheApp.Models.EntityLayer;

namespace TheApp.Models.DataAccessLayer
{
    internal class CashierDAL
    {
        internal void AddProductStockInReceipt(ProductOnReceipt productOnReceipt)
        {
            try
            {   
                ProductStockDAL stockDAL = new ProductStockDAL();
                int IDStock = stockDAL.GetProductStockID(productOnReceipt.Stock);
                int ReceiptID = ReceiptDAL.GetReceiptID(productOnReceipt.Receipt);

                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("AddProductStockInReceipt", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("ReceiptID", ReceiptID);
                cmd.Parameters.AddWithValue("@ProductStockID", IDStock);
                cmd.Parameters.AddWithValue("@Quantity", productOnReceipt.Quantity);
                cmd.Parameters.AddWithValue("@Price", productOnReceipt.Price);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void AddReceipt(Receipt receipt)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("AddReceipt", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Date", receipt.Date);
                cmd.Parameters.AddWithValue("@TotalPrice", receipt.TotalPrice);
                cmd.Parameters.AddWithValue("@CashierName", receipt.CashierName);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal ObservableCollection<ProductStock> SearchProduct(ProductStock stock)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("SearchProducts", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", stock.Product.Name);
                cmd.Parameters.AddWithValue("@Barcode", stock.Product.Barcode);
                if(stock.ExpiryDate != DateTime.MinValue)
                    cmd.Parameters.AddWithValue("@ExpiryDate", stock.ExpiryDate);
                cmd.Parameters.AddWithValue("@ManufacturerName", stock.Product.Manufacturer.Name);
                cmd.Parameters.AddWithValue("@CategoryName", stock.Product.Category.Name);

                con.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                ObservableCollection<ProductStock> result = new ObservableCollection<ProductStock>();

                while (reader.Read())
                {
                    result.Add(
                        new ProductStock
                        {
                            Product = new Product()
                            {
                                Barcode = reader["Barcode"].ToString(),
                                Name = reader["Name"].ToString(),
                                Category = new Category()
                                {
                                    Name = reader["CategoryName"].ToString()
                                },
                                Manufacturer = new Manufacturer()
                                {
                                    Name = reader["ManufacturerName"].ToString()
                                }
                            },
                            Quantity = Convert.ToInt32(reader["Quantity"]),
                            UnitOfMeasure = reader["UnitOfMeasure"].ToString(),
                            ExpiryDate = Convert.ToDateTime(reader["ExpiryDate"]),
                            SellingPrice = Convert.ToDecimal(reader["SellingPrice"])
                        }
                    );
                }
                reader.Close();

                con.Close();
                return result;
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void UpdateStock(ProductStock stockToAddInReceipt)
        {
            try
            {
                int IDStock = new ProductStockDAL().GetProductStockID(stockToAddInReceipt);
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("UpdateStockQuantity", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@StockID", IDStock);
                cmd.Parameters.AddWithValue("@Quantity", stockToAddInReceipt.Quantity);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
    }
}
