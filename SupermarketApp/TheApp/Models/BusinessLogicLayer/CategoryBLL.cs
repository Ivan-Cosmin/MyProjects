using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TheApp.Models.DataAccessLayer;
using TheApp.Models.EntityLayer;

namespace TheApp.Models.BusinessLogicLayer
{
    internal class CategoryBLL
    {
        public ObservableCollection<Category> CategoriesList = new ObservableCollection<Category>();
        CategoryDAL categoriesDAL = new CategoryDAL();

        internal void AddCategory(Category category)
        {
            try
            {
                Validate(category);
                ValidateExistence(category);
                categoriesDAL.ValidateExistence(category);
                categoriesDAL.AddCategory(category);
                CategoriesList.Add(category);
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }


        internal void DeleteCategory(Category category)
        {
            try
            {
                Validate(category);
                ValidateNonExistence(category);
                categoriesDAL.DeleteCategory(category);
                category.Deleted = true;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void ActivateCategory(Category category)
        {
            try
            {
                Validate(category);
                ValidateNonExistence(category);
                categoriesDAL.ActivateCategory(category);
                category.Deleted = false;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        internal void ModifyCategory(Category selectedCategory, Category category)
        {
            try
            {
                Validate(category);
                Validate(selectedCategory);
                ValidateNonExistence(selectedCategory);
                categoriesDAL.ModifyCategory(selectedCategory, category);
                selectedCategory.Name = category.Name;
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }
        internal void GetCategoriesList()
        {
            try
            {
                CategoriesList = categoriesDAL.GetCategoriesList();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void Validate(Category category)
        {
            ValidateCategoryNull(category);
            if (string.IsNullOrEmpty(category.Name))
            {
                throw new Exception("Name is required");
            }
        }

        private void ValidateNonExistence(Category category)
        {
            ValidateCategoryNull(category);
            if(!CategoriesList.Contains(category))
            {
                throw new Exception("Category does not exists");
            }
        }

        private void ValidateCategoryNull(Category category)
        {
            if (category == null)
            {
                throw new Exception("Category is required");
            }
        }

        private void ValidateExistence(Category category)
        {
            ValidateCategoryNull(category);
            if (CategoriesList.Contains(category))
            {
                throw new Exception("Category already exists");
            }
        }

    }
}
