#pragma once

#ifndef _ABSTRACTLINEARALGEBRAOBJECT_H_
#define _ABSTRACTLINEARALGEBRAOBJECT_H_

// Includes
#include <viennacl/backend/memory.hpp>

namespace LightBulb
{
	// Forward declarations

	enum CalculatorType
	{
		CT_CPU,
		CT_GPU
	};

	template<typename EigenType, typename ViennaCLType>
	class AbstractLinearAlgebraObject
	{
		template <class Archive, class EigenT, class ViennaCLT>
		friend void save(Archive& archive, AbstractLinearAlgebraObject<EigenT, ViennaCLT> const& linearAlgebraObject);
		template <class Archive, class EigenT, class ViennaCLT>
		friend void load(Archive& archive, AbstractLinearAlgebraObject<EigenT, ViennaCLT>& linearAlgebraObject);
	protected:
		mutable EigenType eigenValue;
		mutable ViennaCLType viennaclValue;
		mutable bool eigenValueIsDirty;
		mutable bool viennaclValueIsDirty;

		void refreshEigenValue() const
		{
			viennacl::backend::finish();
			copyToEigen();
			viennaclValueIsDirty = false;
		}

		void refreshViennaclValue() const
		{
			viennacl::backend::finish();
			copyToViennaCl();
			eigenValueIsDirty = false;
		}

		virtual void copyToEigen() const = 0;

		virtual void copyToViennaCl() const = 0;

	public:
		virtual ~AbstractLinearAlgebraObject() {};
		AbstractLinearAlgebraObject()
		{
			eigenValueIsDirty = false;
			viennaclValueIsDirty = false;
		}

		const EigenType& getEigenValue() const
		{
			if (viennaclValueIsDirty)
				refreshEigenValue();
			return eigenValue;
		}


		EigenType& getEigenValueForEditing()
		{
			if (viennaclValueIsDirty)
				refreshEigenValue();
			eigenValueIsDirty = true;
			return eigenValue;
		}

		const ViennaCLType& getViennaclValue() const
		{
			if (eigenValueIsDirty)
				refreshViennaclValue();
			return viennaclValue;
		}


		ViennaCLType& getViennaclValueForEditing()
		{
			if (eigenValueIsDirty)
				refreshViennaclValue();
			viennaclValueIsDirty = true;
			return viennaclValue;
		}

		bool operator==(const AbstractLinearAlgebraObject<EigenType, ViennaCLType>& linearAlgebraObject) const
		{
			if (viennaclValueIsDirty)
				refreshEigenValue();
			return eigenValue == linearAlgebraObject.eigenValue;
		}
	};
}

#include "LightBulb/IO/AbstractLinearAlgebraObjectIO.hpp"


#endif