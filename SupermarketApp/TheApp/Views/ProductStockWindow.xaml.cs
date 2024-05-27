using System.Windows;

namespace TheApp.Views
{
    /// <summary>
    /// Interaction logic for ProductStockWindow.xaml
    /// </summary>
    public partial class ProductStockWindow : Window
    {
        public ProductStockWindow()
        {
            InitializeComponent();
        }

        private void NumberValidationTextBox(object sender, System.Windows.Input.TextCompositionEventArgs e)
        {
            if(DataContext is ViewModels.ProductStockVM vm)
            {
                vm.NumberValidationTextBox(sender, e);
            }
        }
    }
}
