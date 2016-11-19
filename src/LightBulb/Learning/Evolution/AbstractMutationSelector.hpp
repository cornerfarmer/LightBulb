#pragma once

#ifndef _ABSTRACTMUTATIONSELECTOR_H_
#define _ABSTRACTMUTATIONSELECTOR_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"
#include "Tools/AbstractCloneable.hpp"

// Library includes
#include <vector>
#include <utility>
#include <map>

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	/**
	 * \brief Describes an algorithm which selects the individuals which will be mutated.
	 */
	class AbstractMutationSelector : public virtual AbstractCloneable, public virtual AbstractRandomGeneratorUser
	{
	private:
		/**
		 * \brief All selected individuals.
		 */
		std::vector<AbstractIndividual*> selectedIndividuals;
		/**
		 * \brief A counter which stores how often an individual is used in all commands.
		 */
		std::map<AbstractIndividual*, int>* currentCounter;
	protected:
		/**
		 * \brief Selects the given individual for mutation.
		 * \param individual The individual.
		 */
		virtual void addIndividualToMutate(AbstractIndividual& individual);
		/**
		 * \brief Executes the selection process.
		 * \param mutationCount Determines how many individuals should be mutated.
		 * \param highscore The current highscore.
		 */
		virtual void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) = 0;
	public:
		virtual ~AbstractMutationSelector() {}
		friend void swap(AbstractMutationSelector& lhs, AbstractMutationSelector& rhs) noexcept;
		/**
		 * \brief Executes the selection process.
		 * \param mutationCount Determines how many individuals should be mutated.
		 * \param highscore The current highscore.
		 * \param counter A counter which stores how often an individual is used in all commands.
		 */
		virtual void executeMutationSelection(int mutationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter);
		/**
		 * \brief Returns the last selection.
		 * \return A vector of all individuals which were selected for mutation.
		 */
		virtual std::vector<AbstractIndividual*>& getMutationSelection();
	};
}

#endif
