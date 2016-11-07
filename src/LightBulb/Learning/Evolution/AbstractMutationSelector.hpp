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
	class AbstractEvolutionObject;
	/**
	 * \brief Describes an algorithm which selects the objects which will be mutated.
	 */
	class AbstractMutationSelector : public virtual AbstractCloneable, public virtual AbstractRandomGeneratorUser
	{
	private:
		/**
		 * \brief All selected objects.
		 */
		std::vector<AbstractEvolutionObject*> selectedObjects;
		/**
		 * \brief A counter which stores how often an object is used in all commands.
		 */
		std::map<AbstractEvolutionObject*, int>* currentCounter;
	protected:
		/**
		 * \brief Selects the given object for mutation.
		 * \param object The object.
		 */
		virtual void addObjectToMutate(AbstractEvolutionObject& object);
		/**
		 * \brief Executes the selection process.
		 * \param mutationCount Determines how many objects should be mutated.
		 * \param highscore The current highscore.
		 */
		virtual void selectForMutation(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) = 0;
	public:
		virtual ~AbstractMutationSelector() {}
		friend void swap(AbstractMutationSelector& lhs, AbstractMutationSelector& rhs) noexcept;
		/**
		 * \brief Executes the selection process.
		 * \param mutationCount Determines how many objects should be mutated.
		 * \param highscore The current highscore.
		 * \param counter A counter which stores how often an object is used in all commands.
		 */
		virtual void executeMutationSelection(int mutationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter);
		/**
		 * \brief Returns the last selection.
		 * \return A vector of all objects which were selected for mutation.
		 */
		virtual std::vector<AbstractEvolutionObject*>& getMutationSelection();
	};
}

#endif
