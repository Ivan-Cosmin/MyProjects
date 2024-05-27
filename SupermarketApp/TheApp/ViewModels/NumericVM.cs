using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using TheApp.Models.EntityLayer;
using TheApp.ViewModels.Commands;

namespace TheApp.ViewModels
{
    internal class NumericVM : BasePropertyChanged
    {
        private int? _inputNumber;
        public int? InputNumber
        {
            get { return _inputNumber; }
            set
            {
                _inputNumber = value;
                NotifyPropertyChanged(nameof(InputNumber));
            }
        }

        public ICommand TransmitNumberCommand { get; set; }
        public Action CloseAction { get; set; }

        public NumericVM()
        {
            TransmitNumberCommand = new RelayCommand(TransmitNumber);
        }

        private void TransmitNumber(object obj)
        {
            if (InputNumber.HasValue)
            {
                CloseAction();
            }
        }
    }
}
