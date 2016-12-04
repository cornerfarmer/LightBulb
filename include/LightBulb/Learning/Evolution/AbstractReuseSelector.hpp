#pragma once

#ifndef _ABSTRACTREUSESELECTOR_H_
#define _ABSTRACTREUSESELECTOR_H_

// Includes
#include "LightBulb/Tools/AbstractCloneable.hpp"

// Library includes
#include <vector>
#include <utility>
#include <map>
#include <string>

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	/**
	* \brief Describes an algorithm which selects the individuals which will be reused.
	*/
	class AbstractReuseSelector : public virtual AbstractCloneable
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
		* \brief Selects the given individual for reusing.
		* \param individual The individual.
		*/
		virtual void addIndividualToReuse(AbstractIndividual& individual);
		/**
		* \brief Executes the selection process.
		* \param reuseCount Determines how many individuals should be reused.
		* \param highscore The current highscore.
		*/
		virtual void selectForReuse(int reuseCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) = 0;
	public:
		virtual ~AbstractReuseSelector() {};
		/**
		* \brief Executes the selection process.
		* \param reuseCount Determines how many individuals should be reused.
		* \param highscore The current highscore.
		* \param counter A counter which stores how often an individual is used in all commands.
		*/
		virtual void executeReuseSelection(int reuseCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter);
		/**
		* \brief Returns the last selection.
		* \return A vector of all individuals which were selected for reusing.
		*/
		virtual const std::vector<AbstractIndividual*>& getReuseSelection() const;
	};
}

#endif
