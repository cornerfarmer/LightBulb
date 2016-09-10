#pragma once

#ifndef _CONSTANTMUTATIONCOMMAND_H_
#define _CONSTANTMUTATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"

namespace LightBulb
{
	// Forward declarations

	// Mutates a constant amount of objects
	class ConstantMutationCommand : public AbstractMutationCommand
	{
	private:
		// Holds amount of objects which should be mutated
		int objectCount;
		// Alternative: Holds the percentage of objects which should be mutated
		double mutationPercentage;
	public:
		virtual ~ConstantMutationCommand() {};
		void setMutationPercentage(double newMutationPercentage);
		void setMutationCount(double newMutationCount);
		// Creates a command which mutates a static amount of objects
		ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, int objectCount_);
		// Creates a command which mutates a percentage of objects
		ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, double mutationPercentage_);

		void select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, int>* counter) override;
	};
}

#endif
