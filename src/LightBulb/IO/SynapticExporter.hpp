#pragma once

#ifndef _SYNAPTICEXPORTER_H_
#define _SYNAPTICEXPORTER_H_

// Library includes
#include <vector>
#include <EigenSrc/Dense>

// Includes
#include "IO/AbstractExporter.hpp"

namespace LightBulb
{
	// Forward declarations
	class JSONObject;
	class JSONAttribute;
	class FeedForwardNetworkTopology;

	// 
	class SynapticExporter : public AbstractExporter
	{
	private:
		FeedForwardNetworkTopology* networkTopology;
		const Eigen::MatrixXd* weights;
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
		std::string execute(NeuralNetwork* neuralNetwork) override;
	};
}

#endif
