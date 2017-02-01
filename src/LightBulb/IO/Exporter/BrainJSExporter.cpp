// Includes
#include "LightBulb/IO/Exporter/BrainJSExporter.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/IO/Exporter/JSONObject.hpp"
#include "LightBulb/IO/Exporter/JSONArray.hpp"
#include "LightBulb/IO/Exporter/JSONNumberElement.hpp"

namespace LightBulb
{
	std::string BrainJSExporter::exportToString(const AbstractNeuralNetwork& neuralNetwork)
	{
		JSONObject jsonObject;
		JSONArray* layers = new JSONArray();
		FeedForwardNetworkTopology& networkTopology = dynamic_cast<FeedForwardNetworkTopology&>(neuralNetwork.getNetworkTopology());

		int layerCount = networkTopology.getLayerCount();
		for (int l = 0; l < layerCount; l++)
		{
			JSONObject* layer = new JSONObject();
			int neuronCount = networkTopology.getNeuronCountsPerLayer()[l];
			for (int n = 0; n < neuronCount; n++)
			{
				JSONObject* neuron = new JSONObject();
				if (l > 0)
				{
					neuron->addAttribute(new JSONAttribute("bias", new JSONNumberElement<double>(networkTopology.getBiasWeightOfNeuron(l, n))));

					JSONObject* weights = new JSONObject();
					std::vector<double> afferentWeights = networkTopology.getAfferentWeightsPerNeuron(l, n, true);
					for (int afferentWeightIndex = 0; afferentWeightIndex < afferentWeights.size(); afferentWeightIndex++)
					{
						weights->addAttribute(new JSONAttribute(std::to_string(afferentWeightIndex), new JSONNumberElement<double>(afferentWeights[afferentWeightIndex])));
					}
					neuron->addAttribute(new JSONAttribute("weights", weights));
				}
				layer->addAttribute(new JSONAttribute(std::to_string(n), neuron));
			}
			layers->addElement(layer);
		}
		jsonObject.addAttribute(new JSONAttribute("layers", layers));

		return jsonObject.toString();
	}

	std::string BrainJSExporter::getFileExtensions() const
	{
		return "BrainJS network (*.json)|*.json";
	}

	std::string BrainJSExporter::getName() const
	{
		return "BrainJS";
	}
}
