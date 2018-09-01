#pragma once
#include <string>
#include <vector>

#include "criteriu.hpp"

class alternativa
{
public:
	::std::string nume;
	std::vector<double> valori_criterii{};
  size_t idx;
	alternativa();
	~alternativa();
};

