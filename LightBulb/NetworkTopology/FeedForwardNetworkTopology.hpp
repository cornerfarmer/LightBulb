#pragma once

#ifndef _FEEDFORWARDNETWORKTOPOLOGY_H_
#define _FEEDFORWARDNETWORKTOPOLOGY_H_

// Libary includes
#include "EigenSrc/Dense"
#include <vector>
#include <memory>

// Includes
#include "NetworkTopology/AbstractNetworkTopology.hpp"

// Forward declarations
class AbstractNeuronDescriptionFactory;
class NeuronDescription;

// This struct contains all options needed to build a FeedForwardNetworkTopology
struct FeedForwardNetworkTopologyOptions
{
	// Enables shourtcut edges
	bool enableShortcuts;
	// Specifies the neuron count of every layer
	std::vector<unsigned int> neuronsPerLayerCount;

	bool useBiasNeuron;

	AbstractNeuronDescriptionFactory* descriptionFactory;
	FeedForwardNetworkTopologyOptions();
	~FeedForwardNetworkTopologyOptions();
	FeedForwardNetworkTopologyOptions(const FeedForwardNetworkTopologyOptions &obj);
};


// A FeedForwardNetworkTopology describes a network with one input layer, multiple "hidden" layers and one output layer
class FeedForwardNetworkTopology : public AbstractNetworkTopology
{
	template <class Archive>
	friend void load(Archive& archive, FeedForwardNetworkTopology& FeedForwardNetworkTopology);
	template <class Archive>
	friend void save(Archive& archive, FeedForwardNetworkTopology const & FeedForwardNetworkTopology);
protected:
	std::unique_ptr<FeedForwardNetworkTopologyOptions> options;
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

	void rebuildActivationsPerLayer(int layerIndex);
public:
	virtual ~FeedForwardNetworkTopology();
	FeedForwardNetworkTopology(FeedForwardNetworkTopologyOptions &options_);
	FeedForwardNetworkTopology();

	int getEdgeCount();

	int getLayerCount();

	int getNeuronCount();

	int getInputSize();

	int getOutputSize();

	std::vector<unsigned int> getNeuronCountsPerLayer();

	void setInput(std::vector<double> &inputVector);

	void getOutput(std::vector<double> &outputVector);
	
	void randomizeWeights(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd);

	void randomizeDependingOnLayerSize(AbstractRandomGenerator* randomGenerator);

	void resetActivation();
	
	void copyWeightsFrom(AbstractNetworkTopology& otherNetwork);

	void refreshNetInputsForLayer(int layerNr);

	void refreshActivationsForLayer(int layerNr);

	double calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork);

	std::vector<Eigen::MatrixXd>* getAllWeights();

	std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>* getAllActivations();

	std::vector<Eigen::VectorXd> getActivationsCopy();

	std::vector<Eigen::VectorXd>* getAllNetInputs();
	

	Eigen::MatrixXd getAfferentWeightsPerLayer(int layerIndex);

	void setAfferentWeightsPerLayer(int layerIndex, Eigen::MatrixXd& newWeights);

	Eigen::MatrixXd getEfferentWeightsPerLayer(int layerIndex);
	
	Eigen::VectorXd getNetInputsPerLayer(int layerIndex);
	
	Eigen::VectorXd getActivationsPerLayer(int layerIndex);
	

	Eigen::VectorXd getEfferentWeightsPerNeuron(int layerIndex, int neuronIndex);

	double getBiasWeightOfNeuron(int layerNr, int neuronNr);

	std::vector<double> getAfferentWeightsPerNeuron(int layerNr, int neuronIndex, bool withoutBiasWeight = false);
	
	double getWeight(int layerIndex, int neuronIndex, int edgeIndex);

	void setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight);

	double getNetInput(int layerIndex, int neuronIndex);

	double getActivation(int layerIndex, int neuronIndex);
	
	bool usesBiasNeuron();

	void removeNeuron(int layerIndex, int neuronIndex);

	void addNeuron(int layerIndex);

	void removeAfferentWeight(int layerIndex, int neuronIndex, int weightIndex);

	bool existsAfferentWeight(int layerIndex, int neuronIndex, int weightIndex);
	
	AbstractNetworkTopology* clone();

	NeuronDescription* getInnerNeuronDescription();

	NeuronDescription* getOutputNeuronDescription();
};

#include "IO/FeedForwardNetworkTopologyIO.hpp"
#endif
