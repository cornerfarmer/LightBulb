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

	int getEdgeCount() override;

	int getLayerCount() override;

	int getNeuronCount() override;

	int getInputSize() override;

	int getOutputSize() override;

	std::vector<unsigned int> getNeuronCountsPerLayer() override;

	void setInput(std::vector<double> &inputVector) override;

	void getOutput(std::vector<double> &outputVector) override;
	
	void randomizeWeights(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd) override;

	void randomizeDependingOnLayerSize(AbstractRandomGenerator* randomGenerator) override;

	void resetActivation() override;
	
	void copyWeightsFrom(AbstractNetworkTopology& otherNetwork) override;

	void refreshNetInputsForLayer(int layerNr) override;

	void refreshActivationsForLayer(int layerNr) override;

	double calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork) override;

	std::vector<Eigen::MatrixXd>* getAllWeights() override;

	std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>* getAllActivations() override;

	std::vector<Eigen::VectorXd> getActivationsCopy() override;

	std::vector<Eigen::VectorXd>* getAllNetInputs() override;
	

	Eigen::MatrixXd getAfferentWeightsPerLayer(int layerIndex) override;

	void setAfferentWeightsPerLayer(int layerIndex, Eigen::MatrixXd& newWeights) override;

	Eigen::MatrixXd getEfferentWeightsPerLayer(int layerIndex) override;
	
	Eigen::VectorXd getNetInputsPerLayer(int layerIndex) override;
	
	Eigen::VectorXd getActivationsPerLayer(int layerIndex) override;
	

	Eigen::VectorXd getEfferentWeightsPerNeuron(int layerIndex, int neuronIndex) override;

	double getBiasWeightOfNeuron(int layerNr, int neuronNr) override;

	std::vector<double> getAfferentWeightsPerNeuron(int layerNr, int neuronIndex, bool withoutBiasWeight = false) override;
	
	double getWeight(int layerIndex, int neuronIndex, int edgeIndex) override;

	void setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight) override;

	double getNetInput(int layerIndex, int neuronIndex) override;

	double getActivation(int layerIndex, int neuronIndex) override;
	
	bool usesBiasNeuron() override;

	void removeNeuron(int layerIndex, int neuronIndex) override;

	void addNeuron(int layerIndex) override;

	void removeAfferentWeight(int layerIndex, int neuronIndex, int weightIndex) override;

	bool existsAfferentWeight(int layerIndex, int neuronIndex, int weightIndex) override;
	
	AbstractNetworkTopology* clone() override;

	NeuronDescription* getInnerNeuronDescription() override;

	NeuronDescription* getOutputNeuronDescription() override;
};

#include "IO/FeedForwardNetworkTopologyIO.hpp"
#endif
