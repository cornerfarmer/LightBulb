// Includes
#include "IO/SynapticExporter.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "IO/JSONObject.hpp"
#include "IO/JSONArray.hpp"
#include "IO/JSONNumberElement.hpp"
#include "IO/JSONStringElement.hpp"

std::string SynapticExporter::execute(NeuralNetwork* neuralNetwork)
{
	layeredNetwork = dynamic_cast<LayeredNetwork*>(neuralNetwork->getNetworkTopology());

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
	for (int l = 0; l < layeredNetwork->getLayerCount(); l++)
	{
		int neuronCount = layeredNetwork->getNeuronCountInLayer(l);
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
		bias = layeredNetwork->getBiasWeightOfNeuron(layerIndex, neuronIndex);
	}
	return new JSONAttribute("bias", new JSONNumberElement<double>(bias));
}

JSONAttribute* SynapticExporter::getNeuronLayerAttribute(int layerIndex, int neuronIndex)
{
	std::string layer;
	if (layerIndex == 0) {
		layer = "input";
	}
	else if (layerIndex == layeredNetwork->getLayerCount() - 1) {
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
	/*weights = layeredNetwork->getWeights();
	for (int layerIndex = 0; layerIndex < layeredNetwork->getLayerCount(); layerIndex++)
	{
		for (int sourceNeuronIndex = layeredNetwork->getLayerOffsets()[layerIndex]; sourceNeuronIndex < layeredNetwork->getLayerOffsets()[layerIndex + 1]; sourceNeuronIndex++)
		{
			for (auto destNeuronIndex = 0; destNeuronIndex < (*weights)[sourceNeuronIndex].size(); destNeuronIndex++)
			{
				connections->addElement(getConnectionJSONObject(layerIndex, sourceNeuronIndex, destNeuronIndex));
			}
		}
	}*/
	return new JSONAttribute("connections", connections);
}

JSONObject* SynapticExporter::getConnectionJSONObject(int layerIndex, int sourceNeuronIndex, int destNeuronIndex)
{
	JSONObject* connection = new JSONObject();

	connection->addAttribute(getConnectionFromAttribute(sourceNeuronIndex));
	connection->addAttribute(getConnectionToAttribute(layerIndex, destNeuronIndex));
	connection->addAttribute(getConnectionWeightAttribute(sourceNeuronIndex, destNeuronIndex));

	return connection;
}

JSONAttribute* SynapticExporter::getConnectionFromAttribute(int sourceNeuronIndex)
{
	return new JSONAttribute("from", new JSONNumberElement<int>(sourceNeuronIndex));
}

JSONAttribute* SynapticExporter::getConnectionToAttribute(int layerIndex, int destNeuronIndex)
{
	return new JSONAttribute("to", new JSONNumberElement<int>(layeredNetwork->getLayerOffsets()[layerIndex + 1] + destNeuronIndex));
}

JSONAttribute* SynapticExporter::getConnectionWeightAttribute(int sourceNeuronIndex, int destNeuronIndex)
{
	return new JSONAttribute("weight", new JSONNumberElement<double>((*weights)[sourceNeuronIndex][destNeuronIndex]));
}
