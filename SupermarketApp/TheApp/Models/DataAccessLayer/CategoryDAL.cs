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
    internal class CategoryDAL
    {
        internal void AddCategory(Category category)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("AddCategory", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", category.Name);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void DeleteCategory(Category category)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("DeleteCategory", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", category.Name);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void ActivateCategory(Category category)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("ActivateCategory", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", category.Name);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void ModifyCategory(Category selectedCategory, Category category)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("ModifyCategory", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", selectedCategory.Name);
                cmd.Parameters.AddWithValue("@NewName", category.Name);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal ObservableCollection<Category> GetCategoriesList()
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("GetAllCategories", con);
                ObservableCollection<Category> result = new ObservableCollection<Category>();
                cmd.CommandType = CommandType.StoredProcedure;
                con.Open();

                SqlDataReader reader = cmd.ExecuteReader();

                while (reader.Read())
                {
                    result.Add(
                        new Category()
                        {
                            Name = reader["Name"].ToString(),
                            Deleted = (bool)reader["Deleted"]
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
        internal int Validate(Category category)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("CheckCategoryExists", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", category.Name);

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

        internal void ValidateExistence(Category category)
        {
            try
            {
                if (Validate(category) == 1)
                    throw new Exception("Category already exists!");
            }
            catch(SqlException ex)
            {
                throw ex;
            }

        }

        internal void ValidateNonExistence(Category category)
        {
            try
            {
                if (Validate(category) == 0)
                    throw new Exception("Category does not exists!");
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
    }
}
