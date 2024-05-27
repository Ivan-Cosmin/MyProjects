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
    internal class ProductDAL
    {
        internal void ActivateProduct(Product product)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("ActivateProduct", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Barcode", product.Barcode);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void AddProduct(Product product)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("AddProduct", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Barcode", product.Barcode);
                cmd.Parameters.AddWithValue("@Name", product.Name);
                cmd.Parameters.AddWithValue("@CategoryName", product.Category.Name);
                cmd.Parameters.AddWithValue("@ManufacturerName", product.Manufacturer.Name);
                cmd.Parameters.AddWithValue("@ManufacturerCountryOfOrigin", product.Manufacturer.CountryOfOrigin);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void DeleteProduct(Product product)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("DeleteProduct", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Barcode", product.Barcode);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal ObservableCollection<Product> GetProductsList()
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("GetAllProducts", con);
                ObservableCollection<Product> result = new ObservableCollection<Product>();
                cmd.CommandType = CommandType.StoredProcedure;
                con.Open();

                SqlDataReader reader = cmd.ExecuteReader();

                while (reader.Read())
                {
                    Product p = new Product();
                    p.Barcode = reader["Barcode"].ToString();
                    p.Name = reader["Name"].ToString();
                    p.Category = new Category()
                    {
                        Name = reader["CategoryName"].ToString()
                    };
                    p.Manufacturer = new Manufacturer()
                    {
                        Name = reader["ManufacturerName"].ToString(),
                        CountryOfOrigin = reader["ManufacturerCountryOfOrigin"].ToString()
                    };

                    p.Deleted = (bool)reader["Deleted"];
                    result.Add(p);
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

        internal void ModifyProduct(Product selectedProduct, Product product)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("ModifyProduct", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Barcode", selectedProduct.Barcode);
                cmd.Parameters.AddWithValue("@NewBarcode", product.Barcode);
                cmd.Parameters.AddWithValue("@NewName", product.Name);
                cmd.Parameters.AddWithValue("@NewCategoryName", product.Category.Name);
                cmd.Parameters.AddWithValue("@NewManufacturerName", product.Manufacturer.Name);
                cmd.Parameters.AddWithValue("@NewManufacturerCountryOfOrigin", product.Manufacturer.CountryOfOrigin);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal int Validate(Product product)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("CheckProductExists", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Barcode", product.Barcode);

                con.Open();
                int result = (int)cmd.ExecuteScalar();
                con.Close();

                return result;
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
        internal void ValidateExistence(Product product)
        {
            try
            {
                if (Validate(product) == 1)
                    throw new Exception("Product already exists!");
            }
            catch (SqlException ex)
            {
                throw ex;
            }

        }
        internal void ValidateNonExistence(Product product)
        {
            try
            {
                if (Validate(product) == 0)
                    throw new Exception("Product does not exists!");
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
    }
}
