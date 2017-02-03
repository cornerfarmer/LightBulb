#pragma once

#ifndef _RANDOMSELECTOR_H_
#define _RANDOMSELECTOR_H_

// Library Includes
#include <memory>

// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationSelector.hpp"
#include "LightBulb/Learning/Evolution/AbstractRecombinationSelector.hpp"

namespace LightBulb
{
	class AbstractRandomFunction;
	/**
	 * \brief A selector which selects individuals with a random function.
	 */
	class RandomSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
	{
	private:
		/**
		 * \brief The random function which should be used for selecting individuals.
		 */
		std::unique_ptr<AbstractRandomFunction> randomFunction;
	protected:
		// Inherited:
		void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		void selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
	public:
		RandomSelector() = default;
		RandomSelector(const RandomSelector& other);
		RandomSelector(RandomSelector&& other) noexcept;
		RandomSelector& operator=(RandomSelector other);
		friend void swap(RandomSelector& lhs, RandomSelector& rhs) noexcept;
		/**
		 * \brief Creates a random selector.
		 * \param randomFunction_ The random function which should be used.
		 */
		RandomSelector(AbstractRandomFunction* randomFunction_);
		// Inherited:
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
