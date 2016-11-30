#pragma once

#ifndef _ABSTRACTSELECTIONCOMMAND_H_
#define _ABSTRACTSELECTIONCOMMAND_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	class AbstractEvolutionEnvironment;
	class EvolutionLearningRule;
	/**
	 * \brief A command that selects a few of the individuals which will be forwarded to the mutation, recombination and reuse commands.
	 */
	class AbstractSelectionCommand : public AbstractCommand
	{
	protected:
	public:
		virtual ~AbstractSelectionCommand() {}
		/**
		 * \brief The command will delete all not-selected individuals from the vector.
		 * \param highscore The highscore.
		 * \param individuals A vector where all selected individuals will be stored in.
		 * \param notUsedIndividuals A vector where all not selected individuals will be stored in.
		 */
		virtual void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::vector<AbstractIndividual*>& individuals, std::vector<AbstractIndividual*>& notUsedIndividuals) = 0;
	};
}

#endif
