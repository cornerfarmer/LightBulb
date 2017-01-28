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
			this->eigenValue = this->viennaclValue;
		}

		void copyToViennaCl() const override
		{
			this->viennaclValue = this->eigenValue;
		}
	public:
		Scalar()
		{
			this->eigenValue = 0;
			this->viennaclValue = 0;
		}

	};
}

#include "LightBulb/IO/ScalarIO.hpp"

#endif