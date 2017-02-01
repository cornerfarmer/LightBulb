// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/AbstractReuseSelector.hpp"

namespace LightBulb
{
	void AbstractReuseSelector::addIndividualToReuse(AbstractIndividual& individual)
	{
		selectedIndividuals.push_back(&individual);
		(*currentCounter)[&individual]++;
	}

	void AbstractReuseSelector::executeReuseSelection(int reuseCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter)
	{
		selectedIndividuals.clear();
		if (reuseCount > 0) {
			currentCounter = &counter;
			selectForReuse(reuseCount, highscore);
		}
		if (selectedIndividuals.size() != reuseCount)
			throw std::logic_error("The reuse selection was not successful");
	}

	const std::vector<AbstractIndividual*>& AbstractReuseSelector::getReuseSelection() const
	{
		return selectedIndividuals;
	}
}