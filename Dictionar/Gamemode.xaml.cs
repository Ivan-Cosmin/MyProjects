using Dictionar.Administration.Classes;
using System;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Dictionar.Classes;
using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;
using System.ComponentModel;

namespace Dictionar
{
    /// <summary>
    /// Interaction logic for Gamemode.xaml
    /// </summary>
    public partial class Gamemode : Window, INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;
        private void NotifyPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }
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
        private int buttonClicks = 0;   //turn no. x
        private int correctGuesses = 0; //correct guesses
        private List<Word> wordsList; // Words xml
        private int currentIndex = 0; // word's current index

        private void ChangeImage(string path)
        {
            BitmapImage bitmapImage = new BitmapImage();
            bitmapImage.BeginInit();
            bitmapImage.UriSource = new Uri(path, UriKind.RelativeOrAbsolute);
            bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
            bitmapImage.EndInit();
            ImageSource = bitmapImage;
        }
        public Gamemode()
        {
            InitializeComponent();
            this.DataContext = this;
            LoadWords(); // load words from xml
            ShowRandomWord();
        }
        private void ShowWord()
        {             
            if (wordsList != null && wordsList.Count > 0)
            {
                Word currentWord = wordsList[currentIndex];
                Random random = new Random();
                if(random.Next(0,2) % 2 == 0 && currentWord.ImagePath != "Resources\\unknown.PNG")
                {
                    ChangeImage(currentWord.ImagePath);
                    ImageBox.Source = ImageSource;
                }
                else
                { 
                    DescriptionBox.Text = currentWord.Description;
                }
            }
        }

        private void NextButton_Click(object sender, RoutedEventArgs e)
        {
            nextClick();
        }
        private void LoadWords()
        {
            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    wordsList = (List<Word>)serializer.Deserialize(fileStream);
                }
            }
        }
        void nextClick()
        {
            if (wordsList != null && wordsList.Count > 0)
            {
                Word currentWord = wordsList[currentIndex];
                string guessedWord = wordInputTextBox.Text.Trim().ToLower();
                if (guessedWord == currentWord.WordText.ToLower())
                {
                    MessageBox.Show("Corect answer!");
                    ++correctGuesses;
                }
                else
                {
                    MessageBox.Show($"Wrong! The answer is {currentWord.WordText}");
                }

                // removes word from word list
                wordsList.RemoveAt(currentIndex);

                if (buttonClicks == 3)
                {
                    nextButton.Visibility = Visibility.Visible;
                    nextButton.Content = "Finish";
                }
                else
                {
                    nextButton.Content = "Next";
                }

                if (buttonClicks == 4)
                {
                    MessageBox.Show($"Your score: {correctGuesses}/5.");
                    Gamemode gamemode = new Gamemode();
                    gamemode.Show();
                    this.Close();
                }
                else
                {
                    ShowRandomWord();
                    buttonClicks++;
                }
            }
        }
        private void ShowRandomWord()
        {
            if (wordsList != null && wordsList.Count > 0)
            {
                Random random = new Random();
                currentIndex = random.Next(0, wordsList.Count);
                wordInputTextBox.Text = "";
                ImageBox.Source = null;
                DescriptionBox.Text = "";
                ShowWord();
            }
        }
    }
}
