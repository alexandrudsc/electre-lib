#pragma once
#include <vector>

#include "criteriu.hpp"
#include "alternativa.hpp"

/** Metoda Electre
 *  
 *
*/
namespace electre
{
    class algoritm
	{
	public:
		static void initializare();
		static void adauga_criteriu(const criteriu &);
		static void adauga_alternativa(const alternativa &);

		/**
		* Functia principala unde se executa algorimul
		* Initializarea trebuie facuta inainte
		*/
		static bool ruleaza();

		static std::string afiseaza_input();

		static algoritm algoritm_electre;
	private:
		static const int MAX_ALTERNATIVE = 1000;
		static const int MAX_CRITERII = 1000;

    /**
    * Pasul 1 - validare
    */
    bool validare();

		/** 
     * Pasul 2 - normalizarea valorilor din matricea de decizie
		 * x[i][j] = criteriu[i][j] / rad( sum (criteriu[i][j])
		 * Pentru fiecare x[i][j] aplicam ponderea criteriului
		 */
		void normalizare();

		/**
		 * Pasul 3 calcularea matricei concordantei
     * x[i][j] = suma coeficientilor de importanta pentru toate
     * criteriile pentru care Varianta i are valoare mai mare ca Varianta j
		 */
		void concordanta();

		/**
		* Pasul 4 calcularea matricei disconcordantei
    * x[i][j] = suma diferentelor dintre valorile criteriilor variantei j si varianta i
    * pentru care varianta j are nota mai buna decat varianta i
		*/
		void discordanta();

		/**
		* Pasul 5 surclasarea (clasificarea) variantelor
    * Daca relatia de comparare: 
    * matrice_concordanta[i][j] - matrice_discordanta[i][j] > matrice_concordanta[j][i] - matrice_discordanta[j][i] 
    * este adevarata, atunci Varianta i este mai buna decat Varianta j
		*/
		void surclasare();

		algoritm();
		~algoritm();

		double matrice_omogena[MAX_ALTERNATIVE][MAX_CRITERII];
		double matrice_concordanta[MAX_ALTERNATIVE][MAX_CRITERII];
		double matrice_discordanta[MAX_ALTERNATIVE][MAX_CRITERII];

		std::vector<criteriu> criterii;
		std::vector<alternativa> alternative;
	};

}