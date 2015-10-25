#pragma once

#ifndef _BESTREUSECOMMAND_H_
#define _BESTREUSECOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractReuseCommand.hpp"

// Forward declarations

// A class to directly reuse the best N evolution objects
class BestReuseCommand : public AbstractReuseCommand
{
private:
	// Holds amount of objects which should be reused
	int objectCount;
	// Alternative: Holds the percentage of objects which should be reused
	double reusePercentage;
public:
	virtual ~BestReuseCommand() {};
	// Creates a command which reuses a static amount of objects
	BestReuseCommand(int objectCount_, bool enableDebugOutput_ = false);
	// Creates a command which reuses a percentage of objects
	BestReuseCommand(double reusePercentage_, bool enableDebugOutput_ = false);
	// Moves the best N objects from the old vector to the new one
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore, std::vector<AbstractEvolutionObject*>* newObjectVector);
};

#endif
