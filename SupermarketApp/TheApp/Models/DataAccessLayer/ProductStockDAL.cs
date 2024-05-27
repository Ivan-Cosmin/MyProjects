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
    internal class ProductStockDAL
    {
        internal void AddStock(ProductStock stock)
        {
            SqlConnection con = DALHelper.Connection;
            try 
            {
                SqlCommand cmd = new SqlCommand("AddProductStock", con);
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Barcode", stock.Product.Barcode);
                cmd.Parameters.AddWithValue("@Quantity", stock.Quantity);
                cmd.Parameters.AddWithValue("@UnitOfMeasure", stock.UnitOfMeasure);
                cmd.Parameters.AddWithValue("@SupplyDate", stock.SupplyDate);
                cmd.Parameters.AddWithValue("@ExpiryDate", stock.ExpiryDate);
                cmd.Parameters.AddWithValue("@PurchasePrice", stock.PurchasePrice);
                cmd.Parameters.AddWithValue("@SellingPrice", stock.SellingPrice);
                con.Open();
                cmd.ExecuteNonQuery();
            }
            catch(SqlException ex)
            {
                throw ex;
            }
        }

        internal int GetProductStockID(ProductStock stock)
        {
            SqlConnection con = DALHelper.Connection;
            try
            {
                SqlCommand cmd = new SqlCommand("GetProductStockID", con);
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Barcode", stock.Product.Barcode);
                cmd.Parameters.AddWithValue("@PurchasePrice", stock.PurchasePrice);
                con.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                if (reader.Read())
                {
                    return Convert.ToInt32(reader["ID"]);
                }
                return -1;
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal ObservableCollection<ProductStock> GetProductStockList()
        {
            SqlConnection con = DALHelper.Connection;
            try
            {
                SqlCommand cmd = new SqlCommand("GetAllProductStocks", con);
                ObservableCollection<ProductStock> result = new ObservableCollection<ProductStock>();
                cmd.CommandType = CommandType.StoredProcedure;
                con.Open();
                SqlDataReader reader; 
                reader = cmd.ExecuteReader();

                while (reader.Read())
                {
                    result.Add(
                              new ProductStock()
                                               {
                            Product = new Product()
                            {
                                Barcode = reader["Barcode"].ToString(),
                                Name = reader["ProductName"].ToString(),
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
                            SupplyDate = Convert.ToDateTime(reader["SupplyDate"]),
                            ExpiryDate = Convert.ToDateTime(reader["ExpiryDate"]),
                            PurchasePrice = Convert.ToDecimal(reader["PurchasePrice"]),
                            SellingPrice = Convert.ToDecimal(reader["SellingPrice"]),
                        }
                                                                  );
                }
                reader.Close();
                return result;
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
    }
}
