// Includes
#include "Learning/Evolution/AbstractReuseSelector.hpp"

namespace LightBulb
{
	void AbstractReuseSelector::addObjectToReuse(AbstractEvolutionObject* object)
	{
		selectedObjects.push_back(object);
		(*currentCounter)[object]++;
	}

	void AbstractReuseSelector::executeReuseSelection(int reuseCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, int>* counter)
	{
		selectedObjects.clear();
		if (reuseCount > 0) {
			currentCounter = counter;
			selectForReuse(reuseCount, highscore);
		}
		if (selectedObjects.size() != reuseCount)
			throw std::logic_error("The reuse selection was not successful");
	}

	std::vector<AbstractEvolutionObject*>* AbstractReuseSelector::getReuseSelection()
	{
		return &selectedObjects;
	}
}