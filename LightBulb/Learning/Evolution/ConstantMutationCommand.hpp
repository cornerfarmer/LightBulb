#pragma once

#ifndef _CONSTANTMUTATIONCOMMAND_H_
#define _CONSTANTMUTATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"
#include "Function/RankBasedRandomFunction.hpp"

// Forward declarations

// Mutates a constant amount of objects
class ConstantMutationCommand : public AbstractMutationCommand
{
private:
	// Holds amount of objects which should be mutated
	int objectCount;
	// Alternative: Holds the percentage of objects which should be mutated
	double mutationPercentage;
	// A random function which will be used to select objects which will be mutated
	RankBasedRandomFunction rankBasedRandomFunction;
public:
	virtual ~ConstantMutationCommand() {};
	void setMutationPercentage(double newMutationPercentage);
	// Creates a command which mutates a static amount of objects
	ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, int objectCount_, bool enableDebugOutput_ = false);
	// Creates a command which mutates a percentage of objects
	ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, double mutationPercentage_, bool enableDebugOutput_ = false);
	// Takes N objects, mutates them and adds them to the new objects vector
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
};

#endif
