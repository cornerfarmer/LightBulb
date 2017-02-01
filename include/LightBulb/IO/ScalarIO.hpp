#pragma once

#ifndef _SCALARIO_H_
#define _SCALARIO_H_

// Includes
#include "LightBulb/LinearAlgebra/Scalar.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractLinearAlgebraObject.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param scalar The Scalar to save.
	*/
	template <class Archive, class DataType>
	void save(Archive& archive, Scalar<DataType> const& scalar)
	{
		archive(cereal::base_class<AbstractLinearAlgebraObject<DataType, viennacl::scalar<DataType>>>(&scalar));
	}

	/**
	* \brief Loads an AbstractLinearAlgebraObject.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param scalar The Scalar to load.
	*/
	template <class Archive, class DataType>
	void load(Archive& archive, Scalar<DataType> const& scalar)
	{
		archive(cereal::base_class<AbstractLinearAlgebraObject<DataType, viennacl::scalar<DataType>>>(&scalar));
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::Scalar<float>);

#endif