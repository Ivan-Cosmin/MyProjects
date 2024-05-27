using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TheApp.Models.DataAccessLayer;
using TheApp.Models.EntityLayer;

namespace TheApp.Models.BusinessLogicLayer
{
    internal class ManufacturersBLL
    {
        public ObservableCollection<Manufacturer> ManufacturersList = new ObservableCollection<Manufacturer>();
        ManufacturersDAL manufacturersDAL = new ManufacturersDAL();

        internal void ActivateManufacturer(Manufacturer manufacturer)
        {
            try
            {
                Validate(manufacturer);
                ValidateNonExistence(manufacturer);
                manufacturersDAL.ActivateManufacturer(manufacturer);
                manufacturer.Deleted = false;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        internal void AddManufacturer(Manufacturer manufacturer)
        {
            try
            {
                Validate(manufacturer);
                ValidateExistence(manufacturer);
                manufacturersDAL.ValidateExistence(manufacturer);
                manufacturersDAL.AddManufacturer(manufacturer);
                ManufacturersList.Add(manufacturer);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void DeleteManufacturer(Manufacturer manufacturer)
        {
            try
            {
                Validate(manufacturer);
                ValidateNonExistence(manufacturer);
                manufacturersDAL.DeleteManufacturer(manufacturer);
                manufacturer.Deleted = true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void GetManufacturersList()
        {
            try
            {
                ManufacturersList = manufacturersDAL.GetManufacturersList();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void ModifyManufacturer(Manufacturer selectedManufacturer,Manufacturer manufacturer)
        {
            try
            {
                Validate(manufacturer);
                Validate(selectedManufacturer);
                ValidateNonExistence(selectedManufacturer);
                manufacturersDAL.ModifyManufacturer(selectedManufacturer, manufacturer);
                selectedManufacturer.Name = manufacturer.Name;
                selectedManufacturer.CountryOfOrigin = manufacturer.CountryOfOrigin;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void ValidateNonExistence(Manufacturer manufacturer)
        {
            ValidateManufacturerNull(manufacturer);
            if (!ManufacturersList.Contains(manufacturer))
            {
                throw new Exception("Manufacturer does not exist");
            }
        }

        private void ValidateExistence(Manufacturer manufacturer)
        {
            ValidateManufacturerNull(manufacturer);
            if (ManufacturersList.Contains(manufacturer))
            {
                throw new Exception("Manufacturer already exists");
            }
        }

        private void Validate(Manufacturer manufacturer)
        {
            ValidateManufacturerNull(manufacturer);
            if(string.IsNullOrWhiteSpace(manufacturer.Name))
            {
                throw new Exception("Name is required");
            }
            if (string.IsNullOrWhiteSpace(manufacturer.CountryOfOrigin))
            {
                throw new Exception("Country of origin is required");
            }
        }

        private void ValidateManufacturerNull(Manufacturer manufacturer)
        {
            if(manufacturer == null)
            {
                throw new Exception("Manufacturer is null");
            }
        }
    }
}
