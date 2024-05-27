namespace TheApp.Models.EntityLayer
{
    internal class Category : BasePropertyChanged
    {
        private string _name;
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
