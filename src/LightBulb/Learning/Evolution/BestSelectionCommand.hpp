#pragma once

#ifndef _BESTSELECTIONCOMMAND_H_
#define _BESTSELECTIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSelectionCommand.hpp"

namespace LightBulb
{
	/**
	 * \brief A command which selects the best N individuals for mutation/recombination
	 */
	class BestSelectionCommand : public AbstractSelectionCommand
	{
	private:
		/**
		 * \brief The amount of individuals which should be selected
		 */
		int individualCount;
		/**
		 * \brief Alternative: The percentage of individuals which should be selected
		 */
		double selectionPercentage;
	public:
		virtual ~BestSelectionCommand() {};
		/**
		 * \brief Creates a command which selects a static amount of individuals.
		 * \param individualCount_ The amount of individuals.
		 */
		BestSelectionCommand(int individualCount_);
		/**
		 * \brief Creates a command which selects a percentage of individuals.
		 * \param selectionPercentage_ The percentage of individuals.
		 */
		BestSelectionCommand(double selectionPercentage_);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::vector<AbstractIndividual*>& individual, std::vector<AbstractIndividual*>& notUsedIndividuals) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
