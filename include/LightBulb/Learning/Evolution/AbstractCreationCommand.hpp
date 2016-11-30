#pragma once

#ifndef _ABSTRACTCREATIONCOMMAND_H_
#define _ABSTRACTCREATIONCOMMAND_H_

// Includes
#include "AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionEnvironment;
	/**
	 * \brief Describes a command which creates new individuals.
	 */
	class AbstractCreationCommand : public AbstractCommand
	{
	protected:
	public:
		virtual ~AbstractCreationCommand() {}
		/**
		 * \brief Creates new individuals and adds them to the given environment.
		 * \param environment The environment to use.
		 * \param notUsedIndividuals A vector of individuals which are not used anymore.
		 */
		virtual void execute(AbstractEvolutionEnvironment& environment, std::vector<AbstractIndividual*>& notUsedIndividuals) = 0;
	};
}

#endif
