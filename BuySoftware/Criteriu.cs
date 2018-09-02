using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BuySoftware
{
    class Criteriu
    {
        public string nume = "";
        public double coeficient_importanta = 0;

        public string Nume
        {
            get { return this.nume; }
            set { this.nume = value; }
        }

        public string Coeficient
        {
            get { return this.coeficient_importanta + ""; }
            set { this.coeficient_importanta = Double.Parse(value); }
        }
    }
}
