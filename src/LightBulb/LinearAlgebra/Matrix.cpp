// Includes
#include "LightBulb/LinearAlgebra/Matrix.hpp"

LightBulb::Matrix::Matrix(int rows, int cols)
{
	eigenValue = Eigen::MatrixXf(rows, cols);
	eigenValueIsDirty = true;
}

LightBulb::Matrix::Matrix(const Eigen::MatrixXf& eigenMatrix)
{
	eigenValue = eigenMatrix;
	eigenValueIsDirty = true;
}

void LightBulb::Matrix::checkEigenSizes() const
{
	if (eigenValue.rows() != viennaclValue.size1() || eigenValue.cols() != viennaclValue.size2())
		eigenValue.resize(viennaclValue.size1(), viennaclValue.size2());
}

void LightBulb::Matrix::checkViennaClSizes() const
{
	if (eigenValue.rows() != viennaclValue.size1() || eigenValue.cols() != viennaclValue.size2())
		viennaclValue.resize(eigenValue.rows(), eigenValue.cols());
}
