#pragma once

#ifndef _SCALAR_H_
#define _SCALAR_H_

// Includes
#include <viennacl/scalar.hpp>
#include "AbstractLinearAlgebraObject.hpp"

namespace LightBulb
{
	// Forward declarations

	/**
	 * \brief Describes a single linear algebra data value.
	 * \tparam DataType The data type which should be stored in the data structure.
	 */
	template<typename DataType = float>
	class Scalar : public AbstractLinearAlgebraObject<DataType, viennacl::scalar<DataType>>
	{
	protected:
		// Inherited:
		void copyToEigen() const override
		{
			this->eigenValue = this->viennaclValue;
		}
		void copyToViennaCl() const override
		{
			this->viennaclValue = this->eigenValue;
		}
	public:
		/**
		* \brief Creates a new matrix with a initial value.
		* \param initialValue The initial value.
		*/
		explicit Scalar(DataType initialValue = 0)
		{
			this->eigenValue = initialValue;
			this->eigenValueIsDirty = true;
		}

	};
}

#include "LightBulb/IO/ScalarIO.hpp"

#endif