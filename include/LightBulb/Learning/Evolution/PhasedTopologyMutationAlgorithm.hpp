#pragma once

#ifndef _PHASEDTOPOLOGYMUTATIONALGORITHM_H_
#define _PHASEDTOPOLOGYMUTATIONALGORITHM_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractMutationAlgorithm.hpp"

// Library Includes
#include <memory>

namespace LightBulb
{
	class MagnitudeBasedPruningMutationAlgorithm;
	class NetworkGrowMutationAlgorithm;
	/**
	 * \brief The phased topology mutation algorithm which automatically adds and removes neurons depending on the fitness values.
	 * \details Uses the MPC (average neuron and weight count in the population) to determine if the algorithm should switch between pruning and complexifying.\n
	 * More details: http://sharpneat.sourceforge.net/phasedsearch.html
	 */
	class PhasedTopologyMutationAlgorithm : public AbstractMutationAlgorithm
	{
	private:
		/**
		 * \brief The algorithm for removing neurons.
		 */
		std::unique_ptr<MagnitudeBasedPruningMutationAlgorithm> magnitudeBasedPruningMutationAlgorithm;
		/**
		 * \brief The algorithm for adding neurons.
		 */
		std::unique_ptr<NetworkGrowMutationAlgorithm> networkGrowMutationAlgorithm;
		/**
		 * \brief Determines the upper boundary of the pruning phase.
		 * \details Is set at the beginning of every complexifying phase.
		 */
		double pruneThreshold;
		/**
		 * \brief True, if currently the pruning phase is enabled, otherwise the complexifying phase is on.
		 */
		bool pruningPhase;
		/**
		 * \brief The last mpc value.
		 */
		double lastMPC;
		/**
		 * \brief The amount of round since the mpc did not decrease.
		 */
		int mpcNotFallenRounds;
		/**
		 * \brief The threshold which should be added to the mpc to get the new pruneThreshold.
		 */
		int pruningThresholdDistance;
		double calcMPC(const std::vector<std::pair<double, AbstractIndividual*>>& highscore);
	public:
		PhasedTopologyMutationAlgorithm() = default;
		/**
		 * \brief Creates the phased topology mutation algorithm.
		 * \param magnitudeBasedPruningMutationAlgorithm_ The algorithm for removing neurons.
		 * \param networkGrowMutationAlgorithm_ The algorithm for adding neurons.
		 * \param pruningThresholdDistance_ The threshold which should be added to the mpc to get the new pruneThreshold.
		 */
		PhasedTopologyMutationAlgorithm(MagnitudeBasedPruningMutationAlgorithm* magnitudeBasedPruningMutationAlgorithm_, NetworkGrowMutationAlgorithm* networkGrowMutationAlgorithm_, int pruningThresholdDistance_ = 30);
		PhasedTopologyMutationAlgorithm(const PhasedTopologyMutationAlgorithm& other);
		PhasedTopologyMutationAlgorithm(PhasedTopologyMutationAlgorithm&& other) noexcept;
		PhasedTopologyMutationAlgorithm& operator=(PhasedTopologyMutationAlgorithm other);
		friend void swap(PhasedTopologyMutationAlgorithm& lhs, PhasedTopologyMutationAlgorithm& rhs) noexcept;
		// Inherited:
		void execute(AbstractIndividual& individual1) override;
		void initialize(const std::vector<std::pair<double, AbstractIndividual*>>& highscore) override;
		void setRandomGenerator(AbstractRandomGenerator& randomGenerator_) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
