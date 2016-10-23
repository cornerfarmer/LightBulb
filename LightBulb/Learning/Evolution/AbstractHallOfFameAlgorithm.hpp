#pragma once

#ifndef _ABSTRACTHALLOFFAMEALGORITHM_H_
#define _ABSTRACTHALLOFFAMEALGORITHM_H_

// Library Includes
#include <vector>
#include <map>

// Include
#include "Logging/AbstractLoggable.hpp"
#include "AbstractEvolutionObject.hpp"
#include "AbstractCombiningStrategy.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractCoevolutionWorld;

	class AbstractHallOfFameAlgorithm : public AbstractLoggable
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractHallOfFameAlgorithm& hallOfFameAlgorithm);
	private:
		CombiningStrategyResults* currentResults;
	protected:
		AbstractCoevolutionWorld* currentWorld;
		std::vector<std::unique_ptr<AbstractEvolutionObject>> members;
		void simulateAgainstMember(AbstractEvolutionObject& object, int memberID, int round);
		virtual void evaluateObjects(std::vector<AbstractEvolutionObject*>& objects) = 0;
	public:
		virtual void execute(AbstractCoevolutionWorld& world, const CombiningStrategyResults& prevResults);
		virtual void addMember(AbstractEvolutionObject* newMember);
	};
}

#include "IO/AbstractHallOfFameAlgorithmIO.hpp"

#endif
