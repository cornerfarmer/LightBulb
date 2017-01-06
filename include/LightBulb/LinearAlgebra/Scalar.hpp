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

	class Scalar : public AbstractLinearAlgebraObject<float, viennacl::scalar<float>>
	{
	protected:
		void copyToEigen() const override;
		void copyToViennaCl() const override;
	public:
		Scalar();
	};
}

#define COMMA ,
USE_PARENT_SERIALIZATION(LightBulb::Scalar, LightBulb::AbstractLinearAlgebraObject<float COMMA viennacl::scalar<float>>, LightBulb)

#endif