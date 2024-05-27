using System;

namespace TheApp.Models.EntityLayer
{
    internal class Manufacturer : BasePropertyChanged
    {
        private string _name;
        private string _countryOfOrigin;
        private bool _deleted;

        public string Name
        {
            get { return _name; }
            set
            {
                _name = value;
                NotifyPropertyChanged("Name");
            }
        }

        public string CountryOfOrigin
        {
            get { return _countryOfOrigin; }
            set
            {
                _countryOfOrigin = value;
                NotifyPropertyChanged("CountryOfOrigin");
            }
        }
        public bool Deleted
        {
            get { return _deleted; }
            set
            {
                _deleted = value;
                NotifyPropertyChanged("Deleted");
            }
        }
    }
}
