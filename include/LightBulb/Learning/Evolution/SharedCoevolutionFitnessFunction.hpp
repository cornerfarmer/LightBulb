#pragma once

#ifndef _SHAREDCOEVOLUTIONFITNESSFUNCTION_H_
#define _SHAREDCOEVOLUTIONFITNESSFUNCTION_H_

// Library Includes

// Include
#include "LightBulb/Learning/Evolution/AbstractCoevolutionFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief A fitness function which rewards individuals that win against opponents which are defeated by fewer other individuals.
	 * \details Describes \n\n
	 * \f$ f_j = \sum{\frac{1}{N_o}} \f$ \n \n
	 * Where \f$N_o\f$ is the number of individuals that can win against opponent \f$o\f$.
	 */
	class SharedCoevolutionFitnessFunction : public AbstractCoevolutionFitnessFunction
	{
	protected:
	public:
		// Inherited:
		std::map<const AbstractIndividual*, double>* execute(const CombiningStrategyResults& results) override;
	};
}

#endif
