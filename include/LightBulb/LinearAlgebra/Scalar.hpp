#pragma once

#ifndef _SCALAR_H_
#define _SCALAR_H_

// Includes
#include <viennacl/scalar.hpp>
#include "AbstractLinearAlgebraObject.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	// Forward declarations

	template<typename DataType = float>
	class Scalar : public AbstractLinearAlgebraObject<DataType, viennacl::scalar<DataType>>
	{
	protected:
		void copyToEigen() const override
		{
			eigenValue = viennaclValue;
		}

		void copyToViennaCl() const override
		{
			viennaclValue = eigenValue;
		}
	public:
		Scalar()
		{
			eigenValue = 0;
			viennaclValue = 0;
		}

	};
}

#include "LightBulb/IO/ScalarIO.hpp"

#endif