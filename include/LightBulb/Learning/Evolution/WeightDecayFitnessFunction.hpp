#pragma once

#ifndef _WEIGHTDECAYFITNESSFUNCTION_H_
#define _WEIGHTDECAYFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Decreases fitness values depending on the neuron count of the corresponding individuals.
	 * \details Describes: \n \n \f$ fit(o) = fit*(o) - a * 0.5 * \sum{\omega_{i,j}^2} \f$ \n \n
	 * \f$a: scaling factor\f$ \n 
	 * \f$\omega: weight\f$ \n 
	 */
	class WeightDecayFitnessFunction : public AbstractFitnessFunction
	{
	private:
		/**
		* \brief The factor which controls how strong the function will affect the fitness values.
		*/
		double fac;
	public:
		/**
		 * \brief Creates the weight decay fitness function.
		 * \param fac_ The factor which controls how strong the function will affect the fitness values.
		 */
		WeightDecayFitnessFunction(double fac_);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		AbstractFitnessFunction* clone() const override;
	};
}

#endif
