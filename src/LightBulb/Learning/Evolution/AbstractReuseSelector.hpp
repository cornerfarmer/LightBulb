#pragma once

#ifndef _ABSTRACTREUSESELECTOR_H_
#define _ABSTRACTREUSESELECTOR_H_

// Includes
#include "Tools/AbstractCloneable.hpp"

// Library includes
#include <vector>
#include <utility>
#include <map>
#include <string>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	/**
	* \brief Describes an algorithm which selects the objects which will be reused.
	*/
	class AbstractReuseSelector : public virtual AbstractCloneable
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
		* \brief Selects the given object for reusing.
		* \param object The object.
		*/
		virtual void addObjectToReuse(AbstractEvolutionObject& object);
		/**
		* \brief Executes the selection process.
		* \param reuseCount Determines how many objects should be reused.
		* \param highscore The current highscore.
		*/
		virtual void selectForReuse(int reuseCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) = 0;
	public:
		virtual ~AbstractReuseSelector() {};
		/**
		* \brief Executes the selection process.
		* \param reuseCount Determines how many objects should be reused.
		* \param highscore The current highscore.
		* \param counter A counter which stores how often an object is used in all commands.
		*/
		virtual void executeReuseSelection(int reuseCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::map<AbstractEvolutionObject*, int>& counter);
		/**
		* \brief Returns the last selection.
		* \return A vector of all objects which were selected for reusing.
		*/
		virtual const std::vector<AbstractEvolutionObject*>& getReuseSelection() const;
	};
}

#endif
