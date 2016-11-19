#pragma once

#ifndef _NEURONDECAYFITNESSFUNCTION_H_
#define _NEURONDECAYFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Decreases fitness values depending on the neuron count of the corresponding individuals.
	 * \details Describes: \n \n \f$ fit(o) = fit*(o) - a * N \f$ \n \n
	 * \f$a: scaling factor\f$ \n 
	 * \f$N: neuron count\f$ \n 
	 */
	class NeuronDecayFitnessFunction : public AbstractFitnessFunction
	{
	private:
		/**
		 * \brief The factor which controls how strong the function will affect the fitness values.
		 */
		double fac;
	public:
		/**
		 * \brief Creates the neuron decay fitness function.
		 * \param fac_ The factor which controls how strong the function will affect the fitness values.
		 */
		NeuronDecayFitnessFunction(double fac_);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
