// Includes
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"

namespace LightBulb
{
	void AbstractRecombinationSelector::addObjectToRecombination(AbstractEvolutionObject& object)
	{
		selectedObjects.push_back(&object);
		(*currentCounter)[&object]++;
	}

	void AbstractRecombinationSelector::executeRecombinationSelection(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter)
	{
		selectedObjects.clear();
		if (recombinationCount > 0) {
			currentCounter = &counter;

			selectForRecombination(recombinationCount, highscore);
		}

		if (selectedObjects.size() != recombinationCount * 2)
			throw std::logic_error("The recombination selection was not successful");
	}

	std::vector<AbstractEvolutionObject*>& AbstractRecombinationSelector::getRecombinationSelection()
	{
		return selectedObjects;
	}

	void swap(AbstractRecombinationSelector& lhs, AbstractRecombinationSelector& rhs) noexcept
	{
		using std::swap;
		swap(lhs.selectedObjects, rhs.selectedObjects);
		swap(lhs.currentCounter, rhs.currentCounter);
	}
}
