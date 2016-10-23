#pragma once

#ifndef _REMAINDERSTOCHASTICSAMPLINGSELECTOR_H_
#define _REMAINDERSTOCHASTICSAMPLINGSELECTOR_H_

// Library Includes
#include <memory>

// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "Function/SelectionFunction/AbstractSelectionFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	// A command which selects the best N objects for mutation/recombination
	class RemainderStochasticSamplingSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
	{
	private:
		std::unique_ptr<AbstractSelectionFunction> randomFunction;
		bool withReplacement;
		void select(bool recombination, int objectCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore);
	protected:
		void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
		void selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
	public:
		RemainderStochasticSamplingSelector(bool withReplacement_ = true);
		void setRandomFunction(AbstractSelectionFunction* randomFunction);
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
	};
}

#endif
