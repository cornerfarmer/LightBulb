#pragma once

#ifndef _FITNESSSHARINGFITNESSFUNCTION_H_
#define _FITNESSSHARINGFITNESSFUNCTION_H_

// Library Includes

// Include
#include "Learning/Evolution/AbstractFitnessFunction.hpp"

namespace LightBulb
{
	/**
	 * \brief A fitness function to make sure to keep individuality in the population.
	 * \details Describes: \n \n \f$ fit(o) = \frac{fit*(o)}{(\sum Sh(d(o,o_i)))} \f$ \n \n
	 *  Sharing function: \n \n \f$ Sh(d(o,o_i)) ={\begin{cases} 1 - (\frac{d(o,o_i)}{\sigma})^\alpha&{\mbox{if }}d(o,o_i)<\sigma\\ 0&{\mbox{otherwise}}\end{cases}}\f$ \n \n
	 * \f$\sigma: dissimilarity threshold\f$ \n 
	 * \f$d(o,o_i): euclidean distance between two individuals \f$ \n 
	 * \f$\alpha: exponent\f$ \n 
	 */
	class FitnessSharingFitnessFunction : public AbstractFitnessFunction
	{
	private:
		/**
		 * \brief Can be used to determine how strong similarity is punished.
		 */
		double exponent;
		/**
		 * \brief Determines the maximum euclidean distance between two individuals when the fitness value should still be reduced.
		 */
		double dissimilarityThreshold;
	public:
		/**
		 * \brief Creates the fitness sharing function.
		 * \param dissimilarityThreshold_ Determines the maximum euclidean distance between two individuals when the fitness value should still be reduced. (Value is problem specific!)
		 * \param exponent_ Can be used to determine how strong similarity is punished.
		 */
		FitnessSharingFitnessFunction(double dissimilarityThreshold_, double exponent_ = 1);
		// Inherited:
		void execute(std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		AbstractFitnessFunction* clone() const override;
	};
}

#endif
