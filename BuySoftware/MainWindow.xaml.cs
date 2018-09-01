using System.Text;
using System.Windows;

namespace BuySoftware
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            
            InitializeComponent();
            electre.initializare();
            electre.adauga_criteriu("pret", 0.4);
            electre.adauga_criteriu("calitate", 0.3);
            electre.adauga_criteriu("performanta", 0.2);
            electre.adauga_criteriu("portabilitate", 0.1);

            electre.adauga_alternativa("visual studio", new double[] { 7, 9, 8, 10}, 4);
            electre.adauga_alternativa("android studio", new double[] { 10, 7, 8, 8 }, 4);
            electre.adauga_alternativa("eclipse", new double[] { 1, 8, 6, 8 }, 4);
            electre.adauga_alternativa("qt creator", new double[] { 7, 6, 10, 8 }, 4);

            StringBuilder in_params = new StringBuilder(1000);
            electre.afiseaza_input(in_params);
            MessageBox.Show(in_params.ToString());
            in_params = new StringBuilder(1000);
            electre.ruleaza();
            electre.afiseaza_input(in_params);
            MessageBox.Show(in_params.ToString());
        }
    }
}
