// Includes
#include "LightBulb/Learning/Evolution/BestReuseSelector.hpp"

namespace LightBulb
{
	void BestReuseSelector::selectForReuse(int reuseCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore)
	{
		for (int i = 0; i < reuseCount; i++)
		{
			addIndividualToReuse(*highscore[i].second);
		}
	}

	AbstractCloneable* BestReuseSelector::clone() const
	{
		return new BestReuseSelector(*this);
	}
}
