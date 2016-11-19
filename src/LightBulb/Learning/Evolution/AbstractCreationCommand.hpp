#pragma once

#ifndef _ABSTRACTCREATIONCOMMAND_H_
#define _ABSTRACTCREATIONCOMMAND_H_

// Includes
#include "AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionWorld;
	/**
	 * \brief Describes a command which creates new individuals.
	 */
	class AbstractCreationCommand : public AbstractCommand
	{
	protected:
	public:
		virtual ~AbstractCreationCommand() {}
		/**
		 * \brief Creates new individuals and adds them to the given world.
		 * \param world The world to use.
		 * \param notUsedIndividuals A vector of individuals which are not used anymore.
		 */
		virtual void execute(AbstractEvolutionWorld& world, std::vector<AbstractIndividual*>& notUsedIndividuals) = 0;
	};
}

#endif
