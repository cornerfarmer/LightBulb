// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationSelector.hpp"

namespace LightBulb
{
	void swap(AbstractMutationSelector& lhs, AbstractMutationSelector& rhs) noexcept
	{
		using std::swap;
		swap(lhs.selectedIndividuals, rhs.selectedIndividuals);
		swap(lhs.currentCounter, rhs.currentCounter);
	}

	void AbstractMutationSelector::addIndividualToMutate(AbstractIndividual& individual)
	{
		selectedIndividuals.push_back(&individual);
		(*currentCounter)[&individual]++;
	}

	void AbstractMutationSelector::executeMutationSelection(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter)
	{
		selectedIndividuals.clear();
		if (mutationCount > 0) {
			currentCounter = &counter;
			selectForMutation(mutationCount, highscore);
		}

		if (selectedIndividuals.size() != mutationCount)
			throw std::logic_error("The mutation selection was not successful");
	}

	std::vector<AbstractIndividual*>& AbstractMutationSelector::getMutationSelection()
	{
		return selectedIndividuals;
	}
}
