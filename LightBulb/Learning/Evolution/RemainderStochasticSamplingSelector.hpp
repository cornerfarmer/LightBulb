#pragma once

#ifndef _REMAINDERSTOCHASTICSAMPLINGSELECTOR_H_
#define _REMAINDERSTOCHASTICSAMPLINGSELECTOR_H_

// Library Includes
#include <memory>

// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "Function/SelectionFunction/AbstractSelectionFunction.hpp"

// Forward declarations

// A command which selects the best N objects for mutation/recombination
class RemainderStochasticSamplingSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
{
private:
	std::unique_ptr<AbstractSelectionFunction> randomFunction;
	bool withReplacement;
	void select(bool recombination, int objectCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
protected:
	void selectForMutation(int mutationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
	void selectForRecombination(int recombinationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
public:
	RemainderStochasticSamplingSelector(bool withReplacement_ = true);
	void setRandomFunction(AbstractSelectionFunction* randomFunction);
	void setRandomGenerator(AbstractRandomGenerator* randomGenerator_);
};

#endif
