// Includes
#include "Function/RectifierFunction.hpp"
// Library includes

RectifierFunction::RectifierFunction(double leakyFac_)
{
	leakyFac = leakyFac_;
}

double RectifierFunction::execute(double input)
{
	// Execture the fermi function
	return  std::max(leakyFac * input, input);
}

double RectifierFunction::executeDerivation(double input)
{
	// Execute the derivation of the Fermi function		
	return input * (input > 0);
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