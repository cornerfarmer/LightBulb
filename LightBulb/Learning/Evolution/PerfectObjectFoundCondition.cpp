// Includes
#include "Learning/Evolution/PerfectObjectFoundCondition.hpp"
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"
// Library includes
#include <iostream>
#include <iomanip>

bool PerfectObjectFoundCondition::evaluate(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	if (highscore->size() > 0)
	{
		if (perfectObjectExists())
		{
			counter++;
			if (counter > count)
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
bool PerfectObjectFoundCondition::perfectObjectExists()
{
	auto results = combiningStrategy->getPrevResults();
	std::map<AbstractEvolutionObject*, bool> defeatedObjects;

	for (auto resultsPerObject = results->begin(); resultsPerObject != results->end(); resultsPerObject++)
	{
		for (auto result = resultsPerObject->second.begin(); result != resultsPerObject->second.end(); result++)
		{
			defeatedObjects[result->first] |= result->second;
		}
	}

	for (auto defeatedObject = defeatedObjects.begin(); defeatedObject != defeatedObjects.end(); defeatedObject++)
	{
		if (!defeatedObject->second)
			return true;
	}
	return false;
}

PerfectObjectFoundCondition::PerfectObjectFoundCondition(int count_, AbstractCombiningStrategy* combiningStrategy_, bool enableDebugOutput_)
	: AbstractExitCondition(enableDebugOutput_)
{
	combiningStrategy = combiningStrategy_;
	counter = 0;
	count = count_;
}

void PerfectObjectFoundCondition::setCount(int newCount)
{
	count = newCount;
}
