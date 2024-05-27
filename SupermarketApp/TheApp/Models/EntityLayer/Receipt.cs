using System;

namespace TheApp.Models.EntityLayer
{
    internal class Receipt : BasePropertyChanged
    {
        private DateTime _date;
        private string _cashierName;
        private decimal _totalPrice;

        public DateTime Date
        {
            get => _date;
            set
            {
                _date = value;
                NotifyPropertyChanged("Date");
            }
        }
        public string CashierName
        {
            get => _cashierName;
            set
            {
                _cashierName = value;
                NotifyPropertyChanged("CashierName");
            }
        }
        public decimal TotalPrice
        {
            get => _totalPrice;
            set
            {
                _totalPrice = value;
                NotifyPropertyChanged("TotalPrice");
            }
        }
    }
}
