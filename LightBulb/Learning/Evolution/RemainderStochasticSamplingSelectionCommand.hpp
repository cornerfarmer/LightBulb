#pragma once

#ifndef _REMAINDERSTOCHASTICSAMPLINGSELECTIONCOMMAND_H_
#define _REMAINDERSTOCHASTICSAMPLINGSELECTIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractSelectionCommand.hpp"
#include "Function/RouletteWheelSelectionFunction.hpp"

// Forward declarations

// A command which selects the best N objects for mutation/recombination
class RemainderStochasticSamplingSelectionCommand : public AbstractSelectionCommand
{
private:
	// Holds amount of objects which should be selected
	int objectCount;

	RouletteWheelSelectionFunction randomFunction;
public:
	virtual ~RemainderStochasticSamplingSelectionCommand() {};
	void setObjectCount(int newObjectCount);
	// Creates a command which selects a static amount of objects
	RemainderStochasticSamplingSelectionCommand(int objectCount_, bool enableDebugOutput_ = false);
	// Deletes all objects from the highscore which are not part of the selected objects.
	void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
};

#endif
