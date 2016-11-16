#pragma once

#ifndef _MUTATIONALGORITHM_H_
#define _MUTATIONALGORITHM_H_

// Library Includes
#include <random>

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"


namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	/**
	 * \brief  A algorithm which mutates a given evolution object by executing the corresponding EvolutionStrategy algorithm.
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
		double mutationStrengthMin;
		/**
		 * \brief The absolute maximum of a mutationStrength value.
		 */
		double mutationStrengthMax;
	public:
		/**
		 * \brief Creates the mutation algorithm.
		 * \param mutationStrengthChangeSpeed_ This factor influences the change speed of mutationStrengths.
		 * \param mutationStrengthMax_ The absolute maximum of a mutationStrength value.
		 * \param mutationStrengthMin_ The absolute minimum of a mutationStrength value.
		 */
		MutationAlgorithm(double mutationStrengthChangeSpeed_, double mutationStrengthMax_ = 50, double mutationStrengthMin_ = 0.000001f);
		// Inherited:
		void execute(AbstractEvolutionObject& object1) override;
		AbstractMutationAlgorithm* clone() const override;
	};
}

#endif
