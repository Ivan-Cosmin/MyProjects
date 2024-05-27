namespace TheApp.Models.EntityLayer
{
    internal class Product : BasePropertyChanged
    {
        public Product()
        {
            Category = new Category();
            Manufacturer = new Manufacturer();
        }
        private string _barcode;
        private string _name;
        private Category _category;
        private Manufacturer _manufacturer;
        private bool _deleted;
        public string Barcode
        {
            get { return _barcode; }
            set
            {
                _barcode = value;
                NotifyPropertyChanged("Barcode");
            }
        }
        public string Name
        {
            get { return _name; }
            set
            {
                _name = value;
                NotifyPropertyChanged("Name");
            }
        }
        public Category Category
        {
            get { return _category; }
            set
            {
                _category = value;
                NotifyPropertyChanged("Category");
            }
        }
        public Manufacturer Manufacturer
        {
            get { return _manufacturer; }
            set
            {
                _manufacturer = value;
                NotifyPropertyChanged("Manufacturer");
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
