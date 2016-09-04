#pragma once

#ifndef _RMSPROPLEARNINGRATEHELPEROPTIONS_H_
#define _RMSPROPLEARNINGRATEHELPEROPTIONS_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractGradientDecentAlgorithm.hpp"

// Forward declarations

struct RMSPropLearningRateOptions : public AbstractGradientDecentAlgorithmOptions
{	
	// Sets the factor by which the learningRate can grow
	double gradientMomentum;
	double squaredGradientMomentum;
	double deltaWeightsMomentum;
	double learningRate;
	double minSquaredGradient;
	RMSPropLearningRateOptions()
	{
		gradientMomentum = 0.95;
		squaredGradientMomentum = 0.95;
		deltaWeightsMomentum = 0.9;
		learningRate = 0.25;
		minSquaredGradient = 0.01;
	}
};


class RMSPropLearningRate : public AbstractGradientDecentAlgorithm
{
	template <class Archive>
	friend void serialize(Archive& archive, RMSPropLearningRate& rmsPropLearningRate);
	friend struct cereal::LoadAndConstruct<RMSPropLearningRate>;
private:
	// Holds for every edge its previous learning rate
	std::vector<Eigen::MatrixXd> prevGradient;
	std::vector<Eigen::MatrixXd> prevSquaredGradient;
	std::vector<Eigen::MatrixXd> prevDeltaWeights;
	RMSPropLearningRateOptions* getOptions();
public:
	RMSPropLearningRate(RMSPropLearningRateOptions& options_);
	RMSPropLearningRate();
	// Computes the new learning rate of the given edge from the given gradient
	Eigen::MatrixXd calcDeltaWeight(AbstractNetworkTopology* networkTopology, int layerIndex, Eigen::MatrixXd& gradients) override;
	// Returns if the learning has stopped
	bool learningHasStopped() override;
	// Initializes the ResilientLearningRateHelper
	void initializeAlgorithm(AbstractNetworkTopology* networkTopology) override;
};

#include "IO/RMSPropLearningRateIO.hpp"

#endif

