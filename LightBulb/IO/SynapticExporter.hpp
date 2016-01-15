#pragma once

#ifndef _SYNAPTICEXPORTER_H_
#define _SYNAPTICEXPORTER_H_

// Library includes
#include <vector>

// Includes
#include "IO/AbstractExporter.hpp"

// Forward declarations
class JSONObject;
class JSONAttribute;
class FastLayeredNetwork;

// 
class SynapticExporter : public AbstractExporter
{
private:
	FastLayeredNetwork* layeredNetwork;
	std::vector<std::vector<double>>* weights;
	JSONObject* getNetworkJSONObject();
	JSONAttribute* getNeuronsAttribute();
	JSONObject* getNeuronJSONObject(int layer, int neuron);
	JSONAttribute* getNeuronSquashAttribute(int layer, int neuron);
	JSONAttribute* getNeuronBiasAttribute(int layer, int neuron);
	JSONAttribute* getNeuronLayerAttribute(int layer, int neuron);
	JSONAttribute* getConnectionsAttribute();
	JSONObject* getConnectionJSONObject(int layerIndex, int sourceNeuronIndex, int destNeuronIndex);
	JSONAttribute* getConnectionFromAttribute(int sourceNeuronIndex);
	JSONAttribute* getConnectionToAttribute(int layerIndex, int destNeuronIndex);
	JSONAttribute* getConnectionWeightAttribute(int sourceNeuronIndex, int destNeuronIndex);
public:
	std::string execute(NeuralNetwork* neuralNetwork);
};

#endif
