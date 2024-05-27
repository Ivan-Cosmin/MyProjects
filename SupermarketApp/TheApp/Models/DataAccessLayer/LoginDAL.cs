using System.Data;
using System.Data.SqlClient;
using TheApp.Models.EntityLayer;

namespace TheApp.Models.DataAccessLayer
{
    internal class LoginDAL
    {
        public string ValidateLogin(User user)
        {
            SqlConnection con = DALHelper.Connection;
            try
            {
                SqlCommand cmd = new SqlCommand("Login", con);
                cmd.CommandType = CommandType.StoredProcedure;
                con.Open();
                cmd.Parameters.Add(new SqlParameter("@Username", user.Username));
                cmd.Parameters.Add(new SqlParameter("@Password", user.Password));
                cmd.Parameters.Add(new SqlParameter("@Type", user.Type));
                var result = cmd.ExecuteScalar();
                con.Close();

                if (result != null)
                {
                    return user.Type;
                }
                return null;
            }
            finally
            {
                con.Close();
            }
        }
    }
}
