#pragma once

#ifndef _VECTOR_H_
#define _VECTOR_H_

// Includes
#include <Eigen/Dense>
#include <viennacl/vector.hpp>
#include "AbstractLinearAlgebraObject.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations

	class Vector : public AbstractLinearAlgebraObject<Eigen::VectorXf, viennacl::vector<float>>
	{
	protected:
		void copyToEigen() const override;
		void copyToViennaCl() const override;
	public:
		Vector(int rows = 0);
		Vector(const Eigen::VectorXf& eigenVector);
	};
}

#define COMMA ,
USE_PARENT_SERIALIZATION(LightBulb::Vector, LightBulb::AbstractLinearAlgebraObject<Eigen::VectorXf COMMA viennacl::vector<float>>, LightBulb)

#endif