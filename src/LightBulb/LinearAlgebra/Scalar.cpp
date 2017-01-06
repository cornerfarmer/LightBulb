// Includes
#include "LightBulb/LinearAlgebra/Scalar.hpp"

LightBulb::Scalar::Scalar()
{
	eigenValue = 0;
	viennaclValue = 0;
}


void LightBulb::Scalar::copyToEigen() const
{
	eigenValue = viennaclValue;
}

void LightBulb::Scalar::copyToViennaCl() const
{
	viennaclValue = eigenValue;
}
