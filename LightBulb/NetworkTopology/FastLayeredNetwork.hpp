#pragma once

#ifndef _FASTLAYEREDNETWORK_H_
#define _FASTLAYEREDNETWORK_H_

// Libary includes
#include <vector>
#include <memory>

// Includes
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/BiasNeuron.hpp"
#include "Function/XorShfGenerator.hpp"

// Forward declarations
class AbstractNeuronFactory;
class AbstractActivationFunction;
class AbstractInputFunction;
class AbstractOutputFunction;
class AbstractThreshold;

// This struct contains all options needed to build a LayeredNetwork
struct FastLayeredNetworkOptions
{
	// Enables shourtcut edges
	bool enableShortcuts;
	// Enables a bias neuron
	bool useBiasNeuron;
	// Specifies the neuron count of every layer
	std::vector<unsigned int> neuronsPerLayerCount;
	// Specifies which neurons of the last layer will be used as output neurons (if empty, the whole last layer will be used)
	std::vector<unsigned int> outputNeuronsIndices;

	AbstractActivationFunction* activationFunction;

	AbstractInputFunction* inputFunction;

	AbstractOutputFunction* outputFunction;

	AbstractThreshold* threshold;
	FastLayeredNetworkOptions();
	~FastLayeredNetworkOptions();
	FastLayeredNetworkOptions(const FastLayeredNetworkOptions &obj);
};


// A FastLayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class FastLayeredNetwork : public AbstractNetworkTopology
{
protected:
	std::unique_ptr<FastLayeredNetworkOptions> options;
	//
	std::vector<double> netInputs;
	//
	std::vector<double> activations;

	std::vector<std::vector<double>> weights;

	std::vector<int> layerOffsets;
	// Builds the network from the given options
	void buildNetwork();
	// Refreshes the neuronPerLayerCounters
	void refreshNeuronsPerLayerCounters();
	// Rebuilds the output neurons vector from the outputNeuronsIndices option
	void rebuildOutputNeurons();

	XorShfGenerator randGenerator;
public:
	~FastLayeredNetwork();
	FastLayeredNetwork(FastLayeredNetworkOptions &options_);
	FastLayeredNetwork();

	void setInput(std::vector<std::pair<bool, double>>* inputVector);

	void getOutput(std::vector<std::pair<bool, double>> &outputVector);

	void setInput(std::vector<double>* inputVector);

	void getOutput(std::vector<double> &outputVector);
	// Calculates the layer count
	int getLayerCount();
	// Returns all Neurons
	std::vector<std::vector<StandardNeuron*>>* getNeurons();
	// Set all weights to new random values between randStart and randEnd
	void randomizeWeights(double randStart, double randEnd);
	// Adds a new neuron into the specified layer
	AbstractNeuron* addNeuronIntoLayer(int layerIndex, bool refreshNeuronCounters, bool addEdgesToNextLayer);
	// Removes the neuron with given index from a layer
	void removeNeuronFromLayer(int layerIndex, int neuronIndex);
	// Removes the givem neuron from a layer
	void removeNeuronFromLayer(int layerIndex, AbstractNeuron* neuronToRemove);
	// Adds a new layer
	void addNewLayer(int layerIndex, int initialNeuronCount);
	// Adds a given neuron to a layer
	void addNeuronIntoLayer(int layerIndex, AbstractNeuron* newNeuron, bool refreshNeuronCounters);
	// Calculates the Edge count
	int getEdgeCount();
	// Reset all activations of all neurons
	void resetActivation();
	// Merge this network with another one (The neurons of the otherNetwork will be removed from it)
	void mergeWith(FastLayeredNetwork& otherNetwork);
	// Merge this network with another one
	virtual void horizontalMergeWith(FastLayeredNetwork& otherNetwork);
	// Returns a map which holds for every edge the information if it is recurrent or not
	virtual std::unique_ptr<std::map<Edge*, bool>> getNonRecurrentEdges();
	// Puts all current neuron outputs into the given map
	void getAllNeuronOutputs(std::map<AbstractNeuron*, double>& neuronOutputs);
	// Puts all current neuron net inputs into the given map
	void getAllNeuronNetInputs(std::map<AbstractNeuron*, double>& neuronNetInputs);

	// Returns all InputNeurons in the NeuralNetwork
	std::vector<AbstractNeuron*>* getInputNeurons();
	// Returns all OutputNeurons in the NeuralNetwork
	std::vector<StandardNeuron*>* getOutputNeurons();

	BiasNeuron* getBiasNeuron();

	int getOutputSize();

	void copyWeightsFrom(AbstractNetworkTopology& otherNetwork);

	void refreshNetInputsForLayer(int layerNr);

	void refreshActivationsForLayer(int layerNr);

	std::vector<std::vector<double>>* getWeights();

	double calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork);

	int getNeuronCountInLayer(int layerNr);

	double getBiasWeightOfNeuron(int layerNr, int neuronNr);

	std::vector<double> getAfferentWeights(int layerNr, int neuronNr);
};

#endif
