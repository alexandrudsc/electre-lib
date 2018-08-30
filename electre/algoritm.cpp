#include <algorithm>
#include <numeric>

#include "algoritm.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// functii private
///////////////////////////////////////////////////////////////////////////////

void algoritm::initializare()
{
	alternative.clear();
	criterii.clear();
}

void algoritm::adauga_alternativa(const alternativa &a)
{
	alternative.push_back(a);
}

void algoritm::adauga_criteriu(const criteriu &c)
{
	criterii.push_back(c);
}

/**
 * Functia principala unde se executa algorimul
 * Initializarea trebuie facuta inainte
*/
void algoritm::ruleaza()
{
  // pasul 2
  normalizare();
  // pasul 3
  concordanta();
  // pasul 4
  discordanta();
  // pasul 5
  surclasare();
}

///////////////////////////////////////////////////////////////////////////////
// functii private
///////////////////////////////////////////////////////////////////////////////
algoritm::algoritm()
{
}


algoritm::~algoritm()
{
}

void algoritm::normalizare()
{
  int n = alternative.size();
  int m = criterii.size();
  // calculare patrate
  for (vector<double> &v : m_decizie)
	transform(v.begin(), v.end(), v.begin(), 
     [](double &x) { return x * x; });

  for (vector<double> &v : m_decizie)
  {
	// calculez radical din suma
	const double sum = accumulate(v.begin(), v.end(), 0.0);
	const double radical = sqrt(sum);
	// normalizare
	transform(v.begin(), v.end(), v.begin(),
	  [&radical](double &x) { return x / radical; });
  }

  // aplicare ponderi
  for (vector<double> &v : m_decizie)
  {
	transform(v.begin(), v.end(), v.begin(),
	  [&v, this](double &x) 
	  { size_t index = (&x - &v[0]);  return x * criterii[index].pondere; });
  }
}

void algoritm::concordanta()
{

}

void algoritm::discordanta()
{

}

void algoritm::surclasare()
{

}