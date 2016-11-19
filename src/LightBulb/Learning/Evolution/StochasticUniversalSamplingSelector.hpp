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
	/**
	 * \brief Executes a roullete wheel selection.
	 * \details The roullete wheel is divided into different parts (one per individual) depending on their fitness values.
	 * Then all 360/popsize degrees a marker is set. Now the individuals on whose parts the marker point are chosen.
	 */
	class StochasticUniversalSamplingSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
	{
	private:
		/**
		* \brief The selection function which should be used.
		*/
		std::unique_ptr<AbstractSelectionFunction> selectionFunction;
		/**
		* \brief Executes selection.
		* \param recombine True, if a selection for recombination should be executed.
		* \param individualCount The amount of individuals to select.
		* \param highscore The current highscore.
		*/
		void select(bool recombine, int individualCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore);
	protected:
		// Inherited:
		void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		void selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
	public:
		StochasticUniversalSamplingSelector() = default;
		/**
		 * \brief The stochastic universal sampling selector.
		 * \param selectionFunction_ The selection function which should be used.
		 */
		StochasticUniversalSamplingSelector(AbstractSelectionFunction* selectionFunction_);
		StochasticUniversalSamplingSelector(const StochasticUniversalSamplingSelector& other);
		StochasticUniversalSamplingSelector(StochasticUniversalSamplingSelector&& other) noexcept;
		StochasticUniversalSamplingSelector& operator=(StochasticUniversalSamplingSelector other);
		friend void swap(StochasticUniversalSamplingSelector& lhs, StochasticUniversalSamplingSelector& rhs) noexcept;
		// Inherited:
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
