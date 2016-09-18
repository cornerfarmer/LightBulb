// Includes
#include "Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	void AbstractGradientCalculation::calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap)
	{
		calcGradient(networkTopology, *networkTopology->getAllNetInputs(), *networkTopology->getAllActivations(), errormap);
	}

	void AbstractGradientCalculation::initGradient(AbstractNetworkTopology* networkTopology)
	{
		if (gradient.empty()) {
			gradient = *networkTopology->getAllWeights();
		}

		// Adjust all hidden/output layers except 
		for (int l = 0; l < gradient.size(); l++)
		{
			gradient[l].setZero();
		}
	}


	std::vector<Eigen::MatrixXd>* AbstractGradientCalculation::getGradient()
	{
		return &gradient;
	}
}
