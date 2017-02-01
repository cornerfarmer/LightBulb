// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Function/ActivationFunction/RectifierFunction.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

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

	void RectifierFunction::execute(int layerNr, std::vector<Vector<>> &activations, const std::vector<Vector<>> &netInputs) const
	{
		activations[layerNr].getEigenValueForEditing() = netInputs[layerNr].getEigenValue().cwiseMax(0);
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
