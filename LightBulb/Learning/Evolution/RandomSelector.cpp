// Includes
#include <Learning/Evolution/RandomSelector.hpp>
//Library includes
#include <iostream>
#include <iomanip>
#include <stdexcept>

RandomSelector::RandomSelector(AbstractRandomFunction* randomFunction_)
{
	randomFunction.reset(randomFunction_);
	objectsToDo = 0;
	highscore = NULL;
}

void RandomSelector::initMutation(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore_, int mutationCount)
{
	highscore = highscore_;
	objectsToDo = mutationCount;
}

AbstractEvolutionObject* RandomSelector::nextMutation()
{
	if (objectsToDo-- <= 0)
		throw std::logic_error("The randomSelector has to select more objects than it should!");

	return (*highscore)[randomFunction->execute(highscore->size())].second;
}

void RandomSelector::initRecombination(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int recombinationCount)
{
	initMutation(highscore, recombinationCount * 2);
}

std::array<AbstractEvolutionObject*, 2> RandomSelector::nextRecombination()
{
	std::array<AbstractEvolutionObject*, 2> arr;
	arr[0] = nextMutation();
	arr[1] = nextMutation();
	return arr;
}

bool RandomSelector::hasFinished()
{
	return objectsToDo == 0;
}
