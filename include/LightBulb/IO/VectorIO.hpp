#pragma once

#ifndef _VECTORIO_H_
#define _VECTORIO_H_

// Includes
#include "LightBulb/LinearAlgebra/Vector.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractLinearAlgebraObject.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param vector The Vector to save.
	*/
	template <class Archive, class DataType = float>
	void save(Archive& archive, Vector<DataType> const& vector)
	{
		archive(cereal::base_class<AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, 1>, viennacl::vector<DataType>>>(&vector));
	}

	/**
	* \brief Loads an AbstractLinearAlgebraObject.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param vector The Vector to load.
	*/
	template <class Archive, class DataType>
	void load(Archive& archive, Vector<DataType> const vector)
	{
		archive(cereal::base_class<AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, 1>, viennacl::vector<DataType>>>(&vector));
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::Vector<float>);

#endif