using TheApp.Models.EntityLayer;

namespace TheApp.Models.EntityLayer
{
    internal class ProductOnReceipt : BasePropertyChanged
    {
        private Receipt _receipt;
        private ProductStock _stock;
        private int _quantity;
        private decimal _price;


        public Receipt Receipt
        {
            get {return _receipt;}
            set
            {
                _receipt = value;
                NotifyPropertyChanged("Receipt");
            }
        }
        public ProductStock Stock
        {
            get => _stock;
            set
            {
                _stock = value;
                NotifyPropertyChanged("Stock");
            }
        }
        public int Quantity
        {
            get => _quantity;
            set
            {
                _quantity = value;
                NotifyPropertyChanged("Quantity");
            }
        }
        public decimal Price
        {
            get => _price;
            set
            {
                _price = value;
                NotifyPropertyChanged("Price");
            }
        }

    }
}
