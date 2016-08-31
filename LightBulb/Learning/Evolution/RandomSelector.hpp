#pragma once

#ifndef _RANDOMSELECTOR_H_
#define _RANDOMSELECTOR_H_

// Library Includes
#include <memory>

// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "Function/RandomFunction/AbstractRandomFunction.hpp"

// Forward declarations

//
class RandomSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
{
private:
	// Holds amount of objects which should be selected
	std::unique_ptr<AbstractRandomFunction> randomFunction;
protected:
	void selectForMutation(int mutationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
	void selectForRecombination(int recombinationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
public:
	RandomSelector(AbstractRandomFunction* randomFunction_);

	void setRandomGenerator(AbstractRandomGenerator* randomGenerator_);
};

#endif
