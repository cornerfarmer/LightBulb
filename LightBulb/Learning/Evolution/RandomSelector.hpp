#pragma once

#ifndef _RANDOMSELECTOR_H_
#define _RANDOMSELECTOR_H_

// Library Includes
#include <memory>

// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "Function/AbstractRandomFunction.hpp"

// Forward declarations

//
class RandomSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
{
private:
	// Holds amount of objects which should be selected
	std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore;
	int objectsToDo;
	std::unique_ptr<AbstractRandomFunction> randomFunction;
public:
	RandomSelector(AbstractRandomFunction* randomFunction_);
	void initMutation(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore_, int mutationCount);
	AbstractEvolutionObject* nextMutation();
	void initRecombination(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int recombinationCount);
	std::array<AbstractEvolutionObject*, 2> nextRecombination();
	bool hasFinished();
};

#endif
