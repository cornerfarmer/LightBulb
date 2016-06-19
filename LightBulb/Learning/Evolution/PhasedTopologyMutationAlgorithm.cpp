// Includes
#include "Learning/Evolution/PhasedTopologyMutationAlgorithm.hpp"
#include "AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

PhasedTopologyMutationAlgorithm::PhasedTopologyMutationAlgorithm(MagnitudeBasedPruningMutationAlgorithm* magnitudeBasedPruningMutationAlgorithm_, NetworkGrowMutationAlgorithm* networkGrowMutationAlgorithm_, int pruningThresholdDistance_)
{
	magnitudeBasedPruningMutationAlgorithm.reset(magnitudeBasedPruningMutationAlgorithm_);
	networkGrowMutationAlgorithm.reset(networkGrowMutationAlgorithm_);
	pruningPhase = false;
	pruneThreshold = -1;
	pruningThresholdDistance = pruningThresholdDistance_;
}

void PhasedTopologyMutationAlgorithm::execute(AbstractEvolutionObject* object1)
{
	if (!pruningPhase)
	{
		networkGrowMutationAlgorithm->execute(object1);
	}
	else
	{
		magnitudeBasedPruningMutationAlgorithm->execute(object1);
	}
}

double PhasedTopologyMutationAlgorithm::calcMPC(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	double mpc = 0;
	for (auto entry = highscore->begin(); entry != highscore->end(); entry++)
	{
		mpc += entry->second->getNeuralNetwork()->getNetworkTopology()->getEdgeCount();
	}
	return mpc / highscore->size();
}

void PhasedTopologyMutationAlgorithm::initialize(std::vector<std::pair<double, AbstractEvolutionObject*>>* highscore)
{
	if (!pruningPhase)
	{
		if (pruneThreshold == -1)
		{
			pruneThreshold = calcMPC(highscore) + pruningThresholdDistance;
		}
		else
		{
			if (pruneThreshold <= calcMPC(highscore))
			{
				pruningPhase = true;
				lastMPC = -1;
			}
		}
	}
	else
	{
		double currentMPC = calcMPC(highscore);
		if (lastMPC != -1 && lastMPC <= currentMPC)
		{
			mpcNotFallenRounds++;
			if (mpcNotFallenRounds > 10)
			{
				pruningPhase = false;
				pruneThreshold = currentMPC + pruningThresholdDistance;
			}
		}
		else
		{
			mpcNotFallenRounds = 0;
			lastMPC = currentMPC;
		}
	}
}
