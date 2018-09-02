#include <algorithm>
#include <numeric>
#include <sstream>
#include <iostream>

#include "algoritm.hpp"

using namespace std;
using namespace electre;

electre::algoritm algoritm::algoritm_electre;

///////////////////////////////////////////////////////////////////////////////
// metode publice
///////////////////////////////////////////////////////////////////////////////

bool algoritm::ruleaza()
{
  // pasul 1
  if (!algoritm_electre.validare())
    return false;
	// pasul 2
	algoritm_electre.normalizare();
	// pasul 3
	algoritm_electre.concordanta();
	// pasul 4
	algoritm_electre.discordanta();
	// pasul 5
	algoritm_electre.surclasare();
  return true;
}

void algoritm::initializare()
{
	algoritm_electre.alternative.clear();
	algoritm_electre.criterii.clear();
	memset(algoritm_electre.matrice_omogena, 0, MAX_ALTERNATIVE * MAX_CRITERII);
	memset(algoritm_electre.matrice_concordanta, 0, MAX_ALTERNATIVE * MAX_CRITERII);
	memset(algoritm_electre.matrice_discordanta, 0, MAX_ALTERNATIVE * MAX_CRITERII);
}

void algoritm::adauga_alternativa(const alternativa &a)
{
  size_t idx = algoritm_electre.alternative.size();
	algoritm_electre.alternative.push_back(a);
  algoritm_electre.alternative[idx].idx = idx;
}

void algoritm::adauga_criteriu(const criteriu &c)
{
	algoritm_electre.criterii.push_back(c);
}

std::string algoritm::afiseaza_input()
{
	std::stringstream oss;
  int n, m;
  n = algoritm_electre.alternative.size();
  m = algoritm_electre.criterii.size();

	oss << "Numar criterii: " << algoritm_electre.criterii.size() << "\n";
	for (const criteriu &c : algoritm_electre.criterii)
	{
		oss << c.nume << " " << c.coef_importanta << "\n";
	}
	oss << "Numar alternative: " << algoritm_electre.alternative.size() << "\n";
	for (const alternativa &a : algoritm_electre.alternative)
	{
		oss << a.nume << " ";
		for (double val : a.valori_criterii)
			oss << val << ", ";
		oss << "\n";
	}
	oss << "\n\n\n";
  oss << "====================================================\n";
  oss << "Matricea omogena:\n";
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      oss << algoritm_electre.matrice_omogena[i][j] << " ";
    }
    oss << "\n";
  }
  oss << "====================================================\n";
  oss << "Matricea concordanta:\n";
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      oss << algoritm_electre.matrice_concordanta[i][j] << " ";
    }
    oss << "\n";
  }
  oss << "====================================================\n";
  oss << "Matricea discordanta:\n";
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      oss << algoritm_electre.matrice_discordanta[i][j] << " ";
    }
    oss << "\n";
  }
  oss << "====================================================\n";
	return oss.str();
}

///////////////////////////////////////////////////////////////////////////////
// metode private
///////////////////////////////////////////////////////////////////////////////
algoritm::algoritm()
{
}


algoritm::~algoritm()
{
}

bool algoritm::validare()
{
  // suma coeficientilor de importanta
  double coef_sum = std::accumulate(criterii.begin(), criterii.end(), 0.0,
    [](double i, const criteriu &c) {return c.coef_importanta + i; }
  );

  if (abs(coef_sum - 100 ) < 0.000001)
    return true;
  if (abs(coef_sum - 1) < 0.000001)
    return true;
  return false;
}

void algoritm::normalizare()
{
  int n = alternative.size();
  int m = criterii.size();
  // matricea omogena se construieste prin aplicare coeficienti de importanta
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
	  {
	    matrice_omogena[i][j] = alternative[i].valori_criterii[j] * criterii[j].coef_importanta;
	  }
}

void algoritm::concordanta()
{
  int n = alternative.size();
  int m = criterii.size();

  // matricea concordantei pe baza coeficientilor de importanta
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      if (i == j)
        continue;
      // cautam criteriile pentru care i mai bun ca j
      for (int k = 0; k < m; k++)
        if (matrice_omogena[i][k] >= matrice_omogena[j][k])
          matrice_concordanta[i][j] += criterii[k].coef_importanta;
    }
}

void algoritm::discordanta()
{
  int n = alternative.size();
  int m = criterii.size();

  // calculare diferenta maxima din matricea omogena dintre 
  // nota cea mai mare si cea mai mica
  double max_diff;
  double max = matrice_omogena[0][0];
  double min = matrice_omogena[0][0];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      max = std::max(matrice_omogena[i][j], max);
      min = std::min(matrice_omogena[i][j], min);
    }
  max_diff = max - min;

  // construire matrice discordanta
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
    {
      if (i == j)
        continue;
      // calculam diferentele pe aceleasi criterii intre j si i
      std::vector<double> diff;
      for (int k = 0; k < m; k++)
      {
        const double diff_pe_criteriu = matrice_omogena[j][k] - matrice_omogena[i][k];
        diff.push_back( diff_pe_criteriu > 0 ? diff_pe_criteriu : 0);
      }
        

      // element in matricea discordanta
      matrice_discordanta[i][j] = *(std::max_element( diff.begin(), diff.end())) / max_diff;
    }
}

void algoritm::surclasare()
{
  std::sort(alternative.begin(), alternative.end(),
    [this](const alternativa &a1, const alternativa &a2) -> bool
    {
      int i = a1.idx;
      int j = a2.idx;
      return matrice_concordanta[i][j] - matrice_discordanta[i][j] > matrice_concordanta[j][i]  - matrice_discordanta[j][i];
    }
  );
}