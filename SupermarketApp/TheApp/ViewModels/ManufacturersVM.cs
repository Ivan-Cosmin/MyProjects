using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using TheApp.Models.BusinessLogicLayer;
using TheApp.Models.EntityLayer;
using TheApp.ViewModels.Commands;

namespace TheApp.ViewModels
{
    internal class ManufacturersVM: BasePropertyChanged
    {
        public ManufacturersVM() 
        {
            try
            {
                manufacturersBLL = new ManufacturersBLL();
                manufacturer = new Manufacturer();
                manufacturersBLL.GetManufacturersList();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
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

        private Manufacturer selectedManufacturer;
        public Manufacturer SelectedManufacturer
        {
            get { return selectedManufacturer; }
            set
            {
                selectedManufacturer = value;
                Manufacturer.Name = value.Name;
                Manufacturer.CountryOfOrigin = value.CountryOfOrigin;
                NotifyPropertyChanged("SelectedManufacturer");
                NotifyPropertyChanged("Manufacturer");
            }
        }

        readonly ManufacturersBLL manufacturersBLL;
        public ObservableCollection<Manufacturer> ManufacturersList
        {
            get => manufacturersBLL.ManufacturersList;
            set => manufacturersBLL.ManufacturersList = value;
        }

        private ICommand addCommand;
        private ICommand modifyCommand;
        private ICommand deleteCommand;
        private ICommand activateCommand;

        public ICommand AddCommand
        {
            get
            {
                if (addCommand == null)
                {
                    addCommand = new RelayCommand(AddManufacturer);
                }
                return addCommand;
            }
        }
        public ICommand ModifyCommand
        {
            get
            {
                if (modifyCommand == null)
                {
                    modifyCommand = new RelayCommand(ModifyManufacturer);
                }
                return modifyCommand;
            }
        }
        public ICommand DeleteCommand
        {
            get
            {
                if (deleteCommand == null)
                {
                    deleteCommand = new RelayCommand(DeleteManufacturer);
                }
                return deleteCommand;
            }
        }
        public ICommand ActivateCommand
        {
            get
            {
                if (activateCommand == null)
                {
                    activateCommand = new RelayCommand(ActivateManufacturer);
                }
                return activateCommand;
            }
        }

        private void ActivateManufacturer(object parameter)
        {
            try
            {
                manufacturersBLL.ActivateManufacturer(SelectedManufacturer);
                MessageBox.Show("Manufacturer activated successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void AddManufacturer(object parameter)
        { 
            try
            {
                manufacturersBLL.AddManufacturer(Manufacturer);
                MessageBox.Show("Manufacturer added successfully");
                Clear();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void ModifyManufacturer(object parameter)
        {
            try
            {
                manufacturersBLL.ModifyManufacturer(SelectedManufacturer, Manufacturer);
                MessageBox.Show("Manufacturer modified successfully");
                Clear();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void DeleteManufacturer(object parameter)
        {
            try
            {
                manufacturersBLL.DeleteManufacturer(SelectedManufacturer);
                MessageBox.Show("Manufacturer deleted successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void Clear()
        {
            Manufacturer = new Manufacturer();
        }
    }
}
