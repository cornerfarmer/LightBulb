// Includes
#include "IO/SynapticExporter.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "IO/JSONObject.hpp"
#include "IO/JSONArray.hpp"
#include "IO/JSONNumberElement.hpp"
#include "IO/JSONStringElement.hpp"

std::string SynapticExporter::execute(NeuralNetwork* neuralNetwork)
{
	networkTopology = dynamic_cast<FeedForwardNetworkTopology*>(neuralNetwork->getNetworkTopology());

	std::unique_ptr<JSONObject> jsonObject(getNetworkJSONObject());
	return jsonObject->toString();
}

JSONObject* SynapticExporter::getNetworkJSONObject()
{
	JSONObject* jsonObject = new JSONObject();

	jsonObject->addAttribute(getNeuronsAttribute());
	jsonObject->addAttribute(getConnectionsAttribute());

	return jsonObject;
}

JSONAttribute* SynapticExporter::getNeuronsAttribute()
{
	JSONArray* neurons = new JSONArray();
	for (int l = 0; l < networkTopology->getLayerCount(); l++)
	{
		int neuronCount = networkTopology->getNeuronCountsPerLayer()[l];
		for (int n = 0; n < neuronCount; n++)
		{
			neurons->addElement(getNeuronJSONObject(l, n));
		}
	}
	return new JSONAttribute("neurons", neurons);
}

JSONObject* SynapticExporter::getNeuronJSONObject(int layerIndex, int neuronIndex)
{
	JSONObject* neuron = new JSONObject();
	neuron->addAttribute(getNeuronBiasAttribute(layerIndex, neuronIndex));
	neuron->addAttribute(getNeuronLayerAttribute(layerIndex, neuronIndex));
	neuron->addAttribute(getNeuronSquashAttribute(layerIndex, neuronIndex));	
	return neuron;
}

JSONAttribute* SynapticExporter::getNeuronSquashAttribute(int layerIndex, int neuronIndex)
{
	return new JSONAttribute("squash", new JSONStringElement("HLIM"));
}

JSONAttribute* SynapticExporter::getNeuronBiasAttribute(int layerIndex, int neuronIndex)
{
	double bias = 0;
	if (layerIndex > 0)
	{
		bias = networkTopology->getBiasWeightOfNeuron(layerIndex, neuronIndex);
	}
	return new JSONAttribute("bias", new JSONNumberElement<double>(bias));
}

JSONAttribute* SynapticExporter::getNeuronLayerAttribute(int layerIndex, int neuronIndex)
{
	std::string layer;
	if (layerIndex == 0) {
		layer = "input";
	}
	else if (layerIndex == networkTopology->getLayerCount() - 1) {
		layer = "output";
	}
	else {
		layer = std::to_string((_ULonglong)(layerIndex - 1));
	}
	return new JSONAttribute("layer", new JSONStringElement(layer));
}

JSONAttribute* SynapticExporter::getConnectionsAttribute()
{
	JSONArray* connections = new JSONArray();
	
	for (int layerIndex = 1; layerIndex < networkTopology->getLayerCount(); layerIndex++)
	{
		weights = &(*networkTopology->getAllWeights())[layerIndex - 1];
		for (int sourceNeuronIndex = 0; sourceNeuronIndex < weights->cols() - 1; sourceNeuronIndex++)
		{
			for (int destinationNeuronIndex = 0; destinationNeuronIndex < weights->rows(); destinationNeuronIndex++)
			{
				connections->addElement(getConnectionJSONObject(layerIndex, sourceNeuronIndex, destinationNeuronIndex));
			}
		}
	}
	return new JSONAttribute("connections", connections);
}

JSONObject* SynapticExporter::getConnectionJSONObject(int layerIndex, int sourceNeuronIndex, int destinationNeuronIndex)
{
	JSONObject* connection = new JSONObject();

	connection->addAttribute(getConnectionFromAttribute(layerIndex, sourceNeuronIndex));
	connection->addAttribute(getConnectionToAttribute(layerIndex, destinationNeuronIndex));
	connection->addAttribute(getConnectionWeightAttribute(sourceNeuronIndex, destinationNeuronIndex));

	return connection;
}

JSONAttribute* SynapticExporter::getConnectionFromAttribute(int layerIndex, int sourceNeuronIndex)
{
	return new JSONAttribute("from", new JSONNumberElement<int>(getTotalIndexOfNeuron(layerIndex - 1, sourceNeuronIndex)));
}

JSONAttribute* SynapticExporter::getConnectionToAttribute(int layerIndex, int destinationNeuronIndex)
{
	return new JSONAttribute("to", new JSONNumberElement<int>(getTotalIndexOfNeuron(layerIndex, destinationNeuronIndex)));
}

JSONAttribute* SynapticExporter::getConnectionWeightAttribute(int sourceNeuronIndex, int destNeuronIndex)
{
	return new JSONAttribute("weight", new JSONNumberElement<double>((*weights)(destNeuronIndex, sourceNeuronIndex)));
}

int SynapticExporter::getTotalIndexOfNeuron(int layerIndex, int neuronIndex)
{
	int totalIndex = 0;
	for (int l = 0; l < layerIndex; l++)
	{
		totalIndex += networkTopology->getNeuronCountsPerLayer()[l];
	}
	return totalIndex + neuronIndex;
}
