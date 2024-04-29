using Dictionar.Administration.Classes;
using Dictionar.Classes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Dictionar.Administration
{
    /// <summary>
    /// Interaction logic for DeleteWordWindow.xaml
    /// </summary>
    public partial class DeleteWordWindow : Window
    {
        EditDictionaryClass editDictionary = new EditDictionaryClass();
        public DeleteWordWindow()
        {
            InitializeComponent();
            this.DataContext = this;
            PopulateCategoriesComboBox();
        }

        private void PopulateCategoriesComboBox()
        {
            List<string> existingWords = editDictionary.GetExistingWords();
            foreach (string word in existingWords)
            {
                wordComboBox.Items.Add(word);
            }
        }

        private void Delete_Button(object sender, RoutedEventArgs e)
        {
            string word = wordComboBox.Text;
            editDictionary.DeleteWord(word);
            wordComboBox.Items.Clear();
            PopulateCategoriesComboBox();
        }
        private void Cancel_Button(object sender, RoutedEventArgs e)
        {
            this.Close();
        }


        private void wordComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}
