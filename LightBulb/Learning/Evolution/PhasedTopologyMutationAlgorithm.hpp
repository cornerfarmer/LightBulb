#pragma once

#ifndef _PHASEDTOPOLOGYMUTATIONALGORITHM_H_
#define _PHASEDTOPOLOGYMUTATIONALGORITHM_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationAlgorithm.hpp"
#include "MagnitudeBasedPruningMutationAlgorithm.hpp"
#include "NetworkGrowMutationAlgorithm.hpp"

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
	double calcMPC(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
public:
	PhasedTopologyMutationAlgorithm(MagnitudeBasedPruningMutationAlgorithm* magnitudeBasedPruningMutationAlgorithm_, NetworkGrowMutationAlgorithm* networkGrowMutationAlgorithm_);

	void execute(AbstractEvolutionObject* object1);

	void initialize(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore);
};

#endif
