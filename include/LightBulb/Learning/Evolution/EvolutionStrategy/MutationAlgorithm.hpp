#pragma once

#ifndef _MUTATIONALGORITHM_H_
#define _MUTATIONALGORITHM_H_

// Library Includes

// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"


namespace LightBulb
{
	// Forward declarations
	class AbstractIndividual;
	/**
	 * \brief  A algorithm which mutates a given individual by executing the corresponding EvolutionStrategy algorithm.
	 * \details The algorithm:\n\n
	 * 1. All mutationStrength values are changed randomly.\n
	 * 2. The new mutationStrength values are added to their corresponding weights.
	 */
	class MutationAlgorithm : public AbstractMutationAlgorithm
	{
	private:
		/**
		 * \brief This factor influences the change speed of mutationStrengths.
		 */
		double mutationStrengthChangeSpeed;
		/**
		 * \brief The absolute minimum of a mutationStrength value.
		 */
		float mutationStrengthMin;
		/**
		 * \brief The absolute maximum of a mutationStrength value.
		 */
		float mutationStrengthMax;
		void mutateMutationStrength(viennacl::vector_base<float>& mutationStrength, const viennacl::vector_base<float>& randNumbers) const;
		void mutateWeights(viennacl::matrix_base<float>& W, const viennacl::vector_base<float>& mutationStrength, unsigned mutationStrengthOffset, unsigned randNumbersOffset, const viennacl::vector_base<float>& randNumbers) const;
	public:
		/**
		 * \brief Creates the mutation algorithm.
		 * \param mutationStrengthChangeSpeed_ This factor influences the change speed of mutationStrengths.
		 * \param mutationStrengthMax_ The absolute maximum of a mutationStrength value.
		 * \param mutationStrengthMin_ The absolute minimum of a mutationStrength value.
		 */
		MutationAlgorithm(double mutationStrengthChangeSpeed_, double mutationStrengthMax_ = 50, double mutationStrengthMin_ = 0.000001f);
		// Inherited:
		void execute(AbstractIndividual& individual1) override;
		AbstractMutationAlgorithm* clone() const override;
	};
}

#endif
