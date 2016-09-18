// Includes
#include "Function/ActivationFunction/RectifierFunction.hpp"
// Library includes

namespace LightBulb
{
	RectifierFunction::RectifierFunction(double leakyFac_)
	{
		leakyFac = leakyFac_;
	}

	double RectifierFunction::execute(double input)
	{
		// Execture the fermi function
		return  std::max(leakyFac * input, input);
	}

	void RectifierFunction::execute(int layerNr, std::vector<Eigen::VectorXd>& activations, std::vector<Eigen::VectorXd>& netInputs)
	{
		activations[layerNr] = netInputs[layerNr].cwiseMax(0);
	}

	double RectifierFunction::executeDerivation(double input)
	{
		// Execute the derivation of the Fermi function		
		return (input > 0);
	}

	AbstractActivationFunction* RectifierFunction::getActivationFunctionCopy()
	{
		return new RectifierFunction(*this);
	}

	double RectifierFunction::getMaximum()
	{
		return 1;
	}

	double RectifierFunction::getMinimum()
	{
		return 0;
	}

	bool RectifierFunction::hasAMaxAndMinimum()
	{
		return false;
	}

}
