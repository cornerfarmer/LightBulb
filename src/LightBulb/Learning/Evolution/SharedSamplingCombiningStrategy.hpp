#pragma once

#ifndef _SHAREDSAMPLINGCOMBININGSTRATEGY_H_
#define _SHAREDSAMPLINGCOMBININGSTRATEGY_H_

// Library Includes
#include <map>
#include <vector>

// Include
#include "Learning/Evolution/AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	/**
	 * \brief A combining strategy which tries to find bunch of parasites which represent all different types of objects.
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
	private:
		/**
		* \brief Determines the number of competitions per object.
		*/
		int amountOfCompetitionsPerObject;
		/**
		 * \brief Contains the combining strategy of the parasite population.
		 */
		const AbstractCombiningStrategy* otherCombiningStrategy;
		// Inherited:
		void combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractEvolutionObject*>& firstObjects, std::vector<AbstractEvolutionObject*>& secondObjects) override;
	public:
		/**
		 * \brief Creates the shared sampling combining strategy.
		 * \param amountOfCompetitionsPerObject_ Determines the number of competitions per object.
		 * \param secondWorld_ The other world.
		 */
		SharedSamplingCombiningStrategy(int amountOfCompetitionsPerObject_ = 0, AbstractCoevolutionWorld* secondWorld_ = nullptr);
		// Inherited:
		void setSecondWorld(AbstractCoevolutionWorld& newSecondWorld) override;
		int getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const override;
	};
}

#endif
