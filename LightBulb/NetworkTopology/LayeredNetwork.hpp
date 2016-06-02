#pragma once

#ifndef _LAYEREDNETWORK_H_
#define _LAYEREDNETWORK_H_

// Libary includes
#include "EigenSrc/Dense"
#include <vector>
#include <memory>

// Includes
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Function/XorShfGenerator.hpp"

// Forward declarations
class AbstractNeuronDescriptionFactory;
class NeuronDescription;

// This struct contains all options needed to build a LayeredNetwork
struct LayeredNetworkOptions
{
	// Enables shourtcut edges
	bool enableShortcuts;
	// Specifies the neuron count of every layer
	std::vector<unsigned int> neuronsPerLayerCount;
	// Specifies which neurons of the last layer will be used as output neurons (if empty, the whole last layer will be used)
	std::vector<unsigned int> outputNeuronsIndices;

	bool useBiasNeuron;

	AbstractNeuronDescriptionFactory* descriptionFactory;
	LayeredNetworkOptions();
	~LayeredNetworkOptions();
	LayeredNetworkOptions(const LayeredNetworkOptions &obj);
};


// A LayeredNetwork describes a network with one input layer, multiple "hidden" layers and one output layer
class LayeredNetwork : public AbstractNetworkTopology
{
	template <class Archive>
	friend void load(Archive& archive, LayeredNetwork& layeredNetwork);
	template <class Archive>
	friend void save(Archive& archive, LayeredNetwork const & layeredNetwork);
protected:
	std::unique_ptr<LayeredNetworkOptions> options;
	//
	std::vector<Eigen::VectorXd> netInputs;
	//
	Eigen::VectorXd activations;
	
	std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> activationsPerLayerOut;

	std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> activationsPerLayerIn;

	std::vector<Eigen::MatrixXd> weights;

	std::vector<int> layerOffsets;

	std::vector<std::unique_ptr<NeuronDescription>> neuronDescriptionsPerLayer;
	// Builds the network from the given options
	void buildNetwork();
	// Refreshes the neuronPerLayerCounters
	void refreshNeuronsPerLayerCounters();
	// Rebuilds the output neurons vector from the outputNeuronsIndices option
	void rebuildOutputNeurons();

	XorShfGenerator randGenerator;

	void rebuildActivationsPerLayer(int layerIndex);
public:
	virtual ~LayeredNetwork();
	LayeredNetwork(LayeredNetworkOptions &options_);
	LayeredNetwork();
	
	AbstractActivationFunction* getOutputActivationFunction();

	void setInput(std::vector<std::pair<bool, double>> &inputVector);

	void getOutput(std::vector<std::pair<bool, double>> &outputVector);

	void setInput(std::vector<double> &inputVector);

	void getOutput(std::vector<double> &outputVector);
	// Calculates the layer count
	virtual int getLayerCount();
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
	void mergeWith(LayeredNetwork& otherNetwork);
	// Merge this network with another one
	virtual void horizontalMergeWith(LayeredNetwork& otherNetwork);
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

	virtual void refreshNetInputsForLayer(int layerNr);

	virtual void refreshActivationsForLayer(int layerNr);

	std::vector<Eigen::MatrixXd>* getWeights();

	std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>* getActivations();

	std::vector<Eigen::VectorXd>* getNetInputs();

	double calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork);

	int getNeuronCountInLayer(int layerNr);

	std::vector<unsigned int> getNeuronCountsPerLayer();

	double getBiasWeightOfNeuron(int layerNr, int neuronNr);

	std::vector<double> getAfferentWeights(int layerNr, int neuronNr, bool withoutBiasWeight = false);

	std::vector<int> getLayerOffsets();

	int getAfferentEdgeCount(int layerIndex, int neuronIndex);

	double getPrevNeuronActivation(int layerIndex, int neuronIndex, int edgeIndex);
	
	double getWeight(int layerIndex, int neuronIndex, int edgeIndex);

	void setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight);

	double getNetInput(int layerIndex, int neuronIndex);

	Eigen::VectorXd getNetInputVector(int layerIndex);

	Eigen::VectorXd getEfferentWeightVector(int layerIndex, int neuronIndex);

	AbstractActivationFunction* getInnerActivationFunction();

	Eigen::VectorXd getActivationVector(int layerIndex);

	Eigen::MatrixXd getAfferentWeightsPerLayer(int layerIndex);

	void setAfferentWeightsPerLayer(int layerIndex, Eigen::MatrixXd& newWeights);

	Eigen::MatrixXd getEfferentWeightsPerLayer(int layerIndex);

	bool usesBiasNeuron();

	void removeNeuron(int layerIndex, int neuronIndex);

	void addNeuron(int layerIndex);

	void removeAfferentWeight(int layerIndex, int neuronIndex, int weightIndex);

	bool existsAfferentWeight(int layerIndex, int neuronIndex, int weightIndex);

	int getNeuronCount();
};

#include "IO/LayeredNetworkIO.hpp"
#endif
