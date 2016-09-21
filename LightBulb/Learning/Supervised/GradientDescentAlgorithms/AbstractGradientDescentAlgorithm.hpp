#pragma once

#ifndef _ABSTRACTGRADIENTDESCENTALGORITHM_H_
#define _ABSTRACTGRADIENTDESCENTALGORITHM_H_

// Library Includes

// Includes
#include "Learning/AbstractLearningRule.hpp"
#include "IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	class AbstractNetworkTopology;

	struct AbstractGradientDescentAlgorithmOptions
	{
		int test;
		AbstractGradientDescentAlgorithmOptions()
		{
			test = 5;
		}

		virtual ~AbstractGradientDescentAlgorithmOptions() {}
	};


	class AbstractGradientDescentAlgorithm
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractGradientDescentAlgorithm& gradientDescentAlgorithm);
	private:
		bool initialized;
	protected:
		std::unique_ptr<AbstractGradientDescentAlgorithmOptions> options;
		virtual void initializeAlgorithm(AbstractNetworkTopology* networkTopology) = 0;
	public:
		AbstractGradientDescentAlgorithm(AbstractGradientDescentAlgorithmOptions* options_);
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
}

#include "IO/AbstractGradientDescentAlgorithmIO.hpp"

#endif

