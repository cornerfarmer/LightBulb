#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

// Includes
#include <Eigen/Dense>
#include <viennacl/matrix.hpp>
#include "AbstractLinearAlgebraObject.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations

	class Matrix : public AbstractLinearAlgebraObject<Eigen::MatrixXf, viennacl::matrix<float>>
	{
	protected:
		void copyToEigen() const override;
		void copyToViennaCl() const override;
	public:
		Matrix(int rows = 0, int cols = 0);
		Matrix(const Eigen::MatrixXf& eigenMatrix);
	};

}

#define COMMA ,
USE_PARENT_SERIALIZATION(LightBulb::Matrix, LightBulb::AbstractLinearAlgebraObject<Eigen::MatrixXf COMMA viennacl::matrix<float>>, LightBulb)


#endif