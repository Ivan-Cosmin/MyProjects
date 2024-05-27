using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using TheApp.Models.BusinessLogicLayer;
using TheApp.Models.EntityLayer;
using System.Collections.ObjectModel;
using System.Windows.Input;
using TheApp.ViewModels.Commands;

namespace TheApp.ViewModels
{
    internal class CategoriesVM : BasePropertyChanged
    {
        public CategoriesVM()
        {
            try
            {
                categoriesBLL = new CategoryBLL();
                category = new Category();
                categoriesBLL.GetCategoriesList();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private Category category;
        public Category Category
        {
            get { return category; }
            set
            {
                category = value;
                NotifyPropertyChanged("Category");
            }
        }
        private Category selectedCategory;
        public Category SelectedCategory
        {
            get { return selectedCategory; }
            set
            {
                selectedCategory = value;
                Category.Name = value.Name;
                NotifyPropertyChanged("SelectedCategory");
                NotifyPropertyChanged("Category");
            }
        }

        CategoryBLL categoriesBLL;

        public ObservableCollection<Category> CategoriesList
        {
            get => categoriesBLL.CategoriesList;
            set => categoriesBLL.CategoriesList = value;
        }

        private ICommand addCommand;
        private ICommand modifyCommand;
        private ICommand deleteCommand;
        private ICommand activateCommand;
        public ICommand AddCommand
        {
            get
            {
                if (addCommand == null)
                {
                    addCommand = new RelayCommand(AddCategory);
                }
                return addCommand;
            }
        }
        public ICommand ModifyCommand
        {
            get
            {
                if (modifyCommand == null)
                {
                    modifyCommand = new RelayCommand(ModifyCategory);
                }
                return modifyCommand;
            }
        }
        public ICommand DeleteCommand
        {
            get
            {
                if (deleteCommand == null)
                {
                    deleteCommand = new RelayCommand(DeleteCategory);
                }
                return deleteCommand;
            }
        }
        public ICommand ActivateCommand
        {
            get
            {
                if (activateCommand == null)
                {
                    activateCommand = new RelayCommand(ActivateCategory);
                }
                return activateCommand;
            }
        }

        private void ActivateCategory(object parameter)
        {
            try
            {
                categoriesBLL.ActivateCategory(SelectedCategory);
                MessageBox.Show("Category activated successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void AddCategory(object parameter)
        {
            try
            {
                categoriesBLL.AddCategory(Category);
                MessageBox.Show("Category added successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }


        private void ModifyCategory(object parameter)
        {
            try
            {
                categoriesBLL.ModifyCategory(SelectedCategory, Category);
                MessageBox.Show("Category modified successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        public void DeleteCategory(object parameter)
        {
            try
            {
                categoriesBLL.DeleteCategory(SelectedCategory);
                MessageBox.Show("Category deleted successfully");
                Clear();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        private void Clear()
        {
            Category = new Category();
        }
    }
}
