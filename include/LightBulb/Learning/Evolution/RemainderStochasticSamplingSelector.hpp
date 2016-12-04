#pragma once

#ifndef _REMAINDERSTOCHASTICSAMPLINGSELECTOR_H_
#define _REMAINDERSTOCHASTICSAMPLINGSELECTOR_H_

// Library Includes
#include <memory>

// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationSelector.hpp"
#include "LightBulb/Learning/Evolution/AbstractRecombinationSelector.hpp"
#include "LightBulb/Function/SelectionFunction/AbstractSelectionFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Selects individuals depending on their fitness value.
	 * \details First: Amount of selections per individual:  \n \f$ N = [\frac{fit(c)}{\sum{fit(c_i)}} * popsize]  \f$ \n \n
	 * Second: Selects the left places by random selection depending on the fitness values.
	 * \note If replacement is enabled, the probabilities in the second step are decreased depending on N of the first step.
	 */
	class RemainderStochasticSamplingSelector : public AbstractMutationSelector, public AbstractRecombinationSelector
	{
	private:
		/**
		 * \brief The random function which should be used.
		 */
		std::unique_ptr<AbstractSelectionFunction> selectionFunction;
		/**
		 * \brief True, if probabilities in the second step should be decreased depending on N of the first step.
		 */
		bool withReplacement;
		/**
		 * \brief Executes selection.
		 * \param recombination True, if a selection for recombination should be executed.
		 * \param individualCount The amount of individuals to select.
		 * \param highscore The current highscore.
		 */
		void select(bool recombination, int individualCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore);
	protected:
		// Inherited:
		void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		void selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
	public:
		/**
		 * \brief Creates a new remainder stochastic sampling selector.
		 * \param withReplacement_ True, if probabilities in the second step should be decreased depending on N of the first step.
		 * \param selectionFunction The selectionFunction which should be used.
		 */
		RemainderStochasticSamplingSelector(bool withReplacement_ = true, AbstractSelectionFunction* selectionFunction = nullptr);
		RemainderStochasticSamplingSelector(const RemainderStochasticSamplingSelector& other);
		RemainderStochasticSamplingSelector(RemainderStochasticSamplingSelector&& other) noexcept;
		RemainderStochasticSamplingSelector& operator=(RemainderStochasticSamplingSelector other);
		friend void swap(RemainderStochasticSamplingSelector& lhs, RemainderStochasticSamplingSelector& rhs) noexcept;
		// Inherited:
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
