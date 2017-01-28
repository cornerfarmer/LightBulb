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
			if (this->eigenValue.rows() != this->viennaclValue.size1() || this->eigenValue.cols() != this->viennaclValue.size2())
				this->eigenValue.resize(this->viennaclValue.size1(), this->viennaclValue.size2());

			viennacl::copy(this->viennaclValue, this->eigenValue);
		}

		void copyToViennaCl() const override
		{
			if (this->eigenValue.rows() != this->viennaclValue.size1() || this->eigenValue.cols() != this->viennaclValue.size2())
				this->viennaclValue.resize(this->eigenValue.rows(), this->eigenValue.cols());

			if (this->eigenValue.size() != 0)
				viennacl::copy(this->eigenValue, this->viennaclValue);
		}

	public:
		Matrix(int rows = 0, int cols = 0)
		{
			if (rows > 0 && cols > 0) {
				this->eigenValue = Eigen::Matrix<DataType, -1, -1>(rows, cols);
				this->eigenValueIsDirty = true;
			}
		}

		Matrix(const Eigen::Matrix<DataType, -1, -1>& eigenMatrix)
		{
			this->eigenValue = eigenMatrix;
			this->eigenValueIsDirty = true;
		}
	};

}


#include "LightBulb/IO/MatrixIO.hpp"

#endif