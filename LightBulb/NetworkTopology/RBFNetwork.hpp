#pragma once

#ifndef _RBFNETWORK_H_
#define _RBFNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"

namespace LightBulb
{
	// A FeedForwardNetworkTopology describes a network with one input layer, multiple "hidden" layers and one output layer
	class RBFNetwork : public FeedForwardNetworkTopology
	{
		template <class Archive>
		friend void save(Archive& archive, RBFNetwork const & rbfNetwork);
		template <class Archive>
		friend void load(Archive& archive, RBFNetwork & rbfNetwork);
	private:
		Eigen::VectorXd neuronWidths;
	public:
		RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer);
		RBFNetwork();
		// Set all weights to new random values between randStart and randEnd
		void randomizeWeights(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd) override;
		// Set all neuron centers to new random values between randStart and randEnd
		void randomizeCenters(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd);
		// Set all neuron centers to new random values between randStart and randEnd
		void randomizeWidths(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd);
		// Sets the center of the RBFNeuron with the given index
		void setCenterOfRBFNeuron(int neuronIndex, std::vector<double> &newCenterPosition);
		// Sets the width of the RBFNeuron with the given index
		void setWidthOfRBFNeuron(int neuronIndex, double newWidth);

		double getWidthOfRBFNeuron(int neuronIndex);

		AbstractNetworkTopology* clone() override;
	};
}

#include "IO/RBFNetworkIO.hpp"

#endif