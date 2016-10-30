#pragma once

#ifndef _PHASEDTOPOLOGYMUTATIONALGORITHM_H_
#define _PHASEDTOPOLOGYMUTATIONALGORITHM_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "MagnitudeBasedPruningMutationAlgorithm.hpp"
#include "NetworkGrowMutationAlgorithm.hpp"

namespace LightBulb
{
	// Forward declarations

	class PhasedTopologyMutationAlgorithm : public AbstractMutationAlgorithm
	{
	private:
		std::unique_ptr<MagnitudeBasedPruningMutationAlgorithm> magnitudeBasedPruningMutationAlgorithm;
		std::unique_ptr<NetworkGrowMutationAlgorithm> networkGrowMutationAlgorithm;
		double pruneThreshold;
		bool pruningPhase;
		double lastMPC;
		int mpcNotFallenRounds;
		int pruningThresholdDistance;
		double calcMPC(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore);
	public:
		PhasedTopologyMutationAlgorithm(MagnitudeBasedPruningMutationAlgorithm* magnitudeBasedPruningMutationAlgorithm_, NetworkGrowMutationAlgorithm* networkGrowMutationAlgorithm_, int pruningThresholdDistance_ = 30);
		PhasedTopologyMutationAlgorithm(const PhasedTopologyMutationAlgorithm& other);
		void execute(AbstractEvolutionObject& object1) override;

		void initialize(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore) override;

		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
