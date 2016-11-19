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
	class AbstractIndividual;
	class AbstractEvolutionWorld;
	class EvolutionLearningRule;
	/**
	 * \brief Describes a command which is executes in the evolution learning process.
	 */
	class AbstractCommand : public AbstractLoggable, public virtual AbstractRandomGeneratorUser, public virtual AbstractCloneable
	{
	protected:
		/**
		 * \brief Returns an editable individual which is clone of the given used individual.
		 * \param usedIndividual The individual which should be cloned.
		 * \param notUsedIndividuals A vector of individual which are not used any more.
		 * \param addToWorld True if new created individual should be added to the world.
		 * \return The editable individual.
		 */
		AbstractIndividual* getUnusedIndividual(AbstractIndividual& usedIndividual, std::vector<AbstractIndividual*>& notUsedIndividuals, bool addToWorld = true) const;

		friend void swap(AbstractCommand& lhs, AbstractCommand& rhs) noexcept;
	};
}

#endif

