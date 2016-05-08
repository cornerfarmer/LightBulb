// Includes
#include "Learning/Evolution/PerfectObjectFoundCondition.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
// Library includes
#include <iostream>
#include <iomanip>
#include "EvolutionLearningRule.hpp"
#include "AbstractCoevolutionWorld.hpp"

bool PerfectObjectFoundCondition::evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, AbstractEvolutionLearningRule* learningRule)
{
	if (highscore->size() > 0)
	{
		AbstractCoevolutionWorld* coevolutionWorld = static_cast<AbstractCoevolutionWorld*>(static_cast<EvolutionLearningRule*>(learningRule)->getWorld());
		if (coevolutionWorld->isParasiteWorld() && perfectObjectExists(coevolutionWorld->getCombiningStrategy()))
		{
			counter++;
			if (counter >= count)
				return true;
		}
		else
		{
			counter = 0;
		}
		return false;
	}
	else
	{
		return false;
	}
}
bool PerfectObjectFoundCondition::perfectObjectExists(AbstractCombiningStrategy* combiningStrategy)
{
	auto results = combiningStrategy->getPrevResults();
	std::map<AbstractEvolutionObject*, bool> defeatedObjects;

	for (auto resultsPerObject = results->begin(); resultsPerObject != results->end(); resultsPerObject++)
	{
		for (auto resultsPerCombination = resultsPerObject->second.begin(); resultsPerCombination != resultsPerObject->second.end(); resultsPerCombination++)
		{
			for (auto result = resultsPerCombination->second.begin(); result != resultsPerCombination->second.end(); result++)
			{
				defeatedObjects[resultsPerCombination->first] |= result->second;
			}
		}
	}

	for (auto defeatedObject = defeatedObjects.begin(); defeatedObject != defeatedObjects.end(); defeatedObject++)
	{
		if (!defeatedObject->second)
			return true;
	}
	return false;
}

PerfectObjectFoundCondition::PerfectObjectFoundCondition(int count_)
	: AbstractExitCondition()
{
	counter = 0;
	count = count_;
}

void PerfectObjectFoundCondition::setCount(int newCount)
{
	count = newCount;
}
