#pragma once

#ifndef _BESTREUSESELECTOR_H_
#define _BESTREUSESELECTOR_H_

// Library includes
#include <vector>
#include <utility>
#include <map>

// Includes
#include "AbstractReuseSelector.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;

	//
	class BestReuseSelector : public AbstractReuseSelector
	{
	private:
	protected:
		void selectForReuse(int reuseCount, const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
	public:
	};
}

#endif
