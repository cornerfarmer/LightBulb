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

	template<class EigenType, class ViennaCLType>
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
			checkEigenSizes();
			viennacl::copy(viennaclValue, eigenValue);
			viennaclValueIsDirty = false;
		}

		void refreshViennaclValue() const
		{
			viennacl::backend::finish();
			checkViennaClSizes();

			if (eigenValue.size() != 0)
				viennacl::copy(eigenValue, viennaclValue);
			eigenValueIsDirty = false;
		}

		virtual void checkEigenSizes() const = 0;

		virtual void checkViennaClSizes() const = 0;


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

		int getCalculatorType() const
		{
			return CT_GPU;
		}
	};
}

#include "LightBulb/IO/AbstractLinearAlgebraObjectIO.hpp"


#endif