#pragma once

#ifndef _RBFNETWORK_H_
#define _RBFNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology/LayeredNetwork.hpp"

// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class RBFNetwork : public LayeredNetwork
{
private:
	Eigen::VectorXd neuronWidths;
public:
	RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer);		
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(double randStart, double randEnd);
	// Set all neuron centers to new random values between randStart and randEnd
	void randomizeCenters(double randStart, double randEnd);
	// Set all neuron centers to new random values between randStart and randEnd
	void randomizeWidths(double randStart, double randEnd);
	// Sets the center of the RBFNeuron with the given index
	void setCenterOfRBFNeuron(int neuronIndex, std::vector<double> &newCenterPosition);
	// Sets the width of the RBFNeuron with the given index
	void setWidthOfRBFNeuron(int neuronIndex, double newWidth);


};

#endif