#pragma once

#ifndef _ABSTRACTNETWORKTOPOLOGY_H_
#define _ABSTRACTNETWORKTOPOLOGY_H_

// Library includes
#include <vector>
#include <map>
#include <Function/AbstractActivationFunction.hpp>

// Forward declarations
class InputNeuron;
class AbstractNeuron;
class StandardNeuron;
class Edge;
class BiasNeuron;

// A NetworkTopology is used to describe the structure of a NeuralNetwork
class AbstractNetworkTopology
{
private:
public:	
	virtual ~AbstractNetworkTopology() {}

	virtual AbstractActivationFunction* getOutputActivationFunction() = 0;

	virtual AbstractActivationFunction* getInnerActivationFunction() = 0;
	// Returns all InputNeurons in the NeuralNetwork
	virtual std::vector<AbstractNeuron*>* getInputNeurons() = 0;
	// Returns all OutputNeurons in the NeuralNetwork
	virtual std::vector<StandardNeuron*>* getOutputNeurons() = 0;
	// Set all weights to new random values between randStart and randEnd
	virtual void randomizeWeights(double randStart, double randEnd) = 0;
	// Returns all Neurons
	virtual std::vector<std::vector<StandardNeuron*>>* getNeurons() = 0;
	// Calculates the Edge count
	virtual int getEdgeCount() = 0;
	// Reset the activation of all neurons
	virtual void resetActivation() = 0;
	// Puts all current neuronOutputValues into the given map
	virtual void getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs) = 0;
	// Puts all current neuronNetInputValues into the given map
	virtual void getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs) = 0;
	// Copies the weight from all matching edges from the other network into the current one
	virtual void copyWeightsFrom(AbstractNetworkTopology& otherNetwork);

	virtual double calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork);
	// Returns the biasNeuron
	virtual BiasNeuron* getBiasNeuron() = 0;
	// Returns is the given neuron is an InputNeuron of this networkTopology
	bool isInputNeuron(AbstractNeuron* neuron);
	// Returns is the given neuron is an OutputNeuron of this networkTopology
	bool isOutputNeuron(StandardNeuron* neuron);

	virtual void getOutput(std::vector<std::pair<bool, double>> &outputVector);
	
	virtual void getOutput(std::vector<double> &outputVector);

	virtual void setInput(std::vector<double> &inputVector);

	virtual int getOutputSize() { return getOutputNeurons()->size(); }

	virtual int getNeuronCountInLayer(int layerIndex) = 0;

	virtual int getLayerCount() = 0;

	virtual int getAfferentEdgeCount(int layerIndex, int neuronIndex) = 0;

	virtual double getPrevNeuronActivation(int layerIndex, int neuronIndex, int edgeIndex) = 0;

	virtual double getWeight(int layerIndex, int neuronIndex, int edgeIndex) = 0;

	virtual void setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight) = 0;

	virtual double getNetInput(int layerIndex, int neuronIndex) = 0;

	virtual Eigen::VectorXd getNetInputVector(int layerIndex) = 0;

	virtual Eigen::VectorXd getEfferentWeightVector(int layerIndex, int neuronIndex) = 0;

	virtual Eigen::VectorXd getActivationVector(int layerIndex) = 0;

	virtual Eigen::MatrixXd getAfferentWeightsPerLayer(int layerIndex) = 0;

	virtual void setAfferentWeightsPerLayer(int layerIndex, Eigen::MatrixXd& newWeights) = 0;
};

#endif
