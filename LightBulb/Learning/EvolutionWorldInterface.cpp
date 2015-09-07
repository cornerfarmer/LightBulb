// Includes
#include "Learning\EvolutionWorldInterface.hpp"
//Library include
#include <algorithm>

std::unique_ptr<std::vector<std::pair<double, EvolutionObjectInterface*>>> EvolutionWorldInterface::getHighscoreList()
{
	std::unique_ptr<std::vector<std::pair<double, EvolutionObjectInterface*>>> list(new std::vector<std::pair<double, EvolutionObjectInterface*>>(getEvolutionObjects()->size()));
	int listIndex = 0;
	for (auto object = getEvolutionObjects()->begin(); object < getEvolutionObjects()->end(); object++)
	{		
		(*list)[listIndex++] = std::make_pair<double, EvolutionObjectInterface*>(getScore(*object), *object);
	}
	std::sort(list->begin(), list->end(), std::greater<std::pair<double, EvolutionObjectInterface*>>());
	return list;
}