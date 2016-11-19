#pragma once

#ifndef _LINEARSSCALINGFITNESSFUNCTION_H_
#define _LINEARSCALINGFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief Performs linear scaling on fitness values.
	 * \details Describes: \n \n \f$ fit(o) = a * fit*(o) + b \f$ \n \n
	 * \f$a: proportional scaling\f$ \n 
	 * \f$b: base\f$ \n 
	 */
	class LinearScalingFitnessFunction : public AbstractFitnessFunction
	{
	private:
		/**
		 * \brief The factor by which the fitness values should be scaled.
		 */
		double proportionalScaling;
		/**
		 * \brief A constant base which is added to every value.
		 */
		double base;
		/**
		 * \brief True if dynamic scaling is activated. In that mode, the negative smallest fitness value is taken as base.
		 */
		bool useDynamicScaling;
	public:
		/**
		 * \brief Creates a liniear scaling fitness function.
		 * \param proportionalScaling_ The factor by which the fitness values should be scaled.
		 * \param base_ A constant base which is added to every value.
		 * \param useDynamicScaling_ True if dynamic scaling is activated. In that mode, the negative smallest fitness value is taken as base.
		 */
		LinearScalingFitnessFunction(double proportionalScaling_, double base_, bool useDynamicScaling_ = false);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		AbstractFitnessFunction* clone() const override;
	};
}

#endif
