// Includes
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"


void AbstractRecombinationSelector::addObjectToRecombination(AbstractEvolutionObject* object)
{
	selectedObjects.push_back(object);
	(*currentCounter)[object]["recombine"]++;
}

void AbstractRecombinationSelector::executeRecombinationSelection(int recombinationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter)
{
	selectedObjects.clear();
	if (recombinationCount > 0) {
		currentCounter = counter;

		selectForRecombination(recombinationCount, highscore);
	}

	if (selectedObjects.size() != recombinationCount * 2)
		throw std::logic_error("The recombination selection was not successful");
}

std::vector<AbstractEvolutionObject*>* AbstractRecombinationSelector::getRecombinationSelection()
{
	return &selectedObjects;
}
