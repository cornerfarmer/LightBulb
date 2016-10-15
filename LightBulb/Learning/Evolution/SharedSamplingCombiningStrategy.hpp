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
	// Forward declarations

	class SharedSamplingCombiningStrategy : public AbstractCombiningStrategy
	{
		template <class Archive>
		friend void serialize(Archive& archive, SharedSamplingCombiningStrategy& sharedSamplingCombiningStrategy);
	private:
		int amountOfCompetitionsPerObject;
		AbstractCombiningStrategy* otherCombiningStrategy;
		void combine(AbstractCoevolutionWorld* simulationWorld, std::vector<AbstractEvolutionObject*>* firstObjects, std::vector<AbstractEvolutionObject*>* secondObjects) override;
	public:
		void setSecondWorld(AbstractCoevolutionWorld* newSecondWorld) override;
		SharedSamplingCombiningStrategy(int amountOfCompetitionsPerObject_ = 0, AbstractCoevolutionWorld* secondWorld_ = nullptr);
		int getTotalMatches(AbstractCoevolutionWorld* simulationWorld) override;
	};
}

#endif
