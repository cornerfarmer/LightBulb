#pragma once

#ifndef _ABSTRACTRECOMBINATIONCOMMAND_H_
#define _ABSTRACTRECOMBINATIONCOMMAND_H_

// Library Includes
#include <vector>
#include <memory>

// Includes
#include "LightBulb/Learning/Evolution/AbstractCommand.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	class AbstractEvolutionEnvironment;
	class EvolutionLearningRule;
	class AbstractRecombinationAlgorithm;
	class AbstractRecombinationSelector;
	/**
	 * \brief A command which recombines a few of the given individuals.
	 */
	class AbstractRecombinationCommand : public AbstractCommand
	{
	protected:
		/**
		 * \brief The algorithm which executes the recombination.
		 */
		std::unique_ptr<AbstractRecombinationAlgorithm> recombinationAlgorithm;
		/**
		 * \brief The algorithm which selects individuals for recombination.
		 */
		std::unique_ptr<AbstractRecombinationSelector> recombinationSelector;
	public:
		~AbstractRecombinationCommand();
		AbstractRecombinationCommand();
		AbstractRecombinationCommand(const AbstractRecombinationCommand& other);
		friend void swap(AbstractRecombinationCommand& lhs, AbstractRecombinationCommand& rhs) noexcept;
		/**
		 * \brief Creates a new recombination command.
		 * \param recombinationAlgorithm_ The recombination algorithm to use.
		 * \param recombinationSelector_ The recombination selector to use.
		 */
		AbstractRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_);
		/**
		* \brief Select individuals for recombination.
		* \param highscore The current highscore.
		* \param counter A counter which stores how often an individual is used in all commands.
		*/
		virtual void select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter) = 0;
		/**
		* \brief Executes the recombination.
		* \details The algorithm will take a few of the old individuals, recombine them and insert them into the new individual vector
		* \param newIndividualVector A vector where the new/recombinated individuals will be stored in.
		* \param counter A counter of all left operations per individual.
		* \param notUsedIndividuals A vector of individuals which are not used anymore.
		*/
		virtual void execute(std::vector<AbstractIndividual*>& newIndividualVector, std::map<AbstractIndividual*, int>& counter, std::vector<AbstractIndividual*>& notUsedIndividuals);
		// Inherited:
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
		void setCalculatorType(const CalculatorType& calculatorType) override;
	};
}

#endif
