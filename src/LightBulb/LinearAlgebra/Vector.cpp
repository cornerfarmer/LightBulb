// Includes
#include "LightBulb/LinearAlgebra/Vector.hpp"

LightBulb::Vector::Vector(int rows)
{
	eigenValue = Eigen::VectorXf(rows);
	eigenValueIsDirty = true;
}

LightBulb::Vector::Vector(const Eigen::VectorXf& eigenVector)
{
	eigenValue = eigenVector;
	eigenValueIsDirty = true;
}

void LightBulb::Vector::checkEigenSizes() const
{
	if (eigenValue.size() != viennaclValue.size())
		eigenValue.resize(viennaclValue.size());
}

void LightBulb::Vector::checkViennaClSizes() const
{
	if (eigenValue.size() != viennaclValue.size())
		viennaclValue.resize(eigenValue.size());
}
