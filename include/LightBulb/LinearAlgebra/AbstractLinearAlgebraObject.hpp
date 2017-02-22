#pragma once

#ifndef _ABSTRACTLINEARALGEBRAOBJECT_H_
#define _ABSTRACTLINEARALGEBRAOBJECT_H_

// Includes

namespace LightBulb
{
	// Forward declarations

	enum CalculatorType : unsigned int
	{
		CT_CPU,
		CT_GPU
	};

	/**
	 * \brief Describes an abstract linear algebra data structure.
	 * \tparam EigenType The data type to use for cpu computation.
	 * \tparam ViennaCLType The data type to use for gpu computation.
	 */
	template<typename EigenType, typename ViennaCLType>
	class AbstractLinearAlgebraObject
	{
		template <class Archive, class EigenT, class ViennaCLT>
		friend void save(Archive& archive, AbstractLinearAlgebraObject<EigenT, ViennaCLT> const& linearAlgebraObject);
		template <class Archive, class EigenT, class ViennaCLT>
		friend void load(Archive& archive, AbstractLinearAlgebraObject<EigenT, ViennaCLT>& linearAlgebraObject);
	protected:
		/**
		 * \brief The object to use for cpu computation. 
		 */
		mutable EigenType eigenValue;
		/**
		* \brief The object to use for gpu computation.
		*/
		mutable ViennaCLType viennaclValue;
		/**
		 * \brief True, if eigenValue is dirty and viennaclValue is outdated.
		 */
		mutable bool eigenValueIsDirty;
		/**
		* \brief True, if viennaclValue is dirty and eigenValue is outdated.
		*/
		mutable bool viennaclValueIsDirty;
		/**
		 * \brief Copies all changes from viennaclValue to eigenValue.
		 */
		void refreshEigenValue() const
		{
			//viennacl::backend::finish();
			copyToEigen();
			viennaclValueIsDirty = false;
		}
		/**
		* \brief Copies all changes from eigenValue to viennaclValue.
		*/
		void refreshViennaclValue() const
		{
			//viennacl::backend::finish();
			copyToViennaCl();
			eigenValueIsDirty = false;
		}
		/**
		 * \brief Copies the eigenValue to the viennaclValue.
		 */
		virtual void copyToEigen() const = 0;
		/**
		* \brief Copies the viennaclValue to the eigenValue.
		*/
		virtual void copyToViennaCl() const = 0;
		/**
		 * \brief Copies all data from the given linear algebra object.
		 * \param other The linear algebra object to copy.
		 */
		void copyAllFrom(const AbstractLinearAlgebraObject<EigenType, ViennaCLType>& other)
		{
			if (other.eigenValueIsDirty)
			{
				eigenValue = other.eigenValue;
				eigenValueIsDirty = true;
				viennaclValueIsDirty = false;
			}
			else
			{
				viennaclValue = other.viennaclValue;
				viennaclValueIsDirty = true;
				eigenValueIsDirty = false;
			}
		}
	public:
		virtual ~AbstractLinearAlgebraObject() {};
		AbstractLinearAlgebraObject()
		{
			eigenValueIsDirty = false;
			viennaclValueIsDirty = false;
		}
		AbstractLinearAlgebraObject(const AbstractLinearAlgebraObject<EigenType, ViennaCLType>& other)
		{
			copyAllFrom(other);
		}
		AbstractLinearAlgebraObject<EigenType, ViennaCLType>& operator=(const AbstractLinearAlgebraObject<EigenType, ViennaCLType>& linearAlgebraObject)
		{
			if (linearAlgebraObject.eigenValueIsDirty)
			{
				eigenValue = linearAlgebraObject.eigenValue;
				eigenValueIsDirty = true;
				viennaclValueIsDirty = false;
			}
			else
			{
				viennaclValue = linearAlgebraObject.viennaclValue;
				viennaclValueIsDirty = true;
				eigenValueIsDirty = false;
			}
			return *this;
		}
		/**
		 * \brief Returns the data as eigen value (cpu).
		 * \details If the eigen value is outdated it will be refreshed.
		 * \return The eigen value.
		 */
		const EigenType& getEigenValue() const
		{
			if (viennaclValueIsDirty)
				refreshEigenValue();
			return eigenValue;
		}
		/**
		* \brief Returns the data as eigen value (cpu) and reserves it for modifications.
		* \details If the eigen value is outdated it will be refreshed.
		* \return The eigen value.
		*/
		EigenType& getEigenValueForEditing()
		{
			if (viennaclValueIsDirty)
				refreshEigenValue();
			eigenValueIsDirty = true;
			return eigenValue;
		}
		/**
		* \brief Returns the data as viennacl value (gpu).
		* \details If the viennacl value is outdated it will be refreshed.
		* \return The viennacl value.
		*/
		const ViennaCLType& getViennaclValue() const
		{
			if (eigenValueIsDirty)
				refreshViennaclValue();
			return viennaclValue;
		}
		/**
		* \brief Returns the data as viennacl value (gpu) and reserves it for modifications.
		* \details If the viennacl value is outdated it will be refreshed.
		* \return The viennacl value.
		*/
		ViennaCLType& getViennaclValueForEditing()
		{
			if (eigenValueIsDirty)
				refreshViennaclValue();
			viennaclValueIsDirty = true;
			return viennaclValue;
		}
		/**
		 * \brief Compares two linear algebra objects.
		 * \param linearAlgebraObject The other linear algebra objects.
		 * \return True if they are equal.
		 */
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