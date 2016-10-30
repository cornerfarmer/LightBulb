#pragma once

#ifndef _BESTSELECTIONCOMMAND_H_
#define _BESTSELECTIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSelectionCommand.hpp"

namespace LightBulb
{
	// Forward declarations

	// A command which selects the best N objects for mutation/recombination
	class BestSelectionCommand : public AbstractSelectionCommand
	{
	private:
		// Holds amount of objects which should be selected
		int objectCount;
		// Alternative: Holds the percentage of objects which should be selected
		double selectionPercentage;
	public:
		virtual ~BestSelectionCommand() {};
		void setObjectCount(int newObjectCount);
		// Creates a command which selects a static amount of objects
		BestSelectionCommand(int objectCount_);
		// Creates a command which selects a percentage of objects
		BestSelectionCommand(double selectionPercentage_);
		// Deletes all objects from the highscore which are not part of the selected objects.
		void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore, std::vector<AbstractEvolutionObject*>& objects, std::vector<AbstractEvolutionObject*>& notUsedObjects) override;

		AbstractCloneable* clone() const override;
	};
}

#endif
