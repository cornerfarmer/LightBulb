// Includes
#include "Function/ActivationFunction/RectifierFunction.hpp"
// Library includes

namespace LightBulb
{
	RectifierFunction::RectifierFunction(double leakyFac_)
	{
		leakyFac = leakyFac_;
	}

	double RectifierFunction::execute(double input) const
	{
		// Execture the fermi function
		return  std::max(leakyFac * input, input);
	}

	void RectifierFunction::execute(int layerNr, std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, const std::vector<Eigen::VectorXd>& netInputs) const
	{
		activations[layerNr] = netInputs[layerNr].cwiseMax(0);
	}

	double RectifierFunction::executeDerivation(double input) const
	{
		// Execute the derivation of the Fermi function		
		return (input > 0);
	}

	AbstractCloneable* RectifierFunction::clone() const
	{
		return new RectifierFunction(*this);
	}

	double RectifierFunction::getMaximum() const
	{
		return 1;
	}

	double RectifierFunction::getMinimum() const
	{
		return 0;
	}

	bool RectifierFunction::hasAMaxAndMinimum() const
	{
		return false;
	}

}
