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
    internal class ProductBLL
    {
        public ObservableCollection<Product> ProductsList = new ObservableCollection<Product>();
        public ObservableCollection<Category> CategoriesList = new ObservableCollection<Category>();
        public ObservableCollection<Manufacturer> ManufacturersList = new ObservableCollection<Manufacturer>();
        ProductDAL productDAL = new ProductDAL();

        internal void AddProduct(Product product)
        {
            try
            {
                Validate(product);
                ValidateExistence(product);
                productDAL.ValidateExistence(product);
                productDAL.AddProduct(product);
                ProductsList.Add(product);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void DeleteProduct(Product selectedProduct)
        {
            try
            {
                Validate(selectedProduct);
                ValidateNonExistence(selectedProduct);
                productDAL.DeleteProduct(selectedProduct);
                selectedProduct.Deleted = true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void ActivateProduct(Product selectedProduct)
        {
            try
            {
                Validate(selectedProduct);
                ValidateNonExistence(selectedProduct);
                productDAL.ActivateProduct(selectedProduct);
                selectedProduct.Deleted = false;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void ModifyProduct(Product selectedProduct, Product product)
        {
            try
            {
                Validate(product);
                Validate(selectedProduct);
                ValidateNonExistence(selectedProduct);
                productDAL.ModifyProduct(selectedProduct, product);
                selectedProduct.Barcode = product.Barcode;
                selectedProduct.Name = product.Name;
                selectedProduct.Category = product.Category;
                selectedProduct.Manufacturer = product.Manufacturer;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void ValidateNonExistence(Product product)
        {
            ValidateProductNull(product);
            if (!ProductsList.Contains(product))
            {
                throw new Exception("Product does not exists");
            }
        }
        private void ValidateExistence(Product product)
        {
            ValidateProductNull(product);
            if (ProductsList.Contains(product))
            {
                throw new Exception("Product already exists");
            }
        }

        private void Validate(Product product)
        {
            try
            {
                ValidateProductNull(product);
                ValidateProductBarcode(product.Barcode);
                ValidateProductCategory(product.Category);
                ValidateProductManufacturer(product);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void ValidateProductManufacturer(Product product)
        {
            try
            {
                ManufacturersDAL manufacturerDAL = new ManufacturersDAL();
                manufacturerDAL.ValidateNonExistence(product.Manufacturer);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void ValidateProductCategory(Category category)
        {
            try
            {
                CategoryDAL categoryDAL = new CategoryDAL();
                categoryDAL.ValidateNonExistence(category);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void ValidateProductBarcode(string barcode)
        {
            if (string.IsNullOrEmpty(barcode))
                throw new Exception("Barcode is required");
            for (int i = 0; i < barcode.Length; i++)
            {
                if (!char.IsDigit(barcode[i]))
                    throw new Exception("Barcode must be a number");
            }
        }

        private void ValidateProductNull(Product product)
        {
            if(product == null)
                throw new Exception("Product is null");
        }

        internal void GetCategoriesList()
        {   
            try
            {
                CategoryDAL categoryDAL = new CategoryDAL();
                CategoriesList = categoryDAL.GetCategoriesList();
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
                ManufacturersDAL manufacturerDAL = new ManufacturersDAL();
                ManufacturersList = manufacturerDAL.GetManufacturersList();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void GetProductsList()
        {
            try
            {
                ProductsList = productDAL.GetProductsList();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
    }
}
