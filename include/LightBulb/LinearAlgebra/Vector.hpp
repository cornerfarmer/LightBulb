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


	template<typename DataType = float>
	class Vector : public AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, 1>, viennacl::vector<DataType>>
	{
	protected:
		void copyToEigen() const override
		{
			if (eigenValue.size() != viennaclValue.size())
				eigenValue.resize(viennaclValue.size());

			viennacl::copy(viennaclValue, eigenValue);
		}

		void copyToViennaCl() const override
		{
			if (eigenValue.size() != viennaclValue.size())
				viennaclValue.resize(eigenValue.size());

			if (eigenValue.size() != 0)
				viennacl::copy(eigenValue, viennaclValue);
		}

	public:
		Vector(int rows = 0)
		{
			if (rows > 0) {
				eigenValue = Eigen::Matrix<DataType, -1, 1>(rows);
				eigenValueIsDirty = true;
			}
		}

		Vector(const Eigen::Matrix<DataType, -1, 1>& eigenVector)
		{
			eigenValue = eigenVector;
			eigenValueIsDirty = true;
		}
	};
}

#include "LightBulb/IO/VectorIO.hpp"

#endif