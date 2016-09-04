#pragma once

#ifndef _ABSTRACTGRADIENTDECENTALGORITHM_H_
#define _ABSTRACTGRADIENTDECENTALGORITHM_H_

// Library Includes

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "IO/UseParentSerialization.hpp"

// Forward declarations
class AbstractNeuralNetwork;
class AbstractNetworkTopology;

struct AbstractGradientDecentAlgorithmOptions
{
	int test;
	AbstractGradientDecentAlgorithmOptions()
	{
		test = 5;
	}

	virtual ~AbstractGradientDecentAlgorithmOptions() {}
};


class AbstractGradientDecentAlgorithm
{
	template <class Archive>
	friend void serialize(Archive& archive, AbstractGradientDecentAlgorithm& gradientDecentAlgorithm);
private:
	bool initialized;
protected:
	std::unique_ptr<AbstractGradientDecentAlgorithmOptions> options;
	virtual void initializeAlgorithm(AbstractNetworkTopology* networkTopology) = 0;
public:
	AbstractGradientDecentAlgorithm(AbstractGradientDecentAlgorithmOptions* options_);
	// Computes the new learning rate of the given edge from the given gradient
	virtual Eigen::MatrixXd calcDeltaWeight(AbstractNetworkTopology* networkTopology, int layerIndex, Eigen::MatrixXd& gradients) = 0;
	// Print a short debug output (totalLearningRate)
	virtual std::string printDebugOutput() { return ""; };
	// Returns if the learning has stopped
	virtual bool learningHasStopped() = 0;
	// Initializes the ResilientLearningRateHelper
	void initialize(AbstractNetworkTopology* networkTopology);

	bool isInitialized();
};

#include "IO/AbstractGradientDecentAlgorithmIO.hpp"

#endif

