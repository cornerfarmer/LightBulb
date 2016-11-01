#pragma once

#ifndef _STOCHASTICUNIVERSALSAMPLINGSELECTOR_H_
#define _STOCHASTICUNIVERSALSAMPLINGSELECTOR_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "Function/SelectionFunction/AbstractSelectionFunction.hpp"
#include <memory>

namespace LightBulb
{
	// Forward declarations

	// A command which selects the best N objects for mutation/recombination
	class StochasticUniversalSamplingSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
	{
	private:
		std::unique_ptr<AbstractSelectionFunction> randomFunction;
		void select(bool recombine, int objectCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore);
	protected:
		void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
		void selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
	public:
		StochasticUniversalSamplingSelector();
		StochasticUniversalSamplingSelector(const StochasticUniversalSamplingSelector& other);
		StochasticUniversalSamplingSelector(StochasticUniversalSamplingSelector&& other) noexcept;
		StochasticUniversalSamplingSelector& operator=(StochasticUniversalSamplingSelector other);
		friend void swap(StochasticUniversalSamplingSelector& lhs, StochasticUniversalSamplingSelector& rhs) noexcept;

		void setRandomFunction(AbstractSelectionFunction* randomFunction_);
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
