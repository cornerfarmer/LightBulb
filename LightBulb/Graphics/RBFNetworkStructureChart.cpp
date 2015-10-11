// Includes
#include "Graphics/RBFNetworkStructureChart.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/RBFThreshold.hpp"

RBFNetworkStructureChart::RBFNetworkStructureChart(RBFNetworkStructureChartOptions &options_)
	: AbstractNetworkStructureChart(new RBFNetworkStructureChartOptions(options_))
{
	// Check if all given options are correct
	// Check if the given neural network is valid
	if (getOptions()->rbfNetwork == NULL)
		throw std::invalid_argument("The given rbfNetwork is not valid");
	// Check if the indices are correct
	if (options->xNeuronCoordinateIndex >= getNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'xNeuronCoordinateIndex'");
	if (options->yNeuronCoordinateIndex >= getNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'yNeuronCoordinateIndex'");
}

std::vector<StandardNeuron*>* RBFNetworkStructureChart::getNeurons()
{
	return &getOptions()->rbfNetwork->getNeurons()->front();
}

double RBFNetworkStructureChart::getRadiusOfNeuron(StandardNeuron& neuron)
{
	RBFThreshold* thresholdOfNeuron = static_cast<RBFThreshold*>(neuron.getThreshold());
	return thresholdOfNeuron->getWidth();
}

std::vector<double> RBFNetworkStructureChart::getPositionOfNeuron(StandardNeuron& neuron)
{
	return neuron.getAfferentWeightsVector();
}

RBFNetworkStructureChartOptions* RBFNetworkStructureChart::getOptions()
{
	return static_cast<RBFNetworkStructureChartOptions*>(options);
}