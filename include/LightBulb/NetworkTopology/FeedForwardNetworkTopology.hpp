#pragma once

#ifndef _FEEDFORWARDNETWORKTOPOLOGY_H_
#define _FEEDFORWARDNETWORKTOPOLOGY_H_

// Libary includes
#include <vector>
#include <memory>

// Includes
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuronDescriptionFactory;
	class NeuronDescription;

	/**
	 * \brief This struct contains all options needed to build a FeedForwardNetworkTopology
	 */
	struct FeedForwardNetworkTopologyOptions
	{
		/**
		 * \brief Enables shourtcut edges.
		 * \details When this is true, all layers are connected to ALL following layers.\n
		 * Default: false
		 */
		bool enableShortcuts;
		/**
		 * \brief Specifies the neuron counts of every layer.
		 */
		std::vector<unsigned int> neuronsPerLayerCount;
		/**
		 * \brief Specifies if a bias neuron should be used.
		 * \details Default: true
		 */
		bool useBiasNeuron;
		/**
		 * \brief The factory which should provide the neuron descriptions for the network.
		 */
		AbstractNeuronDescriptionFactory* descriptionFactory;
		/**
		* \brief Creates the options and fills them with default options.
		*/
		FeedForwardNetworkTopologyOptions();
		~FeedForwardNetworkTopologyOptions();
		FeedForwardNetworkTopologyOptions(const FeedForwardNetworkTopologyOptions& other);
		FeedForwardNetworkTopologyOptions(FeedForwardNetworkTopologyOptions&& other) noexcept;
		FeedForwardNetworkTopologyOptions& operator=(FeedForwardNetworkTopologyOptions other);
		friend void swap(FeedForwardNetworkTopologyOptions& lhs, FeedForwardNetworkTopologyOptions& rhs) noexcept;
	};

	/**
	* \brief A feed forward network describes a network which has only forward connections.
	* \details It has one input layer, multiple "hidden" layers and one output layer.
	* The activation is forward propagated, so the network has no internal state.
	*/
	class FeedForwardNetworkTopology : public AbstractNetworkTopology
	{
		template <class Archive>
		friend void load(Archive& archive, FeedForwardNetworkTopology& feedForwardNetworkTopology);
		template <class Archive>
		friend void save(Archive& archive, FeedForwardNetworkTopology const & feedForwardNetworkTopology);
	private:
		TopologicalOrder defaultActivationOrder;
	protected:
		/**
		 * \brief The options of the network.
		 */
		std::unique_ptr<FeedForwardNetworkTopologyOptions> options;
		/**
		 * \brief All net inputs per layer.
		 */
		std::vector<Vector> netInputs;
		/**
		 * \brief All activations.
		 */
		std::vector<Vector> activations;
		/**
		 * \brief The weights per layer
		 */
		std::vector<Matrix> weights;
		/**
		 * \brief The offset of each layer in the activations vector.
		 */
		std::vector<int> layerOffsets;
		/**
		 * \brief All neuron descriptions per layer.
		 */
		std::vector<std::unique_ptr<NeuronDescription>> neuronDescriptionsPerLayer;
		/**
		 * \brief Builds the network from the given options
		 */
		void buildNetwork();
		/**
		 * \brief Rebuilds the vector block activations per layer.
		 * \note This has to be done when the activations vector has been changed.
		 */
		//void rebuildActivationsPerLayer();
	public:
		virtual ~FeedForwardNetworkTopology();
		/**
		* \brief Creates the feed forward network.
		* \param options_ The options which configure the network.
		*/
		FeedForwardNetworkTopology(FeedForwardNetworkTopologyOptions &options_);
		/**
		* \brief Creates a new feed forward network with default options.
		*/
		FeedForwardNetworkTopology();
		// Inherited:
		int getEdgeCount() const override;
		int getLayerCount() const override;
		int getNeuronCount() const override;
		int getInputSize() const override;
		int getOutputSize() const override;
		const std::vector<unsigned int>& getNeuronCountsPerLayer() const override;
		void setInput(const std::vector<double> &inputVector) override;
		void getOutput(std::vector<double> &outputVector) const override;
		void randomizeWeights(AbstractRandomGenerator& randomGenerator, double randStart, double randEnd) override;
		void randomizeDependingOnLayerSize(AbstractRandomGenerator& randomGenerator) override;
		void resetActivation() override;
		void copyWeightsFrom(const AbstractNetworkTopology& otherNetwork) override;
		void refreshNetInputsForLayer(int layerNr) override;
		void refreshActivationsForLayer(int layerNr) override;
		double calculateEuclideanDistance(const AbstractNetworkTopology& otherNetwork) const override;
		std::vector<Matrix>& getAllWeights() override;
		const std::vector<Matrix>& getAllWeights() const override;
		const std::vector<Vector>& getAllActivations() const override;
		const std::vector<Vector>& getAllNetInputs() const override;
		Matrix getAfferentWeightsPerLayer(int layerIndex) const override;
		void setAfferentWeightsPerLayer(int layerIndex, const Matrix& newWeights) override;
		Matrix getEfferentWeightsPerLayer(int layerIndex) const override;
		Vector getNetInputsPerLayer(int layerIndex) const override;
		Vector getActivationsPerLayer(int layerIndex) const override;
		Vector getEfferentWeightsPerNeuron(int layerIndex, int neuronIndex) const override;
		double getBiasWeightOfNeuron(int layerNr, int neuronNr) const override;
		std::vector<double> getAfferentWeightsPerNeuron(int layerNr, int neuronIndex, bool withoutBiasWeight = false) const override;
		double getWeight(int layerIndex, int neuronIndex, int edgeIndex) const override;
		void setWeight(int layerIndex, int neuronIndex, int edgeIndex, double weight) override;
		double getNetInput(int layerIndex, int neuronIndex) const override;
		double getActivation(int layerIndex, int neuronIndex) const override;
		bool usesBiasNeuron() const override;
		void removeNeuron(int layerIndex, int neuronIndex) override;
		void addNeuron(int layerIndex) override;
		void removeAfferentWeight(int layerIndex, int neuronIndex, int weightIndex) override;
		bool existsAfferentWeight(int layerIndex, int neuronIndex, int weightIndex) override;
		AbstractNetworkTopology* clone() const override;
		const NeuronDescription& getInnerNeuronDescription() const override;
		const NeuronDescription& getOutputNeuronDescription() const override;
		const AbstractActivationOrder& getDefaultActivationOrder() const override;
	};
}

#include "LightBulb/IO/FeedForwardNetworkTopologyIO.hpp"
#endif
