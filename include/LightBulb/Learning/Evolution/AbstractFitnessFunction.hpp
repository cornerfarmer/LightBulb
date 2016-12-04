#pragma once

#ifndef _ABSTRACTFITNESSFUNCTION_H_
#define _ABSTRACTFITNESSFUNCTION_H_

// Includes
#include "LightBulb/Logging/AbstractLoggable.hpp"
#include "LightBulb/Tools/AbstractCloneable.hpp"

// Library Includes
#include <vector>
#include <utility>

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	/**
	 * \brief Describes a function which does some post processing on the calculated fitness values.
	 */
	class AbstractFitnessFunction : public virtual AbstractCloneable, public AbstractLoggable
	{
	public:
		virtual ~AbstractFitnessFunction() {}
		/**
		 * \brief Executes the fitness function.
		 * \param highscore The current fitness values which should be adjusted.
		 */
		virtual void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore) = 0;
	};
}

#endif
