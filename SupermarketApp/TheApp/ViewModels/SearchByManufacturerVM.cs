using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using TheApp.Models.BusinessLogicLayer;
using TheApp.Models.DataAccessLayer;
using TheApp.Models.EntityLayer;
using TheApp.ViewModels.Commands;

namespace TheApp.ViewModels
{
    internal class SearchByManufacturerVM : BasePropertyChanged
    {
        SearchByManufacturerBLL searchByManufacturerBLL = new SearchByManufacturerBLL();
        public SearchByManufacturerVM() 
        {
            Manufacturer = new Manufacturer();
            searchByManufacturerBLL.GetManufacturersList();
        }


        private Manufacturer manufacturer;
        public Manufacturer Manufacturer
        {
            get { return manufacturer; }
            set
            {
                manufacturer = value;
                NotifyPropertyChanged("Manufacturer");
            }
        }

        public ObservableCollection<Product> ProductsList
        {
            get => searchByManufacturerBLL.ProductsList;
            set => searchByManufacturerBLL.ProductsList = value;
        }
        public ObservableCollection<Manufacturer> ManufacturersList
        {
            get => searchByManufacturerBLL.ManufacturersList;
            set => searchByManufacturerBLL.ManufacturersList = value;
        }


        private ICommand searchCommand;
        public ICommand SearchCommand
        {
            get
            {
                if (searchCommand == null)
                {
                    searchCommand = new RelayCommand(SearchByManufacturer);
                }
                return searchCommand;
            }
        }

        private void SearchByManufacturer(object obj)
        {
            ProductsList = searchByManufacturerBLL.SearchByManufacturer(Manufacturer);
            NotifyPropertyChanged("ProductsList");
        }
    }
}
