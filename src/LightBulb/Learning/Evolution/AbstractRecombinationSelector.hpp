#pragma once

#ifndef _ABSTRACTRECOMBINATIONSELECTOR_H_
#define _ABSTRACTRECOMBINATIONSELECTOR_H_

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
	* \brief Describes an algorithm which selects the objects which will be recombined.
	*/
	class AbstractRecombinationSelector : public virtual AbstractCloneable, public virtual AbstractRandomGeneratorUser
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
		* \brief Selects the given object for recombination.
		* \param object The object.
		*/
		virtual void addObjectToRecombination(AbstractEvolutionObject& object);
		/**
		* \brief Executes the selection process.
		* \param recombinationCount Determines how many objects should be created by recombination. (=> 2x recombinationCount objects will be recombined)
		* \param highscore The current highscore.
		*/
		virtual void selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) = 0;
	public:
		virtual ~AbstractRecombinationSelector() {}
		friend void swap(AbstractRecombinationSelector& lhs, AbstractRecombinationSelector& rhs) noexcept;
		/**
		* \brief Executes the selection process.
		* \param recombinationCount Determines how many objects should be created by recombination. (=> 2x recombinationCount objects will be recombined)
		* \param highscore The current highscore.
		* \param counter A counter which stores how often an object is used in all commands.
		*/
		virtual void executeRecombinationSelection(int recombinationCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter);
		/**
		* \brief Returns the last selection.
		* \return A vector of all objects which were selected for recombination.
		*/
		virtual std::vector<AbstractEvolutionObject*>& getRecombinationSelection();
	};
}

#endif
