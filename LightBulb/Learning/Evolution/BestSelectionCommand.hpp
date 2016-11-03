#pragma once

#ifndef _BESTSELECTIONCOMMAND_H_
#define _BESTSELECTIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSelectionCommand.hpp"

namespace LightBulb
{
	/**
	 * \brief A command which selects the best N objects for mutation/recombination
	 */
	class BestSelectionCommand : public AbstractSelectionCommand
	{
	private:
		/**
		 * \brief The amount of objects which should be selected
		 */
		int objectCount;
		/**
		 * \brief Alternative: The percentage of objects which should be selected
		 */
		double selectionPercentage;
	public:
		virtual ~BestSelectionCommand() {};
		/**
		 * \brief Creates a command which selects a static amount of objects.
		 * \param objectCount_ The amount of objects.
		 */
		BestSelectionCommand(int objectCount_);
		/**
		 * \brief Creates a command which selects a percentage of objects.
		 * \param selectionPercentage_ The percentage of objects.
		 */
		BestSelectionCommand(double selectionPercentage_);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::vector<AbstractEvolutionObject*>& objects, std::vector<AbstractEvolutionObject*>& notUsedObjects) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
