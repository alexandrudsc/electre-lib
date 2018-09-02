using System;
using System.Collections.Generic;
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

namespace BuySoftware
{
    /// <summary>
    /// Interaction logic for ElectreEtape.xaml
    /// </summary>
    public partial class ElectreEtape : Window
    {
        class Etapa
        {
            string text = "";

            public string Text
            {
                get { return this.text; }
                set { this.text =value; }
            }
        }

        public ElectreEtape()
        {
            InitializeComponent();
        }

        public void ShowDialog(ref string[] input)
        {
            string[] rezultat = input[0].Split(new string[] { "Numar alternative" }, StringSplitOptions.RemoveEmptyEntries);
            input[0] = rezultat[0];
            Etapa e;
            for(int i = 0; i < 3; i++)
            {
                e = new Etapa();
                e.Text = input[i].Trim();
                lEtapeElectre.Items.Add(e);
            }
            e = new Etapa();
            e.Text = "Numar alternative" + rezultat[1].Trim();
            lEtapeElectre.Items.Add(e);
            ShowDialog();
            return;
        }
    }
}
