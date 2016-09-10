// Includes
#include "IO/BrainJSExporter.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "IO/JSONObject.hpp"
#include "IO/JSONArray.hpp"
#include "IO/JSONNumberElement.hpp"

namespace LightBulb
{
	std::string BrainJSExporter::execute(NeuralNetwork* neuralNetwork)
	{
		JSONObject jsonObject;
		JSONArray* layers = new JSONArray();
		FeedForwardNetworkTopology* networkTopology = dynamic_cast<FeedForwardNetworkTopology*>(neuralNetwork->getNetworkTopology());

		int layerCount = networkTopology->getLayerCount();
		for (int l = 0; l < layerCount; l++)
		{
			JSONObject* layer = new JSONObject();
			int neuronCount = networkTopology->getNeuronCountsPerLayer()[l];
			for (int n = 0; n < neuronCount; n++)
			{
				JSONObject* neuron = new JSONObject();
				if (l > 0)
				{
					neuron->addAttribute(new JSONAttribute("bias", new JSONNumberElement<double>(networkTopology->getBiasWeightOfNeuron(l, n))));

					JSONObject* weights = new JSONObject();
					std::vector<double> afferentWeights = networkTopology->getAfferentWeightsPerNeuron(l, n, true);
					for (int afferentWeightIndex = 0; afferentWeightIndex < afferentWeights.size(); afferentWeightIndex++)
					{
						weights->addAttribute(new JSONAttribute(std::to_string((_ULonglong)afferentWeightIndex), new JSONNumberElement<double>(afferentWeights[afferentWeightIndex])));
					}
					neuron->addAttribute(new JSONAttribute("weights", weights));
				}
				layer->addAttribute(new JSONAttribute(std::to_string((_ULonglong)n), neuron));
			}
			layers->addElement(layer);
		}
		jsonObject.addAttribute(new JSONAttribute("layers", layers));

		return jsonObject.toString();
	}
}