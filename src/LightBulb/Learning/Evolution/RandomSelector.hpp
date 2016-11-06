#pragma once

#ifndef _RANDOMSELECTOR_H_
#define _RANDOMSELECTOR_H_

// Library Includes
#include <memory>

// Includes
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "Function/RandomFunction/AbstractRandomFunction.hpp"

namespace LightBulb
{
	// Forward declarations

	//
	class RandomSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
	{
	private:
		// Holds amount of objects which should be selected
		std::unique_ptr<AbstractRandomFunction> randomFunction;
	protected:
		void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
		void selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
	public:
		RandomSelector() = default;
		RandomSelector(AbstractRandomFunction* randomFunction_);
		RandomSelector(const RandomSelector& other);
		RandomSelector(RandomSelector&& other) noexcept;
		RandomSelector& operator=(RandomSelector other);

		friend void swap(RandomSelector& lhs, RandomSelector& rhs) noexcept;

		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;

		AbstractCloneable* clone() const override;
	};
}

#endif
