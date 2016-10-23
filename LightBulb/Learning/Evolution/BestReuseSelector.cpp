// Includes
#include "Learning/Evolution/BestReuseSelector.hpp"

namespace LightBulb
{
	void BestReuseSelector::selectForReuse(int reuseCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		for (int i = 0; i < reuseCount; i++)
		{
			addObjectToReuse(*highscore[i].second);
		}
	}
}