#pragma once

#ifndef _ABSTRACTSELECTIONFUNCTION_H_
#define _ABSTRACTSELECTIONFUNCTION_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"

// Library includes
#include <vector>

namespace LightBulb
{
	class AbstractSelectionFunction : public AbstractRandomGeneratorUser
	{
	private:
	public:
		// Inherited:	
		virtual int execute(const std::vector<double> &probabilities) = 0;
		virtual std::vector<int> execute(const std::vector<double> &probabilities, int selectionCount) = 0;
	};
}

#endif
