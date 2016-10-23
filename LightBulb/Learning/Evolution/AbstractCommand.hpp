#pragma once

#ifndef _ABSTRACTCOMMAND_H_
#define _ABSTRACTCOMMAND_H_

// Include
#include "Learning/Evolution/AbstractRecombinationAlgorithm.hpp"
#include "Logging/AbstractLoggable.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	class AbstractEvolutionWorld;
	class EvolutionLearningRule;

	// A command which combines a few of the given evolution objects.
	class AbstractCommand : public AbstractLoggable, public AbstractRandomGeneratorUser
	{
	protected:
		AbstractEvolutionObject& getUnusedObject(AbstractEvolutionObject& usedObject, std::vector<AbstractEvolutionObject*>& notUsedObjects, bool addToWorld = true) const;
	};
}

#endif

