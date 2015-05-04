#pragma once

#ifndef _RBFNETWORK_H_
#define _RBFNETWORK_H_

// Libary includes

// Includes
#include "LayeredNetwork.hpp"

// Forward declarations


// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class RBFNetwork : public LayeredNetwork
{
private:	
public:
	RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer);		
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(float randStart, float randEnd);
	// Set all neuron centers to new random values between randStart and randEnd
	void randomizeCenters(float randStart, float randEnd);
	// Set all neuron centers to new random values between randStart and randEnd
	void randomizeWidths(float randStart, float randEnd);
	// Sets the center of the RBFNeuron with the given index
	void setCenterOfRBFNeuron(int neuronIndex, std::vector<float> &newCenterPosition);
	// Sets the width of the RBFNeuron with the given index
	void setWidthOfRBFNeuron(int neuronIndex, float newWidth);
};

#endif