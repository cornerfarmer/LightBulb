// Includes
#include "Learning/Evolution/PhasedTopologyMutationAlgorithm.hpp"
#include "AbstractEvolutionObject.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <NetworkTopology/AbstractNetworkTopology.hpp>

namespace LightBulb
{
	PhasedTopologyMutationAlgorithm::PhasedTopologyMutationAlgorithm(MagnitudeBasedPruningMutationAlgorithm* magnitudeBasedPruningMutationAlgorithm_, NetworkGrowMutationAlgorithm* networkGrowMutationAlgorithm_, int pruningThresholdDistance_)
	{
		magnitudeBasedPruningMutationAlgorithm.reset(magnitudeBasedPruningMutationAlgorithm_);
		networkGrowMutationAlgorithm.reset(networkGrowMutationAlgorithm_);
		pruningPhase = false;
		pruneThreshold = -1;
		pruningThresholdDistance = pruningThresholdDistance_;
	}

	PhasedTopologyMutationAlgorithm::PhasedTopologyMutationAlgorithm(const PhasedTopologyMutationAlgorithm& other)
		:AbstractMutationAlgorithm(other)
	{
		magnitudeBasedPruningMutationAlgorithm.reset(new MagnitudeBasedPruningMutationAlgorithm(*other.magnitudeBasedPruningMutationAlgorithm));
		networkGrowMutationAlgorithm.reset(new NetworkGrowMutationAlgorithm(*other.networkGrowMutationAlgorithm));

		pruneThreshold = other.pruneThreshold;
		pruningPhase = other.pruningPhase;
		lastMPC = other.lastMPC;
		mpcNotFallenRounds = other.mpcNotFallenRounds;
		pruningThresholdDistance = other.pruningThresholdDistance;
	}

	PhasedTopologyMutationAlgorithm& PhasedTopologyMutationAlgorithm::operator=(PhasedTopologyMutationAlgorithm other)
	{
		swap(*this, other);
		return *this;
	}

	void swap(PhasedTopologyMutationAlgorithm& lhs, PhasedTopologyMutationAlgorithm& rhs) noexcept
	{
		using std::swap;
		swap(static_cast<AbstractMutationAlgorithm&>(lhs), static_cast<AbstractMutationAlgorithm&>(rhs));
		swap(lhs.magnitudeBasedPruningMutationAlgorithm, rhs.magnitudeBasedPruningMutationAlgorithm);
		swap(lhs.networkGrowMutationAlgorithm, rhs.networkGrowMutationAlgorithm);
		swap(lhs.pruneThreshold, rhs.pruneThreshold);
		swap(lhs.pruningPhase, rhs.pruningPhase);
		swap(lhs.lastMPC, rhs.lastMPC);
		swap(lhs.mpcNotFallenRounds, rhs.mpcNotFallenRounds);
		swap(lhs.pruningThresholdDistance, rhs.pruningThresholdDistance);
	}

	void PhasedTopologyMutationAlgorithm::execute(AbstractEvolutionObject& object1)
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

	double PhasedTopologyMutationAlgorithm::calcMPC(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
	{
		double mpc = 0;
		for (auto entry = highscore.begin(); entry != highscore.end(); entry++)
		{
			mpc += entry->second->getNeuralNetwork().getNetworkTopology().getEdgeCount();
			mpc += entry->second->getNeuralNetwork().getNetworkTopology().getNeuronCount();
		}
		return mpc / highscore.size();
	}

	void PhasedTopologyMutationAlgorithm::initialize(const std::vector<std::pair<double, AbstractEvolutionObject*>>& highscore)
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

	void PhasedTopologyMutationAlgorithm::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
	{
		AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
		networkGrowMutationAlgorithm->setRandomGenerator(randomGenerator_);
		magnitudeBasedPruningMutationAlgorithm->setRandomGenerator(randomGenerator_);
	}

	AbstractCloneable* PhasedTopologyMutationAlgorithm::clone() const
	{
		return new PhasedTopologyMutationAlgorithm(*this);
	}
}
