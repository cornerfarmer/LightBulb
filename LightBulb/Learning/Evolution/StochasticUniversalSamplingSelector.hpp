#pragma once

#ifndef _STOCHASTICUNIVERSALSAMPLINGSELECTOR_H_
#define _STOCHASTICUNIVERSALSAMPLINGSELECTOR_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "Function/RouletteWheelSelectionFunction.hpp"

// Forward declarations

// A command which selects the best N objects for mutation/recombination
class StochasticUniversalSamplingSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
{
private:
	RouletteWheelSelectionFunction randomFunction;
	void select(bool recombine, int objectCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
protected:
	void selectForMutation(int mutationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
	void selectForRecombination(int recombinationCount, std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
public:

};

#endif
