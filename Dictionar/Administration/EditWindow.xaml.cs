using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using Dictionar.Administration.Classes;
using Dictionar.Classes;

namespace Dictionar.Administration
{
    /// <summary>
    /// Interaction logic for EditWindow.xaml
    /// </summary>
    public partial class EditWindow : Window, INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        EditDictionaryClass editDictionary = new EditDictionaryClass();

        private Word word = new Word {Category = "Insert a new category", ImagePath = "Resources\\unknown.PNG" };
        private string wordText;
        public Word Word
        {
            get { return word; }
            set
            {
                word = value;
                NotifyPropertyChanged("Word");
            }
        }
        public EditWindow()
        {
            InitializeComponent();
            this.DataContext = this;
            PopulateCategoriesComboBox();
        }

        private void PopulateCategoriesComboBox()
        {
            List<string> existingCategories = editDictionary.GetExistingCategories();

            // add categories in comboBox
            foreach (string category in existingCategories)
            {
                newCategoryBox.Items.Add(category);
            }

            List<string> existingWords = editDictionary.GetExistingWords();
            foreach (string word in existingWords)
            {
                wordToModifyTextBox.Items.Add(word);
            }

        }

        private void wordToModify(object sender, SelectionChangedEventArgs e)
        {
            string wordTModify = wordToModifyTextBox.SelectedItem.ToString();
            Word word = editDictionary.GetWord(wordTModify);
            if (word != null)
            {
                Word = word;
                wordText = word.WordText;
                NotifyPropertyChanged("Word");
            }
        }

        private void newCategoryComboBox(object sender, SelectionChangedEventArgs e)
        {
            
        }

        private void wordNeedToModify(object sender, SelectionChangedEventArgs e)
        {
            wordToModify(sender, e);
        }

        private void SelectImageButton_Click(object sender, RoutedEventArgs e)
        {
            string path = editDictionary.imageClick();
            if (path != null)
            {
                Word.ImagePath = path;
                NotifyPropertyChanged("Word");
            }
        }

        private void OkButton_Click(object sender, RoutedEventArgs e)
        {
            editDictionary.ModifyWord(wordText, Word);
            newCategoryBox.Items.Clear();
            PopulateCategoriesComboBox();
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
