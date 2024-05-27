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
    internal class UserDAL
    {
        internal void AddUser(User user)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("AddUser", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Username", user.Username);
                cmd.Parameters.AddWithValue("@Password", user.Password);
                cmd.Parameters.AddWithValue("@Type", user.Type);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
        internal void DeleteUser(User user)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("DeleteUser", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Username", user.Username);
                cmd.Parameters.AddWithValue("@Password", user.Password);
                cmd.Parameters.AddWithValue("@Type", user.Type);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void ActivateUser(User user)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("ActivateUser", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Username", user.Username);
                cmd.Parameters.AddWithValue("@Password", user.Password);
                cmd.Parameters.AddWithValue("@Type", user.Type);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
        internal ObservableCollection<string> GetTypeUserList()
        {
            return new ObservableCollection<string>
            {
                "Admin",
                "Cashier"
            };
        }
        internal ObservableCollection<User> GetUsersList()
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("GetAllUsers", con);
                ObservableCollection<User> result = new ObservableCollection<User>();
                cmd.CommandType = CommandType.StoredProcedure;
                con.Open();

                SqlDataReader reader = cmd.ExecuteReader();
               
                while (reader.Read())
                {
                    result.Add(
                        new User()
                        {
                            Username = reader["Username"].ToString(),
                            Password = reader["Password"].ToString(),
                            Type = reader["Type"].ToString(),
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

        internal void ValidateExistence(User user)
        {
            try
            {
                SqlConnection con = DALHelper.Connection; 
                SqlCommand cmd = new SqlCommand("CheckUserExists", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Username", user.Username);
                cmd.Parameters.AddWithValue("@Type", user.Type);

                con.Open();
                int result = (int)cmd.ExecuteScalar();
                con.Close();

                if(result == 1)
                    throw new Exception("User already exists!");
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void ModifyUser(User selectedUser, User user)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("ModifyUser", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Username", selectedUser.Username);
                cmd.Parameters.AddWithValue("@Password", selectedUser.Password);
                cmd.Parameters.AddWithValue("@Type", selectedUser.Type);
                cmd.Parameters.AddWithValue("@NewUsername", user.Username);
                cmd.Parameters.AddWithValue("@NewPassword", user.Password);
                cmd.Parameters.AddWithValue("@NewType", user.Type);

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
