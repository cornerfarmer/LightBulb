// Includes
#include "Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"


std::vector<Eigen::MatrixXd> AbstractGradientCalculation::calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap)
{
	std::vector<Eigen::MatrixXd> gradient(networkTopology->getLayerCount() - 1);

	calcGradient(networkTopology, errormap, gradient);

	return gradient;
}
