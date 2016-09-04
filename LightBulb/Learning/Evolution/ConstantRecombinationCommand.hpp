#pragma once

#ifndef _CONSTANTRECOMBINATIONCOMMAND_H_
#define _CONSTANTRECOMBINATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Function/RandomFunction/RankBasedRandomFunction.hpp"

// Forward declarations


class ConstantRecombinationCommand : public AbstractRecombinationCommand
{
private:
	// Holds amount of objects which should be combined
	int objectCount;
	// Alternative: Holds the percentage of objects which should be combined
	double recombinationPercentage;
public:
	void setRecombinationPercentage(double newRecombinationPercentage);
	void setRecombinationCount(int newObjectCount);
	// Creates a command which combines a static amount of objects
	ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int objectCount_);
	// Creates a command which combines a percentage of objects
	ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_);
	
	void select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, int>* counter) override;
};

#endif
