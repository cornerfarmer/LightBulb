#pragma once

#ifndef _SHAREDSAMPLINGCOMBININGSTRATEGY_H_
#define _SHAREDSAMPLINGCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>

// Include
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	/**
	 * \brief A combining strategy which tries to find bunch of parasites which represent all different types of individuals.
	 * \details This makes the lost information when not using all parasites minimal.\n
	 * The algorithm:\n\n
	 * 1. Calculate for each parasite \f$p\f$:\n
	 * \t \f$ v_p = \sum{\frac{1}{1 + l[o]}}  \f$\n
	 * \t Where \f$o\f$ are all opponents that lost against \f$p\f$.\n\n
	 * 2. Then add \f$p_{min}\f$ with \f$min(v_p)\f$ to the sample.\n\n
	 * 3. Now for every opponent which lost against \f$p_{min}\f$:\n
	 * \t \f$ l[o] = l[o] + 1 \f$\n\n
	 * 4. Now start again.
	 */
	class SharedSamplingCombiningStrategy : public AbstractCombiningStrategy
	{
		template <class Archive>
		friend void serialize(Archive& archive, SharedSamplingCombiningStrategy& sharedSamplingCombiningStrategy);
	protected:
		/**
		* \brief Determines the number of competitions per individual.
		*/
		int amountOfCompetitionsPerIndividual;
		/**
		 * \brief Contains the combining strategy of the parasite population.
		 */
		const AbstractCombiningStrategy* otherCombiningStrategy;
		/**
		 * \brief Combines every individual from the given pool with every individual from the given sample.
		 * \param simulationEnvironment The environment which should be used for comparing individuals.
		 * \param firstIndividuals The pool of individuals.
		 * \param sample The sample.
		 */
		virtual void executeSample(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& sample);
		// Inherited:
		void combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals) override;		
	public:
		/**
		 * \brief Creates the shared sampling combining strategy.
		 * \param amountOfCompetitionsPerIndividual_ Determines the number of competitions per individual.
		 * \param secondEnvironment_ The other environment.
		 */
		SharedSamplingCombiningStrategy(int amountOfCompetitionsPerIndividual_ = 0, AbstractCoevolutionEnvironment* secondEnvironment_ = nullptr);
		// Inherited:
		void setSecondEnvironment(AbstractCoevolutionEnvironment& newSecondEnvironment) override;
		int getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const override;
	};
}

#endif
