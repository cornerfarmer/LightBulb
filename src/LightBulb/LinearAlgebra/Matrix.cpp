// Includes
#include "LightBulb/LinearAlgebra/Matrix.hpp"

LightBulb::Matrix::Matrix(int rows, int cols)
{
	if (rows > 0 && cols > 0) {
		if (getCalculatorType() == CT_GPU)
		{
			viennaclValue = viennacl::matrix<float>(rows, cols);
			viennaclValueIsDirty = true;
		}
		else
		{
			eigenValue = Eigen::MatrixXf(rows, cols);
			eigenValueIsDirty = true;
		}
	}
}

LightBulb::Matrix::Matrix(const Eigen::MatrixXf& eigenMatrix)
{
	eigenValue = eigenMatrix;
	eigenValueIsDirty = true;
}

void LightBulb::Matrix::copyToEigen() const
{
	if (eigenValue.rows() != viennaclValue.size1() || eigenValue.cols() != viennaclValue.size2())
		eigenValue.resize(viennaclValue.size1(), viennaclValue.size2());

	viennacl::copy(viennaclValue, eigenValue);
}

void LightBulb::Matrix::copyToViennaCl() const
{
	if (eigenValue.rows() != viennaclValue.size1() || eigenValue.cols() != viennaclValue.size2())
		viennaclValue.resize(eigenValue.rows(), eigenValue.cols());

	if (eigenValue.size() != 0)
		viennacl::copy(eigenValue, viennaclValue);
}
