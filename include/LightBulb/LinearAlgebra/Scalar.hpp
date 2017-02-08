#pragma once

#ifndef _SCALAR_H_
#define _SCALAR_H_

// Includes
#include <viennacl/scalar.hpp>
#include "AbstractLinearAlgebraObject.hpp"

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
		Scalar(DataType initialValue = 0)
		{
			this->eigenValue = initialValue;
			this->eigenValueIsDirty = true;
		}

	};
}

#include "LightBulb/IO/ScalarIO.hpp"

#endif