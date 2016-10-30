#pragma once

#ifndef _ABSTRACTFITNESSFUNCTION_H_
#define _ABSTRACTFITNESSFUNCTION_H_

// Includes
#include "Logging/AbstractLoggable.hpp"
#include "Tools/AbstractCloneable.hpp"

// Library Includes
#include <vector>
#include <utility>

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;

	//
	class AbstractFitnessFunction : public virtual AbstractCloneable, public AbstractLoggable
	{
	public:
		virtual ~AbstractFitnessFunction() {}
		//
		virtual void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) = 0;
	};
}

#endif
