// Includes
#include "Graphics/RBFNetworkStructureChart.hpp"
#include "NetworkTopology/RBFNetwork.hpp"

RBFNetworkStructureChart::RBFNetworkStructureChart(RBFNetworkStructureChartOptions &options_)
	: AbstractNetworkStructureChart(new RBFNetworkStructureChartOptions(options_))
{
	// Check if all given options are correct
	// Check if the given neural network is valid
	if (getOptions()->rbfNetwork == NULL)
		throw std::invalid_argument("The given rbfNetwork is not valid");
	// Check if the indices are correct
	if (options->xNeuronCoordinateIndex >= getNeuronCount())
		throw std::invalid_argument("Can't find any coordinate with index 'xNeuronCoordinateIndex'");
	if (options->yNeuronCoordinateIndex >= getNeuronCount())
		throw std::invalid_argument("Can't find any coordinate with index 'yNeuronCoordinateIndex'");
}

int RBFNetworkStructureChart::getNeuronCount()
{
	return getOptions()->rbfNetwork->getNeuronCountInLayer(1);
}

double RBFNetworkStructureChart::getRadiusOfNeuron(int neuronIndex)
{
	return getOptions()->rbfNetwork->getWidthOfRBFNeuron(neuronIndex);
}

std::vector<double> RBFNetworkStructureChart::getPositionOfNeuron(int neuronIndex)
{
	Eigen::MatrixXd position = getOptions()->rbfNetwork->getAfferentWeightsPerLayer(1).row(neuronIndex).transpose();
	return std::vector<double>(position.data(), position.data() + position.rows());
}

RBFNetworkStructureChartOptions* RBFNetworkStructureChart::getOptions()
{
	return static_cast<RBFNetworkStructureChartOptions*>(options);
}