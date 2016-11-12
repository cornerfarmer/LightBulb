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
		 * \brief Determines the number of competitions per object.
		 */
		int amountOfCompetitionsPerObject;
		// Inherited:
		void combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractEvolutionObject*>& firstObjects, std::vector<AbstractEvolutionObject*>& secondObjects) override;
	public:
		/**
		 * \brief Creates a random combining strategy.
		 * \param amountOfCompetitionsPerObject_ Determines the number of competitions per object.
		 */
		RandomCombiningStrategy(int amountOfCompetitionsPerObject_ = 0);
		// Inherited:
		int getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const override;
	};
}

#endif
