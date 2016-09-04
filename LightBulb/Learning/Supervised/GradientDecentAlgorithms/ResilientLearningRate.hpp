#pragma once

#ifndef _RESILIENTLEARNINGRATE_H_
#define _RESILIENTLEARNINGRATE_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractGradientDecentAlgorithm.hpp"

// Forward declarations

struct ResilientLearningRateOptions : public AbstractGradientDecentAlgorithmOptions
{	
	// Sets the factor by which the learningRate can grow
	double learningRateGrowFac;
	// Sets the factor by which the learningRate can shrink
	double learningRateShrinkFac;
	// Sets the highest possible learningRate
	double learningRateMax;
	// Sets the lowest possible learningRate
	double learningRateMin;
	// Sets the start value of all learningRates
	double learningRateStart;
	// The lowest total learning rate (if the current value is smaller than this value the learning process will stop)
	double minLearningRate;
	ResilientLearningRateOptions()
	{
		learningRateGrowFac = 1.2f;
		learningRateShrinkFac = 0.5f;
		learningRateMax = 50;
		learningRateMin = 0.000001f;
		learningRateStart = 0.2f;
		minLearningRate = 0;
	}
};


class ResilientLearningRate : public AbstractGradientDecentAlgorithm
{
	template <class Archive>
	friend void serialize(Archive& archive, ResilientLearningRate& resilientLearningRate);
	friend struct cereal::LoadAndConstruct<ResilientLearningRate>;
private:
	// Holds for every edge its previous learning rate
	std::vector<Eigen::MatrixXd> previousLearningRates;
	ResilientLearningRateOptions* getOptions();
public:
	ResilientLearningRate(ResilientLearningRateOptions& options_);
	ResilientLearningRate();

	Eigen::MatrixXd calcDeltaWeight(AbstractNetworkTopology* networkTopology, int layerIndex, Eigen::MatrixXd& gradients) override;
	// Print a short debug output (totalLearningRate)
	std::string printDebugOutput() override;
	// Returns if the learning has stopped
	bool learningHasStopped() override;
	// Initializes the ResilientLearningRateHelper
	void initializeAlgorithm(AbstractNetworkTopology* networkTopology) override;

};

#include "IO/ResilientLearningRateIO.hpp"

#endif

