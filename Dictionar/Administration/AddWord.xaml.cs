
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;

using Dictionar.Administration.Classes;
using Dictionar.Classes;

namespace Dictionar.Administration
{
    /// <summary>
    /// Interaction logic for AddWord.xaml
    /// </summary>
    public partial class AddWord : Window, INotifyPropertyChanged
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

        private Word word = new Word {ImagePath = "Resources\\unknown.PNG" }; 
        public Word Word
        {
            get { return word; }
            set
            {
                word = value;
                NotifyPropertyChanged("Word");
            }
        }

        public AddWord()
        {
            InitializeComponent();
            this.DataContext = this;
            addCategoriesToComboBox();
        }

        void addCategoriesToComboBox()
        {
            List<string> existingCategories = editDictionary.GetExistingCategories();
            foreach (string category in existingCategories)
            {
                categoryComboBox.Items.Add(category);
            }
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
        private void AddButton_Click(object sender, RoutedEventArgs e)
        {
            editDictionary.addWord(Word);
            categoryComboBox.Items.Clear();
            descriptionTextBox.Clear();
            wordTextBox.Clear();
            imagePathTextBox.Clear();
            Word.ImagePath = "Resources\\unknown.PNG";
            addCategoriesToComboBox();
        }

        private void imagePathTextBox_TextChanged(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {

        }

        private void categoryComboBox_SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {

        }
    }
}
