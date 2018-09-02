using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace BuySoftware
{
    class Alternativa
    {
        public string nume;
        private BitmapImage imagine;

        public List<double> valori_criterii = new List<double>();

        public Alternativa(string nume)
        {
            this.nume = nume;
            this.imagine = new BitmapImage(new System.Uri(AppDomain.CurrentDomain.BaseDirectory + "..\\..\\res\\unknown.png", UriKind.Absolute));
        }

        public Alternativa(string nume, string img_abs_path)
        {
            this.nume = nume;
            this.imagine = new BitmapImage(new System.Uri(img_abs_path, UriKind.Absolute));
            this.imagine.DecodePixelHeight = 400;
            this.imagine.DecodePixelWidth = 400;
        }

        public string Nume
        {
            get { return this.nume; }
            set { this.nume = value; }
        }

        public BitmapImage Imagine
        {
            get { return this.imagine; }
            set { this.imagine = value; }
        }
    }
}
