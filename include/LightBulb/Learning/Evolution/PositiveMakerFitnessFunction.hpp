#pragma once

#ifndef _POSITIVEMAKERFITNESSFUNCTION_H_
#define _POSITIVEMAKERFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief A fitness function which makes all fitness values positive.3
	 * \details Describes: \n \n \f$ fit(o) = max(0, fit*(o) + b) \f$ \n \n
	 * \f$b: base\f$ \n 
	 */
	class PositiveMakerFitnessFunction : public AbstractFitnessFunction
	{
	private:
		/**
		 * \brief A constant which is added to every value.
		 */
		double constant;
	public:
		/**
		 * \brief Creates a positive maker fitness function.
		 * \param constant_ A constant which is added to every value.
		 */
		PositiveMakerFitnessFunction(double constant_);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		AbstractFitnessFunction* clone() const override;
	};
}

#endif
