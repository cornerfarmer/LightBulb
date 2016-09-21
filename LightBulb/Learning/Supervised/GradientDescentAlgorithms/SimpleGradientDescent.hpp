#pragma once

#ifndef _SIMPLEGRADIENTDESCENT_H_
#define _SIMPLEGRADIENTDESCENT_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractGradientDescentAlgorithm.hpp"

namespace LightBulb
{
	// Forward declarations

	struct SimpleGradientDescentOptions : public AbstractGradientDescentAlgorithmOptions
	{
		// Sets the weight decay factor, which will be used avoid high weights
		double weightDecayFac;
		// Sets the momentum, which can improve learning speed
		double momentum;
		// Sets the learning Rate
		double learningRate;
		SimpleGradientDescentOptions()
		{
			weightDecayFac = 0;
			momentum = 0.7f;
			learningRate = 0.45f;
		}

	};


	class SimpleGradientDescent : public AbstractGradientDescentAlgorithm
	{
		template <class Archive>
		friend void serialize(Archive& archive, SimpleGradientDescent& simpleGradientDescent);
		friend struct cereal::LoadAndConstruct<SimpleGradientDescent>;
	private:
		// Contains all previous deltaWeights (used by the momentum term)
		std::vector<Eigen::MatrixXd> previousDeltaWeights;
		SimpleGradientDescentOptions* getOptions();
	public:
		SimpleGradientDescent(SimpleGradientDescentOptions& options_);
		SimpleGradientDescent();

		Eigen::MatrixXd calcDeltaWeight(AbstractNetworkTopology* networkTopology, int layerIndex, Eigen::MatrixXd& gradients) override;
		// Print a short debug output (totalLearningRate)
		std::string printDebugOutput() override;
		// Returns if the learning has stopped
		bool learningHasStopped() override;
		// Initializes the ResilientLearningRateHelper
		void initializeAlgorithm(AbstractNetworkTopology* networkTopology) override;
	};
}

#include "IO/SimpleGradientDescentIO.hpp"

#endif

