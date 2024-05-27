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
    internal class ManufacturersDAL
    {
        internal void AddManufacturer(Manufacturer manufacturer)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("AddManufacturer", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", manufacturer.Name);
                cmd.Parameters.AddWithValue("@CountryOfOrigin", manufacturer.CountryOfOrigin);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void DeleteManufacturer(Manufacturer manufacturer)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("DeleteManufacturer", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", manufacturer.Name);
                cmd.Parameters.AddWithValue("@CountryOfOrigin", manufacturer.CountryOfOrigin);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
        internal void ActivateManufacturer(Manufacturer manufacturer)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("ActivateManufacturer", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", manufacturer.Name);
                cmd.Parameters.AddWithValue("@CountryOfOrigin", manufacturer.CountryOfOrigin);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
        internal void ModifyManufacturer(Manufacturer selectedManufacturer, Manufacturer manufacturer)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("ModifyManufacturer", con);

                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.AddWithValue("@Name", selectedManufacturer.Name);
                cmd.Parameters.AddWithValue("@CountryOfOrigin", selectedManufacturer.CountryOfOrigin);
                cmd.Parameters.AddWithValue("@NewName", manufacturer.Name);
                cmd.Parameters.AddWithValue("@NewCountryOfOrigin", manufacturer.CountryOfOrigin);

                con.Open();
                cmd.ExecuteNonQuery();
                con.Close();
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal ObservableCollection<Manufacturer> GetManufacturersList()
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("GetAllManufacturers", con);
                ObservableCollection<Manufacturer> result = new ObservableCollection<Manufacturer>();
                cmd.CommandType = CommandType.StoredProcedure;
                con.Open();

                SqlDataReader reader = cmd.ExecuteReader();

                while (reader.Read())
                {
                    result.Add(
                        new Manufacturer()
                        {
                            Name = reader["Name"].ToString(),
                            CountryOfOrigin = reader["CountryOfOrigin"].ToString(),
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

        internal int Validate(Manufacturer manufacturer)
        {
            try
            {
                SqlConnection con = DALHelper.Connection;
                SqlCommand cmd = new SqlCommand("CheckManufacturerExists", con)
                {
                    CommandType = CommandType.StoredProcedure
                };
                cmd.Parameters.AddWithValue("@Name", manufacturer.Name);
                cmd.Parameters.AddWithValue("@CountryOfOrigin", manufacturer.CountryOfOrigin);

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

        internal void ValidateExistence(Manufacturer manufacturer)
        {
            try
            {
                if (Validate(manufacturer) == 1)
                    throw new Exception("Manufacturer already exists!");
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }

        internal void ValidateNonExistence(Manufacturer manufacturer)
        {
            try
            {
                if (Validate(manufacturer) == 0)
                    throw new Exception("Manufacturer does not exists!");
            }
            catch (SqlException ex)
            {
                throw ex;
            }
        }
    }
}
