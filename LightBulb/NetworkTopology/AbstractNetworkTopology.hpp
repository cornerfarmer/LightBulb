#pragma once

#ifndef _ABSTRACTNETWORKTOPOLOGY_H_
#define _ABSTRACTNETWORKTOPOLOGY_H_

// Includes

// Library includes
#include "EigenSrc/Dense"
#include <vector>
#include <memory>
#include "Function/ActivationFunction/AbstractActivationFunction.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractRandomGenerator;
	class NeuronDescription;

	// A NetworkTopology is used to describe the structure of a NeuralNetwork
	class AbstractNetworkTopology
	{
	private:
	public:
		virtual int getEdgeCount() = 0;

		virtual int getInputSize() = 0;

		virtual int getOutputSize() = 0;

		virtual void setInput(std::vector<double> &inputVector) = 0;

		virtual void getOutput(std::vector<double> &outputVector) = 0;

		virtual void resetActivation() = 0;

		virtual void copyWeightsFrom(AbstractNetworkTopology& otherNetwork) = 0;

		virtual int getNeuronCount() = 0;

		virtual double calculateEuclideanDistance(AbstractNetworkTopology& otherNetwork) = 0;

		virtual void randomizeWeights(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd) = 0;


		virtual int getLayerCount() = 0;

		virtual std::vector<unsigned int> getNeuronCountsPerLayer() = 0;


		virtual void randomizeDependingOnLayerSize(AbstractRandomGenerator* randomGenerator) = 0;

		virtual void refreshNetInputsForLayer(int layerNr) = 0;

		virtual void refreshActivationsForLayer(int layerNr) = 0;

		virtual std::vector<Eigen::MatrixXd>* getAllWeights() = 0;

		virtual std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>>* getAllActivations() = 0;

		virtual std::vector<Eigen::VectorXd> getActivationsCopy() = 0;

		virtual std::vector<Eigen::VectorXd>* getAllNetInputs() = 0;


		virtual Eigen::MatrixXd getAfferentWeightsPerLayer(int layerIndex) = 0;

		virtual void setAfferentWeightsPerLayer(int layerIndex, Eigen::MatrixXd& newWeights) = 0;

		virtual Eigen::MatrixXd getEfferentWeightsPerLayer(int layerIndex) = 0;

		virtual Eigen::VectorXd getNetInputsPerLayer(int layerIndex) = 0;

		virtual Eigen::VectorXd getActivationsPerLayer(int layerIndex) = 0;


		virtual Eigen::VectorXd getEfferentWeightsPerNeuron(int layerIndex, int neuronIndex) = 0;

		virtual double getBiasWeightOfNeuron(int layerNr, int neuronNr) = 0;

		virtual std::vector<double> getAfferentWeightsPerNeuron(int layerNr, int neuronIndex, bool withoutBiasWeight = false) = 0;

		virtual double getWeight(int layerIndex, int neuronIndex, int edgeIndex) = 0;

		virtual void setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight) = 0;

		virtual double getNetInput(int layerIndex, int neuronIndex) = 0;

		virtual double getActivation(int layerIndex, int neuronIndex) = 0;

		virtual bool usesBiasNeuron() = 0;

		virtual void removeNeuron(int layerIndex, int neuronIndex) = 0;

		virtual void addNeuron(int layerIndex) = 0;

		virtual void removeAfferentWeight(int layerIndex, int neuronIndex, int weightIndex) = 0;

		virtual bool existsAfferentWeight(int layerIndex, int neuronIndex, int weightIndex) = 0;

		virtual AbstractNetworkTopology* clone() = 0;

		virtual NeuronDescription* getInnerNeuronDescription() = 0;

		virtual NeuronDescription* getOutputNeuronDescription() = 0;
	};

}

#endif
