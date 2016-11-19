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
	class AbstractIndividual;
	/**
	* \brief Describes an algorithm which selects the individuals which will be recombined.
	*/
	class AbstractRecombinationSelector : public virtual AbstractCloneable, public virtual AbstractRandomGeneratorUser
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
		* \brief Selects the given individual for recombination.
		* \param individual The individual.
		*/
		virtual void addIndividualToRecombination(AbstractIndividual& individual);
		/**
		* \brief Executes the selection process.
		* \param recombinationCount Determines how many individuals should be created by recombination. (=> 2x recombinationCount individuals will be recombined)
		* \param highscore The current highscore.
		*/
		virtual void selectForRecombination(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore) = 0;
	public:
		virtual ~AbstractRecombinationSelector() {}
		friend void swap(AbstractRecombinationSelector& lhs, AbstractRecombinationSelector& rhs) noexcept;
		/**
		* \brief Executes the selection process.
		* \param recombinationCount Determines how many individuals should be created by recombination. (=> 2x recombinationCount individuals will be recombined)
		* \param highscore The current highscore.
		* \param counter A counter which stores how often an individual is used in all commands.
		*/
		virtual void executeRecombinationSelection(int recombinationCount, const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter);
		/**
		* \brief Returns the last selection.
		* \return A vector of all individuals which were selected for recombination.
		*/
		virtual std::vector<AbstractIndividual*>& getRecombinationSelection();
	};
}

#endif
