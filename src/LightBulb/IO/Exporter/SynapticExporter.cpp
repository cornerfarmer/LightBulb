// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/Exporter/SynapticExporter.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/IO/Exporter/JSONObject.hpp"
#include "LightBulb/IO/Exporter/JSONArray.hpp"
#include "LightBulb/IO/Exporter/JSONNumberElement.hpp"
#include "LightBulb/IO/Exporter/JSONStringElement.hpp"
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"
#include "LightBulb/Function/ActivationFunction/BinaryFunction.hpp"
#include "LightBulb/Function/ActivationFunction/FermiFunction.hpp"
#include "LightBulb/Function/ActivationFunction/HyperbolicTangentFunction.hpp"
#include "LightBulb/Function/ActivationFunction/IdentityFunction.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"

namespace LightBulb
{
	std::string SynapticExporter::exportToString(const AbstractNeuralNetwork& neuralNetwork)
	{
		networkTopology = dynamic_cast<FeedForwardNetworkTopology*>(&neuralNetwork.getNetworkTopology());

		std::unique_ptr<JSONObject> jsonObject(getNetworkJSONObject());

		return jsonObject->toString();
	}

	std::string SynapticExporter::getFileExtensions() const
	{
		return "Synaptic network (*.json)|*.json";;
	}

	std::string SynapticExporter::getName() const
	{
		return "Synaptic";
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
		const NeuronDescription* neuronDescription;
		if (layerIndex < networkTopology->getLayerCount() - 1)
			neuronDescription = &networkTopology->getInnerNeuronDescription();
		else
			neuronDescription = &networkTopology->getOutputNeuronDescription();

		if (dynamic_cast<const RectifierFunction*>(&neuronDescription->getActivationFunction()))
			return new JSONAttribute("squash", new JSONStringElement("RELU"));
		else if (dynamic_cast<const BinaryFunction*>(&neuronDescription->getActivationFunction()))
			return new JSONAttribute("squash", new JSONStringElement("HLIM"));
		else if (dynamic_cast<const IdentityFunction*>(&neuronDescription->getActivationFunction()))
			return new JSONAttribute("squash", new JSONStringElement("IDENTITY"));
		else if (dynamic_cast<const FermiFunction*>(&neuronDescription->getActivationFunction()))
			return new JSONAttribute("squash", new JSONStringElement("LOGISTIC"));
		else if (dynamic_cast<const HyperbolicTangentFunction*>(&neuronDescription->getActivationFunction()))
			return new JSONAttribute("squash", new JSONStringElement("TANH"));
		else
			return new JSONAttribute("squash", new JSONStringElement("LOGISTIC"));
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
			layer = std::to_string(layerIndex - 1);
		}
		return new JSONAttribute("layer", new JSONStringElement(layer));
	}

	JSONAttribute* SynapticExporter::getConnectionsAttribute()
	{
		JSONArray* connections = new JSONArray();

		for (int layerIndex = 1; layerIndex < networkTopology->getLayerCount(); layerIndex++)
		{
			weights = &networkTopology->getAllWeights()[layerIndex - 1];
			for (int sourceNeuronIndex = 1; sourceNeuronIndex < weights->getEigenValue().cols(); sourceNeuronIndex++)
			{
				for (int destinationNeuronIndex = 0; destinationNeuronIndex < weights->getEigenValue().rows(); destinationNeuronIndex++)
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
		return new JSONAttribute("from", new JSONNumberElement<int>(getTotalIndexOfNeuron(layerIndex - 1, sourceNeuronIndex - 1)));
	}

	JSONAttribute* SynapticExporter::getConnectionToAttribute(int layerIndex, int destinationNeuronIndex)
	{
		return new JSONAttribute("to", new JSONNumberElement<int>(getTotalIndexOfNeuron(layerIndex, destinationNeuronIndex)));
	}

	JSONAttribute* SynapticExporter::getConnectionWeightAttribute(int sourceNeuronIndex, int destNeuronIndex)
	{
		return new JSONAttribute("weight", new JSONNumberElement<double>((*weights).getEigenValue()(destNeuronIndex, sourceNeuronIndex)));
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
}
