// Includes
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
//Library include
#include <algorithm>

std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> AbstractEvolutionWorld::getHighscoreList()
{
	std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> list(new std::vector<std::pair<double, AbstractEvolutionObject*>>(getEvolutionObjects()->size()));
	int listIndex = 0;
	for (auto object = getEvolutionObjects()->begin(); object < getEvolutionObjects()->end(); object++)
	{		
		(*list)[listIndex++] = std::make_pair(getScore(*object), *object);
	}
	std::sort(list->begin(), list->end(), std::greater<std::pair<double, AbstractEvolutionObject*>>());
	return list;
}
