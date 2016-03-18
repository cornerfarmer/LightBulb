#pragma once

#ifndef _CONSTANTRECOMBINATIONCOMMAND_H_
#define _CONSTANTRECOMBINATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractRecombinationCommand.hpp"
#include "Function/RankBasedRandomFunction.hpp"

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
	// Creates a command which combines a static amount of objects
	ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, int objectCount_, bool enableDebugOutput_ = false);
	// Creates a command which combines a percentage of objects
	ConstantRecombinationCommand(AbstractRecombinationAlgorithm* recombinationAlgorithm_, AbstractRecombinationSelector* recombinationSelector_, double recombinationPercentage_, bool enableDebugOutput_ = false);
	
	void select(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::map<AbstractEvolutionObject*, std::map<std::string, int>>* counter);
};

#endif
