// Includes
#include "LightBulb/Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"

namespace LightBulb
{
	void AbstractGradientCalculation::calcGradient(const AbstractNetworkTopology& networkTopology, const Vector<>& errorVector, const Vector<>* alternativeActivation)
	{
		gradientToUse = &gradient;
		calcGradient(networkTopology, networkTopology.getAllNetInputs(), networkTopology.getAllActivations(), errorVector, alternativeActivation);
	}

	void AbstractGradientCalculation::calcGradient(const AbstractNetworkTopology& networkTopology, const Vector<>& errorVector, std::vector<Matrix<>>& gradient, const Vector<>* alternativeActivation)
	{
		gradientToUse = &gradient;
		calcGradient(networkTopology, networkTopology.getAllNetInputs(), networkTopology.getAllActivations(), errorVector, alternativeActivation);
	}

	void AbstractGradientCalculation::initGradient(const AbstractNetworkTopology& networkTopology)
	{
		if (gradient.empty()) {
			gradient = networkTopology.getAllWeights();
		}


		// Adjust all hidden/output layers except 
		for (int l = 0; l < gradient.size(); l++)
		{
			if (isCalculatorType(CT_GPU))
				gradient[l].getViennaclValueForEditing().clear();
			else
				gradient[l].getEigenValueForEditing().setZero();
		}
		gradientToUse = &gradient;
	}


	std::vector<Matrix<>>& AbstractGradientCalculation::getGradient()
	{
		return gradient;
	}
}
