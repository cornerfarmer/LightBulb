// Includes
#include "Learning/Evolution/BestReuseSelector.hpp"

void BestReuseSelector::selectForReuse(int reuseCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	for (int i = 0; i < reuseCount; i++)
	{
		addObjectToReuse((*highscore)[i].second);
	}
}
