// Includes
#include "Graphics/CounterpropagationNetworkStructureChart.hpp"
#include "NetworkTopology/CounterpropagationNetwork.hpp"
#include "Neuron/StandardNeuron.hpp"

CounterpropagationNetworkStructureChart::CounterpropagationNetworkStructureChart(CounterpropagationNetworkStructureChartOptions &options_)
	: AbstractNetworkStructureChart(new CounterpropagationNetworkStructureChartOptions(options_))
{
	// Check if all given options are correct
	// Check if the given neural network is valid
	if (getOptions()->network == NULL)
		throw std::invalid_argument("The given network is not valid");
	// Check if the indices are correct
	if (options->xNeuronCoordinateIndex >= getNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'xNeuronCoordinateIndex'");
	if (options->yNeuronCoordinateIndex >= getNeurons()->size())
		throw std::invalid_argument("Can't find any coordinate with index 'yNeuronCoordinateIndex'");
}

std::vector<StandardNeuron*>* CounterpropagationNetworkStructureChart::getNeurons()
{
	return &getOptions()->network->getNeurons()->front();
}

double CounterpropagationNetworkStructureChart::getRadiusOfNeuron(StandardNeuron& neuron)
{
	return 0.2;
}

std::vector<double> CounterpropagationNetworkStructureChart::getPositionOfNeuron(StandardNeuron& neuron)
{
	return neuron.getAfferentWeightsVector();
}

CounterpropagationNetworkStructureChartOptions* CounterpropagationNetworkStructureChart::getOptions()
{
	return static_cast<CounterpropagationNetworkStructureChartOptions*>(options);
}