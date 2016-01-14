// Includes
#include "IO/BrainJSExporter.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FastLayeredNetwork.hpp"
#include "IO/JSONObject.hpp"
#include "IO/JSONArray.hpp"
#include "IO/JSONNumberElement.hpp"

std::string BrainJSExporter::execute(NeuralNetwork* neuralNetwork)
{
	JSONObject jsonObject;
	JSONArray* layers = new JSONArray();
	FastLayeredNetwork* layeredNetwork = dynamic_cast<FastLayeredNetwork*>(neuralNetwork->getNetworkTopology());
	
	int layerCount = layeredNetwork->getLayerCount();
	for (int l = 0; l < layerCount; l++)
	{
		JSONObject* layer = new JSONObject();
		int neuronCount = layeredNetwork->getNeuronCountInLayer(l);
		for (int n = 0; n < neuronCount; n++)
		{
			JSONObject* neuron = new JSONObject();
			if (l > 0)
			{
				neuron->addAttribute(new JSONAttribute("bias", new JSONNumberElement<double>(layeredNetwork->getBiasWeightOfNeuron(l, n))));

				JSONObject* weights = new JSONObject();
				std::vector<double> afferentWeights = layeredNetwork->getAfferentWeights(l, n);
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