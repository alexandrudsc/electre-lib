// electre.cpp : Defines the exported functions for the DLL application.
//

#include <vector>
#include <string>

#include "stdafx.h"


#include "algoritm.hpp"
#include "criteriu.hpp"
#include "alternativa.hpp"

extern "C"
{
	__declspec(dllexport) void __stdcall initializare()
	{
		electre::algoritm::initializare();
	}

	/**
	* Functia principala unde se executa algorimul
	* Initializarea trebuie facuta inainte
	*/
	__declspec(dllexport) void __stdcall ruleaza()
	{
		electre::algoritm::ruleaza();
	}

	__declspec(dllexport) void __stdcall  adauga_criteriu(char *nume, double coef_importanta)
	{
		criteriu c;
		c.nume = std::string(nume);
		c.coef_importanta = coef_importanta;
		electre::algoritm::adauga_criteriu(c);
	}
	
	__declspec(dllexport) void __stdcall adauga_alternativa(char *nume, double *valori_criterii, int nr_criterii)
	{
		alternativa a;
		a.nume = std::string(nume);
		for (int i = 0; i < nr_criterii; i++)
		{
			a.valori_criterii.push_back(valori_criterii[i]);
		}
		electre::algoritm::adauga_alternativa(a);
	}

	__declspec(dllexport) void __stdcall afiseaza_input(char *out)
	{
		std::string str = electre::algoritm::algoritm_electre.afiseaza_input();
		str.copy(out, str.length());
	}


}

