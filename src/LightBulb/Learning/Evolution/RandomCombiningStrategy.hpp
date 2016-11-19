#pragma once

#ifndef _RANDOMCOMBININGSTRATEGY_H_
#define _RANDOMCOMBININGSTRATEGY_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	/**
	 * \brief A combining strategy which chooses pairs randomly.
	 */
	class RandomCombiningStrategy : public AbstractCombiningStrategy
	{
		template <class Archive>
		friend void serialize(Archive& archive, RandomCombiningStrategy& randomCombiningStrategy);
	private:
		/**
		 * \brief Determines the number of competitions per individual.
		 */
		int amountOfCompetitionsPerIndividual;
		// Inherited:
		void combine(AbstractCoevolutionEnvironment& simulationEnvironment, std::vector<AbstractIndividual*>& firstIndividuals, std::vector<AbstractIndividual*>& secondIndividuals) override;
	public:
		/**
		 * \brief Creates a random combining strategy.
		 * \param amountOfCompetitionsPerIndividual_ Determines the number of competitions per individual.
		 */
		RandomCombiningStrategy(int amountOfCompetitionsPerIndividual_ = 0);
		// Inherited:
		int getTotalMatches(const AbstractCoevolutionEnvironment& simulationEnvironment) const override;
	};
}

#endif
