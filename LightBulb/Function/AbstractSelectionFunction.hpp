#pragma once

#ifndef _ABSTRACTSELECTIONFUNCTION_H_
#define _ABSTRACTSELECTIONFUNCTION_H_

// Library includes
#include <vector>

class AbstractSelectionFunction
{
private:
public:
	// Inherited:	
	virtual int execute(const std::vector<double> &probabilities) = 0;
	virtual std::vector<int> execute(const std::vector<double> &probabilities, int selectionCount) = 0;
};

#endif
