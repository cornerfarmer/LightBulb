#pragma once

#ifndef _STANDARDDEVIATIONFITNESSFUNCTION_H_
#define _STANDARDDEVIATIONFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief A fitness function which substracts the lower boundary of the standard deviation from the fitness values.
	 * \details Describes: \n \n \f$ fit(o) = fit*(o) - (avg - c * \sqrt{\frac{\sum{(fit_i*(o) - avg)^2}}{N}}) \f$ \n 
	 * \f$avg = \frac{\sum{fit_i*(o)}}{N}\f$ \n 
	 * \f$c: scale factor\f$ \n 
	 * \f$N: object count\f$ \n 
	 */
	class StandardDeviationFitnessFunction : public AbstractFitnessFunction
	{
	private:
		/**
		 * \brief A factory which scales the deviation interval.
		 */
		double deviationFac;
	public:
		/**
		 * \brief Creates a standard deviation fitness function.
		 * \param deviationFac_ A factory which scales the deviation interval.
		 */
		StandardDeviationFitnessFunction(double deviationFac_ = 0);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;
		AbstractFitnessFunction* clone() const override;
	};
}

#endif
