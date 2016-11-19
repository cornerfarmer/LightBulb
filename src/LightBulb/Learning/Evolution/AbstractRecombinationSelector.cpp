// Includes
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"

namespace LightBulb
{
	void AbstractRecombinationSelector::addIndividualToRecombination(AbstractIndividual& individual)
	{
		selectedIndividuals.push_back(&individual);
		(*currentCounter)[&individual]++;
	}

	void AbstractRecombinationSelector::executeRecombinationSelection(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter)
	{
		selectedIndividuals.clear();
		if (recombinationCount > 0) {
			currentCounter = &counter;

			selectForRecombination(recombinationCount, highscore);
		}

		if (selectedIndividuals.size() != recombinationCount * 2)
			throw std::logic_error("The recombination selection was not successful");
	}

	std::vector<AbstractIndividual*>& AbstractRecombinationSelector::getRecombinationSelection()
	{
		return selectedIndividuals;
	}

	void swap(AbstractRecombinationSelector& lhs, AbstractRecombinationSelector& rhs) noexcept
	{
		using std::swap;
		swap(lhs.selectedIndividuals, rhs.selectedIndividuals);
		swap(lhs.currentCounter, rhs.currentCounter);
	}
}
