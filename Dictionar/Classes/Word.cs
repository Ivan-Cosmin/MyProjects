using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Dictionar.Classes
{
    public class Word
    {
        [XmlElement("Category")]
        public string Category { get; set; }

        [XmlElement("Word")]
        public string WordText { get; set; }

        [XmlElement("Description")]
        public string Description { get; set; }

        [XmlElement("ImagePath")]
        public string ImagePath { get; set; }
    }
}
