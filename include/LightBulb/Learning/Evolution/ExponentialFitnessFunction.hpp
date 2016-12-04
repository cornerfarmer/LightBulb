#pragma once

#ifndef _EXPONENTIALFITNESSFUNCTION_H_
#define _EXPONENTIALFITNESSFUNCTION_H_

// Library Includes

// Include
#include "LightBulb/Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Executes exponential scaling of fitness values.
	 * \details Describes: \n \n \f$ fit(o) = (a * fit*(o) + b)^k \f$ \n \n
	 * \f$k: exponent\f$ \n 
	 * \f$a: proportional scaling\f$ \n 
	 * \f$b: base\f$ \n 
	 */
	class ExponentialFitnessFunction : public AbstractFitnessFunction
	{
	private:
		/**
		 * \brief The factor which determines the strength of the exponential scaling.
		 */
		double exponent;
		/**
		 * \brief A constant which scales the fitness value by multiplication.
		 */
		double proportionalScaling;
		/**
		 * \brief A constant which is added to the fitness value and acts like a base.
		 */
		double base;
	public:
		/**
		 * \brief Creates the exponential fitness function.
		 * \param exponent_ The factor which determines the strength of the exponential scaling.
		 * \param proportionalScaling_ A constant which scales the fitness value by multiplication.
		 * \param base_ A constant which is added to the fitness value and acts like a base.
		 */
		ExponentialFitnessFunction(double exponent_ = 1.005, double proportionalScaling_ = 1, double base_ = 0);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		AbstractFitnessFunction* clone() const override;
	};
}

#endif
