#pragma once

#ifndef _SYNAPTICEXPORTER_H_
#define _SYNAPTICEXPORTER_H_

// Library includes
#include <vector>

// Includes
#include "LightBulb/IO/Exporter/AbstractNetworkExporter.hpp"

namespace LightBulb
{
	// Forward declarations
	class JSONObject;
	class Matrix;
	class JSONAttribute;
	class FeedForwardNetworkTopology;
	/**
	 * \brief Exports a neural network for using in Synaptic.
	 */
	class SynapticExporter : public AbstractNetworkExporter
	{
	private:
		FeedForwardNetworkTopology* networkTopology;
		const Matrix* weights;
		JSONObject* getNetworkJSONObject();
		JSONAttribute* getNeuronsAttribute();
		JSONObject* getNeuronJSONObject(int layer, int neuron);
		JSONAttribute* getNeuronSquashAttribute(int layer, int neuron);
		JSONAttribute* getNeuronBiasAttribute(int layer, int neuron);
		JSONAttribute* getNeuronLayerAttribute(int layer, int neuron);
		JSONAttribute* getConnectionsAttribute();
		JSONObject* getConnectionJSONObject(int layerIndex, int sourceNeuronIndex, int destNeuronIndex);
		JSONAttribute* getConnectionFromAttribute(int layerIndex, int sourceNeuronIndex);
		JSONAttribute* getConnectionToAttribute(int layerIndex, int destNeuronIndex);
		JSONAttribute* getConnectionWeightAttribute(int sourceNeuronIndex, int destNeuronIndex);
		int getTotalIndexOfNeuron(int layerIndex, int neuronIndex);
	public:
		// Inherited:
		std::string exportToString(const AbstractNeuralNetwork& neuralNetwork) override;
		std::string getName() const override;
		std::string getFileExtensions() const override;
	};
}

#endif
