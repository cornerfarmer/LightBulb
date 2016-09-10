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

	// A algorithm which mutates a given evolution object by executing the corresponding EvolutionStrategy algorithm
	class NetworkGrowMutationAlgorithm : public AbstractMutationAlgorithm
	{
	private:
		std::vector<unsigned int> maxNeuronsPerLayer;
	public:
		NetworkGrowMutationAlgorithm(std::vector<unsigned int> maxNeuronsPerLayer_);

		void execute(AbstractEvolutionObject* object1) override;
	};
}

#endif
