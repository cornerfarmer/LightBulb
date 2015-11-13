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
	// Takes N * 2 objects, combines them and adds the created objects to the new objects vector
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
};

#endif
