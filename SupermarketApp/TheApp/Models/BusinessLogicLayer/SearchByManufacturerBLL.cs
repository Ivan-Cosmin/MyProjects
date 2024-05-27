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
    internal class SearchByManufacturerBLL : BasePropertyChanged
    {
        public SearchByManufacturerBLL()
        {
            GetProductsList();
            GetManufacturersList();
        }

        public ObservableCollection<Product> ProductsList = new ObservableCollection<Product>();
        public ObservableCollection<Manufacturer> ManufacturersList = new ObservableCollection<Manufacturer>();

        private ObservableCollection<Product> GetProductsList()
        {
            ProductDAL productDAL = new ProductDAL();
            return productDAL.GetProductsList();
        }
        internal void GetManufacturersList()
        {
            ManufacturersDAL manufacturersDAL = new ManufacturersDAL();
            ManufacturersList = manufacturersDAL.GetManufacturersList();
            NotifyPropertyChanged("ProductManufacturersList");
        }

        internal ObservableCollection<Product> SearchByManufacturer(Manufacturer manufacturer)
        {
            var List = GetProductsList();
            ProductsList.Clear();
            foreach (Product Product in List)
            { 
                if(Product.Manufacturer.Name == manufacturer.Name)
                {
                    ProductsList.Add(Product);
                }
            }
            return ProductsList;
        }
    }
}
