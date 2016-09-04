#pragma once

#ifndef _SIMPLEGRADIENTDECENT_H_
#define _SIMPLEGRADIENTDECENT_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractGradientDecentAlgorithm.hpp"

// Forward declarations

struct SimpleGradientDecentOptions : public AbstractGradientDecentAlgorithmOptions
{
	// Sets the weight decay factor, which will be used avoid high weights
	double weightDecayFac;
	// Sets the momentum, which can improve learning speed
	double momentum;
	// Sets the learning Rate
	double learningRate;
	SimpleGradientDecentOptions()
	{
		weightDecayFac = 0;
		momentum = 0.7f;
		learningRate = 0.45f;
	}

};


class SimpleGradientDecent : public AbstractGradientDecentAlgorithm
{
	template <class Archive>
	friend void serialize(Archive& archive, SimpleGradientDecent& simpleGradientDecent);
	friend struct cereal::LoadAndConstruct<SimpleGradientDecent>;
private:
	// Contains all previous deltaWeights (used by the momentum term)
	std::vector<Eigen::MatrixXd> previousDeltaWeights;
	SimpleGradientDecentOptions* getOptions();
public:
	SimpleGradientDecent(SimpleGradientDecentOptions& options_);
	SimpleGradientDecent();

	Eigen::MatrixXd calcDeltaWeight(AbstractNetworkTopology* networkTopology, int layerIndex, Eigen::MatrixXd& gradients) override;
	// Print a short debug output (totalLearningRate)
	std::string printDebugOutput() override;
	// Returns if the learning has stopped
	bool learningHasStopped() override;
	// Initializes the ResilientLearningRateHelper
	void initializeAlgorithm(AbstractNetworkTopology* networkTopology) override;
};

#include "IO/SimpleGradientDecentIO.hpp"

#endif

