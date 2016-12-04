#pragma once

#ifndef _ROULETTEWHEELSELECTIONFUNCTION_H_
#define _ROULETTEWHEELSELECTIONFUNCTION_H_

// Includes
#include "LightBulb/Function/SelectionFunction/AbstractSelectionFunction.hpp"

// Library includes
#include <math.h>
#include <vector>

namespace LightBulb
{
	/**
	 * \brief Selects elements like a roulette wheel.
	 * \details Splits the "roulette wheel" into different parts depending on the element probabilities. \n
	 *  - When choosing one element, the wheel is just spinned once. \n
	 *  - When choosing multiple elements, pointers are placed all 360/n degrees. The chosen elements are determined where the pointers point to.
	 */
	class RouletteWheelSelectionFunction : public AbstractSelectionFunction
	{
	private:
	public:
		// Inherited:	
		int execute(const std::vector<double> &probabilities) const override;
		std::vector<int> execute(const std::vector<double> &probabilities, int selectionCount) const override;
		AbstractCloneable* clone() const override;
	};
}

#endif
