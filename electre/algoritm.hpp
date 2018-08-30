#pragma once
#include <vector>

#include "criteriu.hpp"
#include "alternativa.hpp"

/** Metoda Electre
 *  
 *
*/
class algoritm
{
public:
	void initializare();
	void adauga_criteriu(const criteriu &);
	void adauga_alternativa(const alternativa &);
	void ruleaza();

private:
	
	/** Pasul 2 - normalizarea valorilor din matricea de decizie
	 * x[i][j] = criteriu[i][j] / rad( sum (criteriu[i][j])
	 * Pentru fiecare x[i][j] aplicam ponderea criteriului
	 */
	void normalizare();

	/**
	 * Pasul 3 calcularea matricei concordantei
	*/
	void concordanta();

	/**
	* Pasul 4 calcularea matricei disconcordantei
	*/
	void discordanta();

	/**
	* Pasul 5 surclasarea valorilor
	*/
	void surclasare();

	algoritm();
	~algoritm();

	std::vector<std::vector<double> > m_decizie;
	std::vector<criteriu> criterii;
	std::vector<alternativa> alternative;
};

