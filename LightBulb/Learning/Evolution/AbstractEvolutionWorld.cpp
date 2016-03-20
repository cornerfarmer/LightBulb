// Includes
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
//Library include
#include <algorithm>
#include <functional>

bool AbstractEvolutionWorld::compareHighscoreEntries(const std::pair<double, AbstractEvolutionObject*>& x, const std::pair<double, AbstractEvolutionObject*>& y)
{
	return x.first > y.first || (x.first == y.first && rand() > RAND_MAX / 2);
}

std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> AbstractEvolutionWorld::getHighscoreList()
{
	// Create new vector which should return the whole highscore
	std::unique_ptr<std::vector<std::pair<double, AbstractEvolutionObject*>>> list(new std::vector<std::pair<double, AbstractEvolutionObject*>>(getEvolutionObjects()->size()));
	// Go through all evolution objects
	int listIndex = 0;
	for (auto object = getEvolutionObjects()->begin(); object < getEvolutionObjects()->end(); object++)
	{		
		double score = getScore(*object);

		// Add the objects paired with its score to the list
		(*list)[listIndex++] = std::make_pair(score, *object);

	}
	// Sort the list
	std::sort(list->begin(), list->end(), std::greater<std::pair<double, AbstractEvolutionObject*>>());
	return list;
}
