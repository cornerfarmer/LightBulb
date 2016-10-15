// Includes
#include "Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	void AbstractGradientCalculation::calcGradient(const AbstractNetworkTopology* networkTopology, const ErrorMap_t* errormap)
	{
		gradientToUse = &gradient;
		calcGradient(networkTopology, *networkTopology->getAllNetInputs(), *networkTopology->getAllActivations(), errormap);
	}

	void AbstractGradientCalculation::calcGradient(const AbstractNetworkTopology* networkTopology, const ErrorMap_t* errormap, std::vector<Eigen::MatrixXd>& gradient)
	{
		gradientToUse = &gradient;
		calcGradient(networkTopology, *networkTopology->getAllNetInputs(), *networkTopology->getAllActivations(), errormap);
	}

	void AbstractGradientCalculation::initGradient(const AbstractNetworkTopology* networkTopology)
	{
		if (gradient.empty()) {
			gradient = *networkTopology->getAllWeights();
		}

		// Adjust all hidden/output layers except 
		for (int l = 0; l < gradient.size(); l++)
		{
			gradient[l].setZero();
		}
		gradientToUse = &gradient;
	}


	std::vector<Eigen::MatrixXd>* AbstractGradientCalculation::getGradient()
	{
		return &gradient;
	}
}
