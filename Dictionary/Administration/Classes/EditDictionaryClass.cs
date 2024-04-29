using Dictionar.Classes;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Xml.Serialization;

namespace Dictionar.Administration.Classes
{
    public partial class EditDictionaryClass
    {
        public List<string> GetExistingCategories()
        {
            List<string> existingCategories = new List<string>();

            // If the xml exists then read from .xml
            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    List<Word> existingWords = (List<Word>)serializer.Deserialize(fileStream);
                    foreach (Word word in existingWords)
                    {
                        if (!existingCategories.Contains(word.Category))
                        {
                            existingCategories.Add(word.Category);
                        }
                    }
                }
            }

            return existingCategories;
        }
        public List<string> GetExistingWords()
        {
            List<string> existingCategories = new List<string>();

            // If the xml exists then read from .xml
            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    List<Word> existingWords = (List<Word>)serializer.Deserialize(fileStream);
                    foreach (Word word in existingWords)
                    {
                        if (!existingCategories.Contains(word.WordText))
                        {
                            existingCategories.Add(word.WordText);
                        }
                    }
                }
            }

            return existingCategories;
        }
        public string imageClick()
        {
            Microsoft.Win32.OpenFileDialog openFileDialog = new Microsoft.Win32.OpenFileDialog();
            openFileDialog.Filter = "Image files (*.jpg, *.jpeg, *.png)|*.jpg;*.jpeg;*.png|All files (*.*)|*.*";

            if (openFileDialog.ShowDialog() == true)
            {
                // path to selected folder
                string sourceFilePath = openFileDialog.FileName;

                try
                {
                    // local path to resources of project
                    string resourcesDirectory = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "Resources");

                    // if it doesn't exist then it gets created
                    if (!Directory.Exists(resourcesDirectory))
                    {
                        Directory.CreateDirectory(resourcesDirectory);
                    }

                    // name of folder from absolute path
                    string fileName = Path.GetFileName(sourceFilePath);

                    // new path to local path
                    string destinationFilePath = Path.Combine(resourcesDirectory, fileName);

                    // copy image to local path
                    File.Copy(sourceFilePath, destinationFilePath, true);

                    string relativePath = Path.Combine("Resources", fileName);
                    return relativePath;
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Eroare la selectarea imaginii: " + ex.Message);
                }
            }
            return null;
        }
        public void addWord(Word CurrentWord)
        {
            // category empty
            if (string.IsNullOrEmpty(CurrentWord.Category))
            {
                MessageBox.Show("Please insert a category!");
                return;
            }

            // word empty
            if (string.IsNullOrEmpty(CurrentWord.WordText))
            {
                MessageBox.Show("Please insert a wort!");
                return;
            }

            // description empty
            if (string.IsNullOrEmpty(CurrentWord.Description))
            {
                MessageBox.Show("Please insert a description!");
                return;
            }

            Word word = new Word
            {
                Category = CurrentWord.Category,
                WordText = CurrentWord.WordText,
                Description = CurrentWord.Description,
                ImagePath = CurrentWord.ImagePath
            };

            // read from xml if it exists
            List<Word> existingWords = new List<Word>();
            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    existingWords = (List<Word>)serializer.Deserialize(fileStream);
                }
            }

            // verify if word already exists
            bool wordExists = existingWords.Any(w => w.WordText.Equals(word.WordText, StringComparison.OrdinalIgnoreCase));
            if (wordExists)
            {
                MessageBox.Show("The word is already exist in dictionary.");
                return;
            }

            // add word and serialize in xml
            existingWords.Add(word);
            XmlSerializer serializer2 = new XmlSerializer(typeof(List<Word>));
            using (FileStream fileStream = new FileStream("words.xml", FileMode.Create))
            {
                serializer2.Serialize(fileStream, existingWords);
            }

            MessageBox.Show("The word was succesful added!");
        }

        internal Word GetWord(string wordToModify)
        {
            //need to return the word with the same name in the xml
            List<Word> existingWords = new List<Word>();
            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    existingWords = (List<Word>)serializer.Deserialize(fileStream);
                }
            }
            Word word = existingWords.Find(w => w.WordText.Equals(wordToModify, StringComparison.OrdinalIgnoreCase));
            if (word != null) 
            {
                return word;
            }
            return null;
        }
        public List<Word> SearchWords(string searchText, string selectedCategory)
        {
            List<Word> results = new List<Word>();

            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    List<Word> words = (List<Word>)serializer.Deserialize(fileStream);

                    // Filter words based on search text and selected category
                    results = words.Where(word =>
                                                (string.IsNullOrEmpty(selectedCategory) || word.Category.Equals(selectedCategory)) &&
                                                 word.WordText.Contains(searchText)).Select(word => new Word
                                                 {
                                                     Category = word.Category,
                                                     WordText = word.WordText,
                                                     Description = word.Description,
                                                     ImagePath = word.ImagePath
                                                 }).ToList();
                }
            }

            return results;
        }

        //make the methode GetWordsByInput(input)
        public List<Word> GetWordsByInput(string input)
        {
            List<Word> words = new List<Word>();

            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    List<Word> existingWords = (List<Word>)serializer.Deserialize(fileStream);
                    words = existingWords.Where(word => word.WordText.Contains(input)).ToList();
                }
            }

            return words;
        }

        public void ModifyWord(string wordToModify, Word newWord)
        {
            //read from xml
            List<Word> existingWords = new List<Word>();
            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    existingWords = (List<Word>)serializer.Deserialize(fileStream);
                }
            }
            //find the word to modify
            Word word = existingWords.Find(w => w.WordText.Equals(wordToModify, StringComparison.OrdinalIgnoreCase));
            if (word != null)
            {
                word.Category = newWord.Category;
                word.Description = newWord.Description;
                word.ImagePath = newWord.ImagePath;
            }
            //serialize the list of words
            XmlSerializer serializer2 = new XmlSerializer(typeof(List<Word>));
            using (FileStream fileStream = new FileStream("words.xml", FileMode.Create))
            {
                serializer2.Serialize(fileStream, existingWords);
            }
            MessageBox.Show("The word was succesful edited!");
        }

        //write a method to delete a word
        public void DeleteWord(string wordToDelete)
        {
            //read from xml
            List<Word> existingWords = new List<Word>();
            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    existingWords = (List<Word>)serializer.Deserialize(fileStream);
                }
            }
            //find the word to delete
            Word word = existingWords.Find(w => w.WordText.Equals(wordToDelete, StringComparison.OrdinalIgnoreCase));
            if (word != null)
            {
                existingWords.Remove(word);
            }
            //serialize the list of words
            XmlSerializer serializer2 = new XmlSerializer(typeof(List<Word>));
            using (FileStream fileStream = new FileStream("words.xml", FileMode.Create))
            {
                serializer2.Serialize(fileStream, existingWords);
            }
            MessageBox.Show("The word was succesful deleted!");
        }

        public List<Word> GetWordsByCategory(string selectedCategory)
        {
            List<Word> words = new List<Word>();

            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    List<Word> existingWords = (List<Word>)serializer.Deserialize(fileStream);
                    words = existingWords.Where(word => word.Category.Equals(selectedCategory)).ToList();
                }
            }

            return words;
        }

        public Word GetRandomWord()
        {
            List<Word> words = new List<Word>();

            if (File.Exists("words.xml") && new FileInfo("words.xml").Length > 0)
            {
                XmlSerializer serializer = new XmlSerializer(typeof(List<Word>));
                using (FileStream fileStream = new FileStream("words.xml", FileMode.Open))
                {
                    List<Word> existingWords = (List<Word>)serializer.Deserialize(fileStream);
                    words = existingWords;
                }
            }

            Random random = new Random();
            int index = random.Next(words.Count);
            return words[index];
        }
    }
}