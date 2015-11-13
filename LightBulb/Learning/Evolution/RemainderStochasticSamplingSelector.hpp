#pragma once

#ifndef _REMAINDERSTOCHASTICSAMPLINGSELECTOR_H_
#define _REMAINDERSTOCHASTICSAMPLINGSELECTOR_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "Function/RouletteWheelSelectionFunction.hpp"

// Forward declarations

// A command which selects the best N objects for mutation/recombination
class RemainderStochasticSamplingSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
{
private:
	// Holds amount of objects which should be selected
	std::vector<AbstractEvolutionObject*> objectSequence;
	int currentObjectIndex;
	RouletteWheelSelectionFunction randomFunction;
public:
	void initMutation(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int mutationCount);
	AbstractEvolutionObject* nextMutation();
	void initRecombination(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, int recombinationCount);
	std::array<AbstractEvolutionObject*, 2> nextRecombination();
	bool hasFinished();
};

#endif
