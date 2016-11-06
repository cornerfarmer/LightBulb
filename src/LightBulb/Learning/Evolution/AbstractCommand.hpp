#pragma once

#ifndef _ABSTRACTCOMMAND_H_
#define _ABSTRACTCOMMAND_H_

// Include
#include "Learning/Evolution/AbstractRecombinationAlgorithm.hpp"
#include "Logging/AbstractLoggable.hpp"
#include "Tools/AbstractCloneable.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	class AbstractEvolutionWorld;
	class EvolutionLearningRule;
	/**
	 * \brief Describes a command which is executes in the evolution learning process.
	 */
	class AbstractCommand : public AbstractLoggable, public AbstractRandomGeneratorUser, public virtual AbstractCloneable
	{
	protected:
		/**
		 * \brief Returns an editable object which is clone of the given used object.
		 * \param usedObject The object which should be cloned.
		 * \param notUsedObjects A vector of objects which are not used any more.
		 * \param addToWorld True if new created objects should be added to the world.
		 * \return The editable object.
		 */
		AbstractEvolutionObject* getUnusedObject(AbstractEvolutionObject& usedObject, std::vector<AbstractEvolutionObject*>& notUsedObjects, bool addToWorld = true) const;

		friend void swap(AbstractCommand& lhs, AbstractCommand& rhs) noexcept;
	};
}

#endif

