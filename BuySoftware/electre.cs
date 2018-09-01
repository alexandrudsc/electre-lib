using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BuySoftware
{
    class electre
    {

        [DllImport("..\\..\\..\\Debug\\electre.dll", EntryPoint = "initializare")]
        public static extern void initializare();

        [DllImport("..\\..\\..\\Debug\\electre.dll", EntryPoint = "adauga_criteriu")]
        public static extern void adauga_criteriu(string nume, double pondere);

        [DllImport("..\\..\\..\\Debug\\electre.dll", EntryPoint = "adauga_alternativa")]
        public static extern void adauga_alternativa(string nume, double[] valori, int numar_criterii);

        [DllImport("..\\..\\..\\Debug\\electre.dll", EntryPoint = "ruleaza")]
        public static extern void ruleaza();

        [DllImport("..\\..\\..\\Debug\\electre.dll", EntryPoint = "afiseaza_input")]
        public static extern void afiseaza_input(StringBuilder in_params);
    }
}
