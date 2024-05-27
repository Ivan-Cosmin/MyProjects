using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TheApp.Models.EntityLayer;

namespace TheApp.Models.DataAccessLayer
{
    internal class ReceiptDAL
    {
        internal static int GetReceiptID(Receipt receipt)
        {
            try
            {
                int ID = 0;
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("GetReceiptID", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@CashierName", receipt.CashierName);
                cmd.Parameters.AddWithValue("@Type", "Cashier");
                cmd.Parameters.AddWithValue("@Date", receipt.Date);
                cmd.Parameters.AddWithValue("@TotalPrice", receipt.TotalPrice);

                con.Open();
                SqlDataReader reader = cmd.ExecuteReader();
                while (reader.Read())
                {
                    ID = reader.GetInt32(0);
                }
                reader.Close();
                con.Close();
                return ID;
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
    }
}
