#pragma once

#ifndef _NETWORKGROWMUTATIONALGORITHM_H_
#define _NETWORKGROWMUTATIONALGORITHM_H_

// Library Includes
#include <random>

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractEvolutionObject;
	/**
	 * \brief A mutation algorithm which adds neurons to the given objects.
	 */
	class NetworkGrowMutationAlgorithm : public AbstractMutationAlgorithm
	{
	private:
		/**
		 * \brief The upper boundary of the allowed neuron count per layer.
		 */
		std::vector<unsigned int> maxNeuronsPerLayer;
	public:
		/**
		 * \brief Creates a network grow mutation algorithm.
		 * \param maxNeuronsPerLayer_ The upper boundary of the allowed neuron count per layer.
		 */
		NetworkGrowMutationAlgorithm(const std::vector<unsigned int>& maxNeuronsPerLayer_);
		// Inherited:
		void execute(AbstractEvolutionObject& object1) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
