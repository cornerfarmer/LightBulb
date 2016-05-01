#pragma once

#ifndef _ROULETTEWHEELSELECTIONFUNCTION_H_
#define _ROULETTEWHEELSELECTIONFUNCTION_H_

// Includes
#include "AbstractSelectionFunction.hpp"

// Library includes
#include <math.h>
#include <vector>

class RouletteWheelSelectionFunction : public AbstractSelectionFunction
{
private:
public:
	// Inherited:	
	int execute(const std::vector<double> &probabilities);
	std::vector<int> execute(const std::vector<double> &probabilities, int selectionCount);
};

#endif
