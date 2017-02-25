#pragma once

#ifndef _RECOMBINATIONALGORITHM_H_
#define _RECOMBINATIONALGORITHM_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractRecombinationAlgorithm.hpp"

// Library Includes
#include <viennacl/matrix.hpp>

namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	class Kernel;
	/**
	 * \brief A algorithm which combines two given individuals by executing the corresponding EvolutionStrategy algorithm.
	 * \details There are two modes available:\n\n
	 * 1. The weights of the child are the average values of the parents weights.
	 * 2. The weights are randomly taken either from the first OR the second parent.
	 */
	class RecombinationAlgorithm : public AbstractRecombinationAlgorithm
	{
	private:
		std::unique_ptr<Kernel> recombineWeightsWithAverageKernel;
		std::unique_ptr<Kernel> recombineMutationStrengthWithAverageKernel;
		/**
		 * \brief True, if the average of the parents weights should be used for the child weights.
		 */
		bool useAverageForWeight;
		/**
		* \brief True, if the average of the parents mutation strengths should be used for the child mutation strengths.
		*/
		bool useAverageForMutationStrength;
		void recombineWeightsWithAverage(viennacl::matrix_base<float>& W1, const viennacl::matrix_base<float>& W2) const;
		void recombineMutationStrengthWithAverage(viennacl::vector_base<float>& vec1, const viennacl::vector_base<float>& vec2) const;
	public:
		/**
		 * \brief Creates the recombination algorithm
		 * \param useAverageForWeight_ True, if the average of the parents weights should be used for the child weights.
		 * \param useAverageForMutationStrength_ True, if the average of the parents mutation strengths should be used for the child mutation strengths.
		 */
		RecombinationAlgorithm(bool useAverageForWeight_ = true, bool useAverageForMutationStrength_ = true);
		// Inherited.
		void execute(AbstractIndividual& individual1, AbstractIndividual& individual2) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
