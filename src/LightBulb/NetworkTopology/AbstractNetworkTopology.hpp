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

	/**
	 * \brief A network topology is used to describe the structure of a neural network
	 * \details It consists of multiple layers with multiple neurons which are connected with each other by weights.
	 */
	class AbstractNetworkTopology
	{
	private:
	public:
		virtual ~AbstractNetworkTopology() {};
		/**
		 * \brief Returns the amount of edges.
		 * \return The edge count.
		 */
		virtual int getEdgeCount() const = 0;
		/**
		 * \brief Returns the input size of the network.
		 * \return The input size.
		 */
		virtual int getInputSize() const = 0;
		/**
		 * \brief Returns the output size of the network.
		 * \return The output size.
		 */
		virtual int getOutputSize() const = 0;
		/**
		 * \brief Sets the input of the network.
		 * \param inputVector The input vector. Should be as big as the input size of the network.
		 */
		virtual void setInput(const std::vector<double> &inputVector) = 0;
		/**
		 * \brief Returns the current output of the network.
		 * \param outputVector A vector which contains the current output.
		 */
		virtual void getOutput(std::vector<double> &outputVector) const = 0;
		/**
		 * \brief Sets the activation of all neurons back to zero.
		 */
		virtual void resetActivation() = 0;
		/**
		 * \brief Copies the whole structure of the given network.
		 * \param otherNetwork The network which should be copied.
		 */
		virtual void copyWeightsFrom(const AbstractNetworkTopology& otherNetwork) = 0;
		/**
		 * \brief Returns the whole amount of neurons in the network.
		 * \return The neuron count.
		 */
		virtual int getNeuronCount() const = 0;
		/**
		 * \brief Calculates the euclidean distance between the two networks.
		 * \details \f$ d=\sqrt{\sum{(w_{1,i,j} - w_{2,i,j})^2}} \f$
		 * \param otherNetwork The other network.
		 * \return The euclidean distance.
		 */
		virtual double calculateEuclideanDistance(const AbstractNetworkTopology& otherNetwork) const = 0;
		/**
		 * \brief Randomizes all weights.
		 * \param randomGenerator The random generator which should be used for randomizing.
		 * \param randStart The lower boundary of the random weights.
		 * \param randEnd The higher boundary of the random weights.
		 */
		virtual void randomizeWeights(AbstractRandomGenerator& randomGenerator, double randStart, double randEnd) = 0;
		/**
		 * \brief Returns the count of layers in the network.
		 * \return The layer count.
		 */
		virtual int getLayerCount() const = 0;
		/**
		 * \brief Returns the distribution of neurons over all layers.
		 * \return A vector which stores the count of neurons for every layer.
		 */
		virtual const std::vector<unsigned int>& getNeuronCountsPerLayer() const = 0;
		/**
		 * \brief Randomizes all weights and sets the boundaries depending on the layer sizes.
		 * \details \$f max = 1 / \sqrt{layersize} \n min = -max \$f
		 * \param randomGenerator The random generator which should be used for randomizing.
		 */
		virtual void randomizeDependingOnLayerSize(AbstractRandomGenerator& randomGenerator) = 0;
		/**
		 * \brief Recalculates the net inputs for one layer.
		 * \param layerNr The index of the layer.
		 */
		virtual void refreshNetInputsForLayer(int layerNr) = 0;
		/**
		 * \brief Recalculates the activations for one layer.
		 * \param layerNr The index of the layer.
		 */
		virtual void refreshActivationsForLayer(int layerNr) = 0;
		/**
		 * \brief Returns a pointer to all weights.
		 * \return A pointer to a vector of all weight matrices per layer.
		 */
		virtual std::vector<Eigen::MatrixXd>& getAllWeights() = 0;
		virtual const std::vector<Eigen::MatrixXd>& getAllWeights() const = 0;
		/**
		 * \brief Returns a pointer to all activations.
		 * \return A pointer to a vector of all activation vectors per layer.
		 */
		virtual const std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& getAllActivations() const = 0;
		/**
		 * \brief Returns a pointer to all net inputs.
		 * \return  A pointer to a vector of all net input vectors per layer.
		 */
		virtual const std::vector<Eigen::VectorXd>& getAllNetInputs() const = 0;
		/**
		 * \brief Returns all afferent weights for a layer.
		 * \param layerIndex The index of the layer.
		 * \return A copy of the afferent weights of the layer.
		 */
		virtual Eigen::MatrixXd getAfferentWeightsPerLayer(int layerIndex) const = 0;
		/**
		 * \brief Sets the afferent weights of a layer.
		 * \param layerIndex The index of the layer.
		 * \param newWeights The new afferent weights.
		 */
		virtual void setAfferentWeightsPerLayer(int layerIndex, const Eigen::MatrixXd& newWeights) = 0;
		/**
		 * \brief Returns all efferent weights for a layer.
		 * \param layerIndex The index of the layer.
		 * \return A copy of the efferent weights of the layer.
		 */
		virtual Eigen::MatrixXd getEfferentWeightsPerLayer(int layerIndex) const = 0;
		/**
		 * \brief Returns all net inputs for a layer.
		 * \param layerIndex The index of the layer.
		 * \return A copy of the net inputs of the layer.
		 */
		virtual Eigen::VectorXd getNetInputsPerLayer(int layerIndex) const = 0;
		/**
		* \brief Returns all net inputs for a layer.
		* \param layerIndex The index of the layer.
		* \return A copy of the net inputs of the layer.
		*/
		virtual Eigen::VectorXd getActivationsPerLayer(int layerIndex) const = 0;
		/**
		 * \brief Returns all efferent weights for a neuron.
		 * \param layerIndex The layer index of the neuron.
		 * \param neuronIndex The neuron index inside the layer.
		 * \return A copy of the efferent weights of the neuron.
		 */
		virtual Eigen::VectorXd getEfferentWeightsPerNeuron(int layerIndex, int neuronIndex) const = 0;
		/**
		 * \brief Returns the bias weight of a neuron.
		 * \param layerNr The layer index of the neuron.
		 * \param neuronNr The neuron index inside the layer.
		 * \return The bias weight.
		 */
		virtual double getBiasWeightOfNeuron(int layerNr, int neuronNr) const = 0;
		/**
		 * \brief Returns all afferent weights for a neuron.
		 * \param layerNr The layer index of the neuron.
		 * \param neuronIndex The neuron index inside the layer.
		 * \param withoutBiasWeight If true the bias weight is skipped.
		 * \return A copy of the afferent weights of the neuron.
		 */
		virtual std::vector<double> getAfferentWeightsPerNeuron(int layerNr, int neuronIndex, bool withoutBiasWeight = false) const = 0;

		/**
		 * \brief Returns one efferent weight of a neuron.
		 * \param layerIndex The layer index of the neuron.
		 * \param neuronIndex The neuron index inside the layer.
		 * \param edgeIndex The edge index of the neuron.
		 * \return The efferent weight.
		 */
		virtual double getWeight(int layerIndex, int neuronIndex, int edgeIndex) const = 0;
		/**
		 * \brief Sets one efferent weight of a neuron.
		 * \param layerIndex The layer index of the neuron.
		 * \param neuronIndex The neuron index inside the layer.
		 * \param edgeIndex The edge index of the neuron.
		 * \param weight The weight index.
		 */
		virtual void setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight) = 0;
		/**
		 * \brief Returns the current net input of a neuron.
		 * \param layerIndex The layer index of the neuron. 
		 * \param neuronIndex The neuron index inside the layer.
		 * \return The net input of the neuron.
		 */
		virtual double getNetInput(int layerIndex, int neuronIndex) const = 0;
		/**
		 * \brief Returns the current activation of a neuron
		 * \param layerIndex The layer index of the neuron. 
		 * \param neuronIndex The neuron index inside the layer.
		 * \return The net input of the neuron.
		 */
		virtual double getActivation(int layerIndex, int neuronIndex) const = 0;
		/**
		 * \brief Returns if the network uses a bias neuron.
		 * \return True if the network has a bias neuron.
		 */
		virtual bool usesBiasNeuron() const = 0;
		/**
		 * \brief Remove a neuron.
		 * \param layerIndex The layer index of the neuron. 
		 * \param neuronIndex The neuron index inside the layer.
		 */
		virtual void removeNeuron(int layerIndex, int neuronIndex) = 0;
		/**
		 * \brief Adds a new neuron at the end of a layer.
		 * \param layerIndex The index of the layer.
		 */
		virtual void addNeuron(int layerIndex) = 0;
		/**
		 * \brief Removes an afferent weight of a neuron.
		 * \param layerIndex The index of the layer.
		 * \param neuronIndex The neuron index inside the layer.
		 * \param weightIndex The weight index.
		 */
		virtual void removeAfferentWeight(int layerIndex, int neuronIndex, int weightIndex) = 0;
		/**
		 * \brief Returns if an afferent weight exists.
		 * \param layerIndex The index of the layer.
		 * \param neuronIndex The neuron index inside the layer.
		 * \param weightIndex The weight index.
		 * \return True, if the weight exists.
		 */
		virtual bool existsAfferentWeight(int layerIndex, int neuronIndex, int weightIndex) = 0;
		/**
		 * \brief Clones the whole network.
		 * \return The new network which is clone of this one.
		 */
		virtual AbstractNetworkTopology* clone() const = 0;
		/**
		 * \brief Returns the neuron description of inner/hidden neurons.
		 * \return The neuron description
		 */
		virtual const NeuronDescription& getInnerNeuronDescription() const = 0;
		/**
		* \brief Returns the neuron description of output neurons.
		* \return The neuron description
		*/
		virtual const NeuronDescription& getOutputNeuronDescription() const = 0;
	};

}

#endif
