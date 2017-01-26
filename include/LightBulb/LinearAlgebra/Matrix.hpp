#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

// Includes
#include <Eigen/Dense>
#include <viennacl/matrix.hpp>
#include "AbstractLinearAlgebraObject.hpp"

namespace LightBulb
{
	// Forward declarations

	template<typename DataType = float>
	class Matrix : public AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, -1>, viennacl::matrix<DataType>>
	{
	protected:
		void copyToEigen() const override
		{
			if (eigenValue.rows() != viennaclValue.size1() || eigenValue.cols() != viennaclValue.size2())
				eigenValue.resize(viennaclValue.size1(), viennaclValue.size2());

			viennacl::copy(viennaclValue, eigenValue);
		}

		void copyToViennaCl() const override
		{
			if (eigenValue.rows() != viennaclValue.size1() || eigenValue.cols() != viennaclValue.size2())
				viennaclValue.resize(eigenValue.rows(), eigenValue.cols());

			if (eigenValue.size() != 0)
				viennacl::copy(eigenValue, viennaclValue);
		}

	public:
		Matrix(int rows = 0, int cols = 0)
		{
			if (rows > 0 && cols > 0) {
				eigenValue = Eigen::Matrix<DataType, -1, -1>(rows, cols);
				eigenValueIsDirty = true;
			}
		}

		Matrix(const Eigen::Matrix<DataType, -1, -1>& eigenMatrix)
		{
			eigenValue = eigenMatrix;
			eigenValueIsDirty = true;
		}
	};

}


#include "LightBulb/IO/MatrixIO.hpp"

#endif