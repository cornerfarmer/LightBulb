#pragma once

#ifndef _ABSTRACTCOMBININGSTRATEGY_H_
#define _ABSTRACTCOMBININGSTRATEGY_H_

// Include
#include "Random/AbstractRandomGeneratorUser.hpp"

// Library Includes
#include <vector>
#include <memory>
#include <map>

namespace LightBulb
{
	// Forward declarations
	class AbstractCoevolutionWorld;
	class AbstractEvolutionObject;

	typedef std::map<AbstractEvolutionObject*, std::map<AbstractEvolutionObject*, std::map<int, bool>>> CombiningStrategyResults;

	class AbstractCombiningStrategy : public AbstractRandomGeneratorUser
	{
	private:
		std::unique_ptr<CombiningStrategyResults> results;
		int firstPlayerWins;
	protected:
		AbstractCoevolutionWorld* secondWorld;
		virtual void combine(AbstractCoevolutionWorld& simulationWorld, std::vector<AbstractEvolutionObject*>& firstObjects, std::vector<AbstractEvolutionObject*>& secondObjects) = 0;
		void setResult(AbstractEvolutionObject& firstPlayer, AbstractEvolutionObject& secondPlayer, int round, bool firstPlayerHasWon);
	public:
		AbstractCombiningStrategy(AbstractCoevolutionWorld* secondWorld_ = nullptr);
		virtual CombiningStrategyResults& execute(AbstractCoevolutionWorld& world);
		virtual void setSecondWorld(AbstractCoevolutionWorld& newSecondWorld);
		virtual CombiningStrategyResults& getPrevResults();
		virtual int getFirstPlayerWins() const;
		virtual int getTotalMatches(const AbstractCoevolutionWorld& simulationWorld) const = 0;
	};
}

#endif
