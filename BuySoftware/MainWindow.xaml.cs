using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Animation;
using System.Xml;

namespace BuySoftware
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private List<Alternativa> alternative = new List<Alternativa>();
        private List<Criteriu> criterii = new List<Criteriu>();

        public MainWindow()
        {
            
            InitializeComponent();
        }

        private void btnLeftMenuHide_Click(object sender, RoutedEventArgs e)
        {
            ShowHideMenu("sbHideLeftMenu", btnLeftMenuHide, btnLeftMenuShow, pnlLeftMenu);
        }

        private void btnLeftMenuShow_Click(object sender, RoutedEventArgs e)
        {
            ShowHideMenu("sbShowLeftMenu", btnLeftMenuHide, btnLeftMenuShow, pnlLeftMenu);
        }

        private void ShowHideMenu(string strStoryboard, Button btnHide, Button btnShow, StackPanel pnl)
        {
            Storyboard sb = Resources[strStoryboard] as Storyboard;
            sb.Begin(pnl);

            if (strStoryboard.Contains("Show"))
            {
                btnHide.Visibility = System.Windows.Visibility.Visible;
                btnShow.Visibility = System.Windows.Visibility.Hidden;
            }
            else if (strStoryboard.Contains("Hide"))
            {
                btnHide.Visibility = System.Windows.Visibility.Hidden;
                btnShow.Visibility = System.Windows.Visibility.Visible;
            }
        }

        private void btnAlternative_Click(object sender, RoutedEventArgs e)
        {
            alternative.Clear();
            lAlternative.Items.Clear();
            XmlDocument doc = new XmlDocument();
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Fisier alternative(*.xml)|*.xml|All files (*.*)|*.*";
            try
            {
                if (openFileDialog.ShowDialog() == true)
                {
                    doc.Load(openFileDialog.FileName);

                    foreach (XmlNode xn in doc.SelectNodes("alternative/alternativa"))
                    {
                        Alternativa a = new Alternativa(xn["nume"].InnerText);
                        foreach (Criteriu c in criterii)
                            a.valori_criterii.Add(Double.Parse(xn[c.nume].InnerText));
                        alternative.Add(a);
                    }

                    foreach (Alternativa a in alternative)
                        lAlternative.Items.Add(a);
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show("Eroare la citire alternative: " + ex);
            }
        }

        private void btnCriterii_Click(object sender, RoutedEventArgs e)
        {
            criterii.Clear();
            XmlDocument doc = new XmlDocument();
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "Fisier criterii(*.xml)|*.xml|All files (*.*)|*.*";
            try
            {
                if (openFileDialog.ShowDialog() == true)
                {
                    doc.Load(openFileDialog.FileName);
                    XmlNode root = doc.FirstChild;
                    foreach (XmlNode xn in root.ChildNodes)
                    {
                        Criteriu c = new Criteriu();
                        c.nume = xn.Name;
                        double.TryParse(xn.InnerText, out c.coeficient_importanta);
                        criterii.Add(c);
                    }

                    foreach (Criteriu c in criterii)
                        lCriterii.Items.Add(c);
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show("Eroare la citire criterii: " + ex);
            }
        }

        private void btnRuleaza_Click(object sender, RoutedEventArgs e)
        {
            electre.initializare();
            foreach (Criteriu c in criterii)
                electre.adauga_criteriu(c.nume, c.coeficient_importanta);

            foreach (Alternativa a in alternative)
                electre.adauga_alternativa(a.nume, a.valori_criterii.ToArray(), a.valori_criterii.Count);

            int[] ordonate = new int[alternative.Count];
            if (!electre.ruleaza(ordonate))
            {
                MessageBox.Show("Eroare");
            }
            else
            {
                Alternativa[] copy = new Alternativa[lAlternative.Items.Count];
                lAlternative.Items.CopyTo(copy, 0);
                lAlternative.Items.Clear();
                foreach (int ord in ordonate)
                    lAlternative.Items.Add(copy[ord]);
            }
        }

        private void btnArataEtape_Click(object sender, RoutedEventArgs e)
        {
            StringBuilder in_params = new StringBuilder(1000);
            electre.afiseaza_etape(in_params);
            string etape_str = in_params.ToString();
            string[] etape = etape_str.Split(new[] { '=' }, StringSplitOptions.RemoveEmptyEntries);
            ElectreEtape etape_electre = new ElectreEtape();
            etape_electre.Owner = this;
            etape_electre.Title = "Etape";
            etape_electre.ShowDialog(ref etape);
            
        }
    }
}
