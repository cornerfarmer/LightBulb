#pragma once

#ifndef _MATRIXIO_H_
#define _MATRIXIO_H_

// Includes
#include "LightBulb/LinearAlgebra/Matrix.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractLinearAlgebraObject.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param matrix The Matrix to save.
	*/
	template <class Archive, class DataType>
	void save(Archive& archive, Matrix<DataType> const& matrix)
	{
		archive(cereal::base_class<AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, -1>, viennacl::matrix<DataType>>>(&matrix));
	}

	/**
	* \brief Loads an AbstractLinearAlgebraObject.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param matrix The Matrix to load.
	*/
	template <class Archive, class DataType>
	void load(Archive& archive, Matrix<DataType> const matrix)
	{
		archive(cereal::base_class<AbstractLinearAlgebraObject<Eigen::Matrix<DataType, -1, -1>, viennacl::matrix<DataType>>>(&matrix));
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::Matrix<float>);

#endif