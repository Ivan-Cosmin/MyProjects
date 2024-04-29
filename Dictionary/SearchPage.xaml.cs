using Dictionar.Classes;
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

namespace Dictionar
{
    /// <summary>
    /// Interaction logic for SearchPage.xaml
    /// </summary>
    public partial class SearchPage : Window, INotifyPropertyChanged
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

        private BitmapImage _imageSource;
        public BitmapImage ImageSource
        {
            get => _imageSource;
            private set
            {
                _imageSource = value;
                NotifyPropertyChanged(nameof(ImageSource));
            }
        }

        private Word word = new Word { ImagePath = "Resources\\unknown.PNG" };
        public Word Word
        {
            get { return word; }
            set
            {
                word = value;
                NotifyPropertyChanged("Word");
            }
        }

        private void ChangeImage(string path)
        {
            BitmapImage bitmapImage = new BitmapImage();

            bitmapImage.BeginInit();
            bitmapImage.UriSource = new Uri(path, UriKind.RelativeOrAbsolute);
            bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
            bitmapImage.EndInit();

            ImageSource = bitmapImage;
        }
        public SearchPage()
        {
            InitializeComponent();
            this.DataContext = this;
            PopulateCategoriesComboBox();
        }

        private void DisplayImage(Word word)
        {
            ChangeImage(word.ImagePath);
        }

        private void PopulateCategoriesComboBox()
        {
            List<string> existingCategories = editDictionary.GetExistingCategories();

            // add categories in comboBox
            foreach (string category in existingCategories)
            {
                categoryComboBox.Items.Add(category);
            }
        }

        private void listBoxSuggestions_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void categoryComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            string selectedCategory = categoryComboBox.SelectedItem as string;

            List<Word> words = editDictionary.GetWordsByCategory(selectedCategory);

            searchResultsListBox.Items.Clear();

            foreach (Word word in words)
            {
                searchResultsListBox.Items.Add(word);
            }
        }

        private void searchResultsListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            Word selectedWord = searchResultsListBox.SelectedItem as Word;

            if (selectedWord != null)
            {
                Word = selectedWord;
                DisplayImage(selectedWord);
            }
        }

        private void textBoxInput_TextChanged_1(object sender, TextChangedEventArgs e)
        {
            string input = textBoxInput.Text;

            List<Word> words = editDictionary.GetWordsByInput(input);

            searchResultsListBox.Items.Clear();

            foreach (Word word in words)
            {
                searchResultsListBox.Items.Add(word);
            }
        }
        private void Reset_Click(object sender, RoutedEventArgs e)
        {
            this.Close();

            SearchPage newWindow = new SearchPage();
            newWindow.Show();
        }

        private void Search_Click(object sender, RoutedEventArgs e)
        {
            string input = textBoxInput.Text;

            List<Word> words = editDictionary.GetWordsByInput(input);

            searchResultsListBox.Items.Clear();

            foreach (Word word in words)
            {
                searchResultsListBox.Items.Add(word);
            }
        }
    }
}
