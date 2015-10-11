// Includes
#include "Graphics/LVQNetworkStructureChart.hpp"
#include "NetworkTopology/LVQNetwork.hpp"
#include "Neuron/StandardNeuron.hpp"

LVQNetworkStructureChart::LVQNetworkStructureChart(LVQNetworkStructureChartOptions &options_)
	: AbstractNetworkStructureChart(new LVQNetworkStructureChartOptions(options_))
{
	// Check if all given options are correct
	// Check if the given neural network is valid
	if (getOptions()->lvqNetwork == NULL)
		throw std::invalid_argument("The given lvqNetwork is not valid");
	// Check if the indices are correct
	if (options->xNeuronCoordinateIndex >= getNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'xNeuronCoordinateIndex'");
	if (options->yNeuronCoordinateIndex >= getNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'yNeuronCoordinateIndex'");
}

std::vector<StandardNeuron*>* LVQNetworkStructureChart::getNeurons()
{
	return &getOptions()->lvqNetwork->getNeurons()->front();
}

double LVQNetworkStructureChart::getRadiusOfNeuron(StandardNeuron& neuron)
{
	return 0.2;
}

std::vector<double> LVQNetworkStructureChart::getPositionOfNeuron(StandardNeuron& neuron)
{
	return neuron.getAfferentWeightsVector();
}

LVQNetworkStructureChartOptions* LVQNetworkStructureChart::getOptions()
{
	return static_cast<LVQNetworkStructureChartOptions*>(options);
}